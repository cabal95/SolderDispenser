#ifndef SSD1306_H
#define SSD1306_H

#include <Arduino.h>
#include <Wire.h>

/**
 * Class to drive an SSD1306 128x32 OLED display over I2C.
 */
class Ssd1306
{
private:
    /**
     * The I2C interface to use to communicate with the device.
     */
    TwoWire *m_wire;

    /**
     * The address of the device on the wire bus.
     */
    uint8_t m_address;

    /**
     * The memory buffer that holds our screen contents that will need to
     * be displayed.
     */
    uint8_t *m_buffer;

    /**
     * The width of the screen in pixels.
     */
    uint8_t m_screenWidth;

    /**
     * The height of the screen in pixels.
     */
    uint8_t m_screenHeight;

    /**
     * The current contrast setting for the display.
     */
    uint8_t m_contrast;

    /**
     * The current cursor position for drawing text.
     */
    uint8_t m_cursor[2];

    /**
     * The width of each character in pixels for the selected font.
     */
    uint8_t m_fontWidth;

    /**
     * The height of each character in pixels for the selected font.
     */
    uint8_t m_fontHeight;

    /**
     * The base memory address of the font bitmap data.
     */
    const unsigned char *m_fontBase;

    /**
     * Writes a single command to the display.
     * 
     * @param command The command byte to be written.
     */
    void command(uint8_t command);

    /**
     * Writes a sequence of commands to the display.
     * 
     * @param commands A pointer to the first command byte that should
     * be written.
     * @param count The number of command bytes to be written.
     */
    void commandList(const uint8_t *commands, uint8_t count);

public:
    /**
     * Create a new instance of the Ssd1306 class.
     * 
     * @param wire The TwoWire interface that should be used to communicate
     * with the device.
     * @param address The I2C address of the device to communicate with.
     */
    Ssd1306(TwoWire *wire, uint8_t address);

    /**
     * Initialize the device and prepare it for use. The display will
     * be cleared to black and turned on before this call returns.
     */
    void begin();
    
    /**
     * Clears the display buffer to black. This does not update the
     * display itself.
     */
    void clear();

    /**
     * Dims the display.
     * 
     * @param dim If true then the display is dimmed; otherwise it is
     * returned to normal brightness levels.
     */
    void dimDisplay(bool dim);

    /**
     * Writes the buffered screen contents to the OLED screen.
     */
    void display();

    /**
     * Draws a single pixel into the display buffer.
     * 
     * @param x The x coordinate of the pixel to draw.
     * @param y The y coordinate of the pixel to draw.
     * @param pixelOn If true then the pixel is set to white; otherwise black.
     */
    void drawPixel(uint8_t x, uint8_t y, bool pixelOn);

    /**
     * Gets the width in pixels of each glyph of the currently loaded font.
     */
    uint8_t getFontWidth();

    /**
     * Gets the height in pixels of each glyph of the currently loaded font.
     */
    uint8_t getFontHeight();

    /**
     * Loads a font and prepares to use it for drawing text.
     * 
     * @param fontBase The base address of the font bitmap data.
     * @param fontWidth The width of each glyph in pixels.
     * @param fontHeight The height of each glyph in pixels.
     */
    void setFont(const uint8_t *fontBase, uint8_t fontWidth, uint8_t fontHeight);

    /**
     * Sets the location of the cursor for the next character draw
     * operation.
     * 
     * @param column The zero-based column to locate the cursor at.
     * @param row The zero-based row to locate the cursor at.
     */
    void setCursor(uint8_t column, uint8_t row);

    /**
     * Prints a string to the display buffer at the current cursor location.
     * 
     * @param string The text to write to the display buffer.
     */
    void print(String string);

    /**
     * Draw a single character glyph at the specified pixel location.
     * 
     * @param x The x position in pixels to begin drawing the glyph at.
     * @param y The y position in pixels to begin drawing the glyph at.
     * @param glyph The character to draw at the specified location.
     */
    void drawGlyph(uint8_t x, uint8_t y, uint8_t glyph);

    /**
     * Draw a string of text at the specified pixel location.
     * 
     * @param x The x position in pixels to begin drawing the glyph at.
     * @param y The y position in pixels to begin drawing the glyph at.
     * @param string The string to draw at the specified location.
     */
    void drawString(uint8_t x, uint8_t y, String string);
};

#endif
