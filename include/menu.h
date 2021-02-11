#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal.h>

/**
 * The mode the dispenser motor should operate in.
 */
enum DispenserMode
{
    /**
     * Each button press will move the motor a set number of
     * steps.
     */
    Step = 0,

    /**
     * While the button is pressed, the motor will move a set
     * number of steps per second.
     */
    Drive = 1
};
#define DISPENSERMODE_LAST 1

/**
 * The direction the motor will move the plunger.
 */
enum DispenserDirection
{
    /**
     * The plunger will move forward further into the dispenser.
     */
    Forward = 0,

    /**
     * The plunger will back out of the dispenser.
     */
    Backward = 1
};
#define DISPENSERDIRECTION_LAST 1

/**
 * Displays a menu for the user to use in configuring the device.
 */
class Menu
{
private:
    /**
     * The LCD display to use when interacting with the user.
     */
    LiquidCrystal *m_lcd;

    /**
     * The current menu item being displayed.
     */
    uint8_t m_currentMenu = 1;

    /**
     * Whether we are currently editing a value or not.
     */
    bool m_isEditing = false;

    /**
     * Settings sub-menu mode currently being displayed.
     */
    uint8_t m_settingsMode = 0;

    /**
     * The current dispenser mode.
     */
    DispenserMode m_mode = DispenserMode::Step;

    /**
     * The current direction of the dispenser.
     */
    DispenserDirection m_direction = DispenserDirection::Forward;

    /**
     * The number of steps to move on each button press in Step mode.
     */
    uint16_t m_stepSize = 0;

    /**
     * The number of steps to move per second while the button is
     * depressed in Drive mode.
     */
    uint16_t m_driveSpeed = 0;

    /**
     * Reset the current values to sane defaults.
     */
    void resetValues();

    /**
     * Load the values from EEPROM.
     */
    void loadValues();

    /**
     * Save the current values into EEPROM.
     */
    void saveValues();

    /**
     * Update the display to reflect what should be in screen.
     */
    void updateDisplay();

public:
    /**
     * Initializes the menu for use.
     * 
     * @param lcd The LCD object to display information on.
     */
    void init(LiquidCrystal *lcd);

    /**
     * Gets the current DispenserMode to operate in.
     */
    DispenserMode getMode();

    /**
     * Gets the current direction to move the plunger.
     */
    DispenserDirection getDirection();

    /**
     * Gets the number of steps to move in Step mode.
     */
    uint16_t getStepSize();

    /**
     * Gets the number of steps per second to move in Drive mode.
     */
    uint16_t getDriveSpeed();

    /**
     * Signal that the UP key has been pressed.
     */
    void keyUp();

    /**
     * Signal that the DOWN key has been pressed.
     */
    void keyDown();

    /**
     * Signal that the SELECT key has been pressed.
     */
    void keySelect();
};

#endif
