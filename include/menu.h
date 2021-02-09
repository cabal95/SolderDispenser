#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal.h>

enum DispenserMode
{
    Step = 0,
    Continuous = 1
};
#define DISPENSERMODE_LAST 1

enum DispenserDirection
{
    Forward = 0,
    Backward = 1
};
#define DISPENSERDIRECTION_LAST 1

class Menu
{
private:
    LiquidCrystal *m_lcd;

    uint8_t m_currentMenu = 1;

    bool m_isEditing = false;

    DispenserMode m_mode = DispenserMode::Step;

    DispenserDirection m_direction = DispenserDirection::Forward;

    int16_t m_stepSize = 0;

    int16_t m_continuousSpeed = 0;

    void updateDisplay();

public:
    Menu(LiquidCrystal *lcd);

    DispenserMode getMode();

    DispenserDirection getDirection();

    uint16_t getStepSize();

    void keyUp();
    void keyDown();
    void keySelect();
};

#endif
