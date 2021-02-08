#include "menu.h"

Menu::Menu(LiquidCrystal *lcd)
{
    m_lcd = lcd;

    m_lcd->clear();
    m_lcd->print("Menu Ready");
}

void Menu::keyUp()
{
    m_lcd->setCursor(15, 1);
    m_lcd->print("U");
}

void Menu::keyDown()
{
    m_lcd->setCursor(15, 1);
    m_lcd->print("D");
}

void Menu::keySelect()
{
    m_lcd->setCursor(15, 1);
    m_lcd->print("S");
    m_lcd->setCursor(0, 0);
    m_lcd->cursor();
}
