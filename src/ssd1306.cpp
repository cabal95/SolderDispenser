#include "ssd1306.h"

#define BUFFER_LENGTH 32
#define WIRE_MAX min(256, BUFFER_LENGTH)

enum SsdCommand
{
    SetLowerColumnStartAddress = 0x00,
    SetHigherColumnStartAddress = 0x10,
    SetMemoryAddressingMode = 0x20,
    SetColumnAddress = 0x21,
    SetPageAddress = 0x22,
    DeactivateScroll = 0x2E,
    SetDisplayStartLine = 0x40,
    SetContrast = 0x81,
    ChargePump = 0x8D,
    SetSegmentRemap = 0xA0,
    DisplayAllOnResume = 0xA4,
    DisplayAllOn = 0xA5,
    NormalDisplay = 0xA6,
    InvertDisplay = 0xA7,
    SetMultiplex = 0xA8,
    DisplayOff = 0xAE,
    DisplayOn = 0xAF,
    ComScanInc = 0xC0,
    ComScanDec = 0xC8,
    SetDisplayOffset = 0xD3,
    SetDisplayClockDivide = 0xD5,
    SetPreCharge = 0xD9,
    SetComPins = 0xDA,
    SetVComDeselect = 0xDB,
};

enum SsdVcc
{
    External = 0x01,
    SwitchCap = 0x02
};

/**
 * Create a new instance of the Ssd1306 class.
 * 
 * @param wire The TwoWire interface that should be used to communicate
 * with the device.
 * @param address The I2C address of the device to communicate with.
 */
Ssd1306::Ssd1306(TwoWire *wire, uint8_t address)
{
    m_wire = wire;
    m_address = address;
    m_screenWidth = 128;
    m_screenHeight = 32;
    m_cursor[0] = m_cursor[1] = 0;
}

/**
 * Initialize the device and prepare it for use. The display will
 * be cleared to black and turned on before this call returns.
 */
void Ssd1306::begin()
{
    m_contrast = 0x7F;

    m_wire->setClock(400000);

    uint8_t init[] = {
        SsdCommand::DisplayOff,
        SsdCommand::SetDisplayClockDivide,
        0x80,
        SsdCommand::SetMultiplex,
        (uint8_t)(m_screenHeight - 1),
        SsdCommand::SetDisplayOffset,
        0x00,
        SsdCommand::SetDisplayStartLine,
        SsdCommand::ChargePump,
        0x14,
        SsdCommand::SetMemoryAddressingMode,
        0x00,
        SsdCommand::SetSegmentRemap | 0x01,
        SsdCommand::ComScanDec,
        SsdCommand::SetComPins,
        0x02,
        SsdCommand::SetContrast,
        m_contrast,
        SsdCommand::SetPreCharge,
        0x22,
        SsdCommand::SetVComDeselect,
        0x20,
        SsdCommand::DisplayAllOnResume,
        SsdCommand::NormalDisplay,
        SsdCommand::DeactivateScroll};

    commandList(init, sizeof(init));

    m_wire->setClock(100000);

    //
    // Allocate, clear and then send the buffer to the display.
    //
    m_buffer = (uint8_t *)malloc(m_screenWidth * m_screenHeight / 8);
    clear();
    display();

    command(SsdCommand::DisplayOn);
}

/**
 * Writes a single command to the display.
 * 
 * @param command The command byte to be written.
 */
void Ssd1306::command(uint8_t command)
{
    m_wire->beginTransmission(m_address);
    m_wire->write((uint8_t)0x00);
    m_wire->write(command);
    m_wire->endTransmission();
}

/**
 * Writes a sequence of commands to the display.
 * 
 * @param commands A pointer to the first command byte that should
 * be written.
 * @param count The number of command bytes to be written.
 */
void Ssd1306::commandList(const uint8_t *commands, uint8_t count)
{
    m_wire->beginTransmission(m_address);
    m_wire->write((uint8_t)0x00);

    uint16_t bytesOut = 1;

    while (count--)
    {
        //
        // Check if we have filled the transmission buffer.
        //
        if (bytesOut >= WIRE_MAX)
        {
            m_wire->endTransmission();
            m_wire->beginTransmission(m_address);
            m_wire->write((uint8_t)0x00); // Co = 0, D/C = 0
            bytesOut = 1;
        }

        m_wire->write(*commands++);
        bytesOut++;
    }

    m_wire->endTransmission();
}

/**
 * Dims the display.
 * 
 * @param dim If true then the display is dimmed; otherwise it is
 * returned to normal brightness levels.
 */
void Ssd1306::dimDisplay(bool dim)
{
    m_wire->setClock(400000);

    if (dim)
    {
        uint8_t cmds[] = {SsdCommand::SetContrast, 0, SsdCommand::SetPreCharge, 0x00};

        commandList(cmds, sizeof(cmds));
    }
    else
    {
        uint8_t cmds[] = {SsdCommand::SetContrast, m_contrast, SsdCommand::SetPreCharge, 0x22};

        commandList(cmds, sizeof(cmds));
    }

    m_wire->setClock(100000);
}

