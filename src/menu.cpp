#include "menu.h"

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

Menu::Menu(LiquidCrystal *lcd)
{
    m_lcd = lcd;

    m_lcd->blink();
    m_lcd->clear();

    updateDisplay();
}

DispenserMode Menu::getMode()
{
    return m_mode;
}

DispenserDirection Menu::getDirection()
{
    return m_direction;
}

uint16_t Menu::getStepSize()
{
    return m_stepSize;
}

void Menu::updateDisplay()
{
    m_lcd->clear();

    if (m_currentMenu == 1)
    {
        m_lcd->print("1. Mode");
        m_lcd->setCursor(0, 1);
        m_lcd->print(m_mode == DispenserMode::Step ? "Step" : "Continuous");
    }
    else if (m_currentMenu == 2)
    {
        m_lcd->print("2. Direction");
        m_lcd->setCursor(0, 1);
        m_lcd->print(m_direction == DispenserDirection::Forward ? "Forward" : "Reverse");
    }
    else if (m_currentMenu == 3)
    {
        m_lcd->print("3. Step Size");
        m_lcd->setCursor(0, 1);
        m_lcd->print(m_stepSize);
    }
    else if (m_currentMenu == 4)
    {
        m_lcd->print("4. Step Size");
        m_lcd->setCursor(0, 1);
        m_lcd->print(m_stepSize);
    }

    if (m_isEditing)
    {
        m_lcd->setCursor(0, 1);
    }
    else
    {
        m_lcd->setCursor(0, 0);
    }
}

void Menu::keyUp()
{
    if (m_isEditing)
    {
        if (m_currentMenu == 1)
        {
            m_mode = (DispenserMode)MAX(0, m_mode - 1);
        }
        else if (m_currentMenu == 2)
        {
            m_direction = (DispenserDirection)MAX(0, m_direction - 1);
        }
        else if (m_currentMenu == 3)
        {
            m_stepSize = MIN(1000, m_stepSize + 1);
        }
        else if (m_currentMenu == 3)
        {
            m_continuousSpeed = MIN(1000, m_continuousSpeed + 1);
        }
    }
    else
    {
        m_currentMenu = MAX(1, m_currentMenu - 1);
    }

    updateDisplay();
}

void Menu::keyDown()
{
    if (m_isEditing)
    {
        if (m_currentMenu == 1)
        {
            m_mode = (DispenserMode)MIN(DISPENSERMODE_LAST, m_mode + 1);
        }
        else if (m_currentMenu == 2)
        {
            m_direction = (DispenserDirection)MIN(DISPENSERDIRECTION_LAST, m_direction + 1);
        }
        else if (m_currentMenu == 3)
        {
            m_stepSize = MAX(0, m_stepSize - 1);
        }
        else if (m_currentMenu == 3)
        {
            m_continuousSpeed = MAX(0, m_continuousSpeed - 1);
        }
    }
    else
    {
        m_currentMenu = MIN(3, m_currentMenu + 1);
    }

    updateDisplay();
}

void Menu::keySelect()
{
    m_isEditing = !m_isEditing;

    updateDisplay();
}
