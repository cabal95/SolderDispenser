#include <EEPROM.h>
#include "menu.h"

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const char *SettingsModes[4] = { "Cancel", "Load", "Save", "Init" };

/**
 * Initializes the menu for use.
 * 
 * @param lcd The LCD object to display information on.
 */
void Menu::init(Ssd1306 *lcd)
{
    m_lcd = lcd;

    m_lcd->clear();
    m_lcd->display();

    loadValues();
    updateDisplay();
}

/**
 * Reset the current values to sane defaults.
 */
void Menu::resetValues()
{
    m_mode = DispenserMode::Step;
    m_direction = DispenserDirection::Forward;
    m_stepSize = 5;
    m_driveSpeed = 30;
}

/**
 * Load the values from EEPROM.
 */
void Menu::loadValues()
{
    uint8_t byteValue;

    EEPROM.get<uint8_t>(0, byteValue);
    m_mode = byteValue == DispenserMode::Step ? DispenserMode::Step : DispenserMode::Drive;
    EEPROM.get<uint8_t>(1, byteValue);
    m_direction = byteValue == DispenserDirection::Forward ? DispenserDirection::Forward : DispenserDirection::Backward;
    EEPROM.get<uint16_t>(2, m_stepSize);
    EEPROM.get<uint16_t>(4, m_driveSpeed);
}

/**
 * Save the current values into EEPROM.
 */
void Menu::saveValues()
{
    EEPROM.put<uint8_t>(0, m_mode);
    EEPROM.put<uint8_t>(1, m_direction);
    EEPROM.put<uint16_t>(2, m_stepSize);
    EEPROM.put<uint16_t>(4, m_driveSpeed);
}

/**
 * Update the display to reflect what should be in screen.
 */
void Menu::updateDisplay()
{
    m_lcd->clear();
    m_lcd->setCursor(0, 0);

    if (m_currentMenu == 1)
    {
        m_lcd->print("1. Settings");
        m_lcd->setCursor(0, 1);
        m_lcd->print(SettingsModes[m_settingsMode]);
    }
    else if (m_currentMenu == 2)
    {
        m_lcd->print("2. Mode");
        m_lcd->setCursor(0, 1);
        m_lcd->print(m_mode == DispenserMode::Step ? "Step" : "Drive");
    }
    else if (m_currentMenu == 3)
    {
        m_lcd->print("3. Direction");
        m_lcd->setCursor(0, 1);
        m_lcd->print(m_direction == DispenserDirection::Forward ? "Forward" : "Reverse");
    }
    else if (m_currentMenu == 4)
    {
        m_lcd->print("4. Step Size");
        m_lcd->setCursor(0, 1);
        m_lcd->print(String(m_stepSize));
    }
    else if (m_currentMenu == 5)
    {
        m_lcd->print("5. Drive Speed");
        m_lcd->setCursor(0, 1);
        m_lcd->print(String(m_driveSpeed));
    }

    if (m_isEditing)
    {
        m_lcd->setCursor(0, 1);
    }
    else
    {
        m_lcd->setCursor(0, 0);
    }

    m_lcd->display();
}

/**
 * Gets the current DispenserMode to operate in.
 */
DispenserMode Menu::getMode()
{
    return m_mode;
}

/**
 * Gets the current direction to move the plunger.
 */
DispenserDirection Menu::getDirection()
{
    return m_direction;
}

/**
 * Gets the number of steps to move in Step mode.
 */
uint16_t Menu::getStepSize()
{
    return m_stepSize;
}

/**
 * Gets the number of steps per second to move in Drive mode.
 */
uint16_t Menu::getDriveSpeed()
{
    return m_driveSpeed;
}

/**
 * Signal that the UP key has been pressed.
 */
void Menu::keyUp()
{
    if (m_isEditing)
    {
        if (m_currentMenu == 1)
        {
            m_settingsMode = MIN(4, m_settingsMode + 1);
        }
        else if (m_currentMenu == 2)
        {
            m_mode = (DispenserMode)MIN(DISPENSERMODE_LAST, m_mode + 1);
        }
        else if (m_currentMenu == 3)
        {
            m_direction = (DispenserDirection)MIN(DISPENSERDIRECTION_LAST, m_direction + 1);
        }
        else if (m_currentMenu == 4)
        {
            m_stepSize = MIN(1000, m_stepSize + 1);
        }
        else if (m_currentMenu == 5)
        {
            m_driveSpeed = MIN(1000, m_driveSpeed + 1);
        }
    }
    else
    {
        m_currentMenu = MAX(1, m_currentMenu - 1);
        m_settingsMode = 0;
    }

    updateDisplay();
}

/**
 * Signal that the DOWN key has been pressed.
 */
void Menu::keyDown()
{
    if (m_isEditing)
    {
        if (m_currentMenu == 1)
        {
            m_settingsMode = MAX(0, m_settingsMode - 1);
        }
        else if (m_currentMenu == 2)
        {
            m_mode = (DispenserMode)MAX(0, m_mode - 1);
        }
        else if (m_currentMenu == 3)
        {
            m_direction = (DispenserDirection)MAX(0, m_direction - 1);
        }
        else if (m_currentMenu == 4)
        {
            m_stepSize = MAX(0, m_stepSize - 1);
        }
        else if (m_currentMenu == 5)
        {
            m_driveSpeed = MAX(0, m_driveSpeed - 1);
        }
    }
    else
    {
        m_currentMenu = MIN(5, m_currentMenu + 1);
        m_settingsMode = 0;
    }

    updateDisplay();
}

/**
 * Signal that the SELECT key has been pressed.
 */
void Menu::keySelect()
{
    if (!m_isEditing)
    {
        m_isEditing = true;
    }
    else
    {
        if (m_currentMenu == 1)
        {
            if (m_settingsMode == 1)
            {
                loadValues();
            }
            else if (m_settingsMode == 2 || m_settingsMode == 3)
            {
                if (m_settingsMode == 3)
                {
                    resetValues();
                }

                saveValues();
            }

            m_settingsMode = 0;
            m_isEditing = false;
        }
        else
        {
            m_isEditing = false;
        }
    }

    updateDisplay();
}
