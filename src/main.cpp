#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DRV8825.h>
#include "eventloop.h"
#include "timereventsource.h"
#include "buttoneventsource.h"
#include "menu.h"

#define MOTOR_MICROSTEP 4L
#define MOTOR_STEP_COUNT (200L * MOTOR_MICROSTEP)

#define BTN_RUN 2
#define BTN_UP 3
#define BTN_DOWN 4
#define BTN_SELECT 5
#define MOTOR_DIR 6
#define MOTOR_STEP 7

#define LCD_RS 14
#define LCD_EN 15
#define LCD_D4 16
#define LCD_D5 17
#define LCD_D6 18
#define LCD_D7 19

EventLoop mainLoop;
LiquidCrystal lcd = LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Menu menu;
DRV8825 stepper = DRV8825(200, MOTOR_DIR, MOTOR_STEP);

void toggleLed();
void btnRunPressed();
void btnRunReleased();

void setup()
{
    Serial.begin(9600);

    stepper.begin(1, MOTOR_MICROSTEP);

    lcd.begin(16, 2);
    menu.init(&lcd);

    ButtonEventSource *btnRun = new ButtonEventSource(BTN_RUN, false);
    btnRun->setPressedHandler(btnRunPressed);
    btnRun->setReleasedHandler(btnRunReleased);
    mainLoop.addEvent(btnRun);
}

void loop()
{
    stepper.nextAction();
    mainLoop.runOnce();

    if (Serial.available() > 0)
    {
        int c = Serial.read();

        if (c == 'u')
        {
            menu.keyUp();
            Serial.println("Up");
        }
        else if (c == 'd')
        {
            menu.keyDown();
        }
        else if (c == 's')
        {
            menu.keySelect();
        }
    }
}

void btnRunPressed()
{
    if (menu.getMode() == DispenserMode::Step)
    {
        int steps = menu.getStepSize();

        if (menu.getDirection() == DispenserDirection::Backward)
        {
            steps = -steps;
        }

        stepper.setRPM(60);
        stepper.startMove(steps);
    }
    else
    {
        long steps = 100 * MOTOR_STEP_COUNT;

        if (menu.getDirection() == DispenserDirection::Backward)
        {
            steps = -steps;
        }

        stepper.setRPM(menu.getDriveSpeed() / (float)MOTOR_STEP_COUNT * 60.0);
        stepper.startMove(steps);
    }
}

void btnRunReleased()
{
    if (menu.getMode() == DispenserMode::Drive)
    {
        stepper.stop();
    }
}