/**
 * Clears the display buffer to black. This does not update the
 * display itself.
 */
void Ssd1306::clear()
{
    memset(m_buffer, 0, m_screenWidth * m_screenHeight / 8);
}

/**
 * Writes the buffered screen contents to the OLED screen.
 */
void Ssd1306::display()
{
    m_wire->setClock(400000);

    uint8_t cmds[] = {
        SsdCommand::SetPageAddress,
        0,
        0xFF,
        SsdCommand::SetColumnAddress,
        0};

    commandList(cmds, sizeof(cmds));
    command(m_screenWidth - 1);

    uint16_t count = m_screenWidth * m_screenHeight / 8;
    const uint8_t *ptr = m_buffer;

    m_wire->beginTransmission(m_address);
    m_wire->write((uint8_t)0x40);

    uint16_t bytesWritten = 1;

    while (count--)
    {
        //
        // Check if we have filled the transmit buffer.
        //
        if (bytesWritten >= WIRE_MAX)
        {
            m_wire->endTransmission();
            m_wire->beginTransmission(m_address);
            m_wire->write((uint8_t)0x40);
            bytesWritten = 1;
        }

        m_wire->write(*ptr++);
        bytesWritten++;
    }

    m_wire->endTransmission();
    m_wire->setClock(100000);
}

/**
 * Draws a single pixel into the display buffer.
 * 
 * @param x The x coordinate of the pixel to draw.
 * @param y The y coordinate of the pixel to draw.
 * @param pixelOn If true then the pixel is set to white; otherwise black.
 */
void Ssd1306::drawPixel(uint8_t x, uint8_t y, bool pixelOn)
{
    if (x >= m_screenWidth || y >= m_screenHeight)
    {
        return;
    }

    if (pixelOn)
    {
        m_buffer[x + (y / 8) * m_screenWidth] |= (1 << (y & 7));
    }
    else
    {
        m_buffer[x + (y / 8) * m_screenWidth] &= ~(1 << (y & 7));
    }
}

/**
 * Gets the width in pixels of each glyph of the currently loaded font.
 */
uint8_t Ssd1306::getFontWidth()
{
    return m_fontWidth;
}

/**
 * Gets the height in pixels of each glyph of the currently loaded font.
 */
uint8_t Ssd1306::getFontHeight()
{
    return m_fontHeight;
}

/**
 * Loads a font and prepares to use it for drawing text.
 * 
 * @param fontBase The base address of the font bitmap data.
 * @param fontWidth The width of each glyph in pixels.
 * @param fontHeight The height of each glyph in pixels.
 */
void Ssd1306::setFont(const uint8_t *fontBase, uint8_t fontWidth, uint8_t fontHeight)
{
    m_fontBase = fontBase;
    m_fontWidth = fontWidth;
    m_fontHeight = fontHeight;
}

/**
 * Sets the location of the cursor for the next character draw
 * operation.
 * 
 * @param column The zero-based column to locate the cursor at.
 * @param row The zero-based row to locate the cursor at.
 */
void Ssd1306::setCursor(uint8_t column, uint8_t row)
{
    m_cursor[0] = column;
    m_cursor[1] = row;
}

/**
 * Prints a string to the display buffer at the current cursor location.
 * 
 * @param string The text to write to the display buffer.
 */
void Ssd1306::print(String string)
{
    unsigned int length = string.length();

    for (unsigned int i = 0; i < length; i++)
    {
        drawGlyph(m_cursor[0] * m_fontWidth, m_cursor[1] * m_fontHeight, string[i]);
        m_cursor[0] += 1;
    }
}

/**
 * Draw a single character glyph at the specified pixel location.
 * 
 * @param x The x position in pixels to begin drawing the glyph at.
 * @param y The y position in pixels to begin drawing the glyph at.
 * @param glyph The character to draw at the specified location.
 */
void Ssd1306::drawGlyph(uint8_t x, uint8_t y, unsigned char glyph)
{
    if (glyph < 32 || glyph > 126 || m_fontBase == nullptr)
    {
        return;
    }

    unsigned const char *font_base = m_fontBase + ((glyph - 32) * m_fontHeight);

    for (int row = 0; row < m_fontHeight; row++)
    {
        unsigned char rowValue = pgm_read_byte(font_base + row);

        for (int px = 0; px < m_fontWidth; px++)
        {
            if (((rowValue >> px) & 0x01) == 0x01)
            {
                drawPixel(x + px, y + row, true);
            }
        }
    }
}

/**
 * Draw a string of text at the specified pixel location.
 * 
 * @param x The x position in pixels to begin drawing the glyph at.
 * @param y The y position in pixels to begin drawing the glyph at.
 * @param string The string to draw at the specified location.
 */
void Ssd1306::drawString(uint8_t x, uint8_t y, String string)
{
    unsigned int length = string.length();

    for (unsigned int i = 0; i < length; i++)
    {
        drawGlyph(x, y, string[i]);
        x += m_fontWidth;
    }
}
