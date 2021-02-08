#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal.h>

class Menu
{
private:
    LiquidCrystal *m_lcd;

public:
    Menu(LiquidCrystal *lcd);

    void keyUp();
    void keyDown();
    void keySelect();
};

#endif
