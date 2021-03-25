#include <Arduino.h>
#include <DRV8825.h>
#include "eventloop.h"
#include "timereventsource.h"
#include "buttoneventsource.h"
#include "ssd1306.h"
#include "fonts.h"
#include "menu.h"

#define MOTOR_MICROSTEP 4L
#define MOTOR_STEP_COUNT (200L * MOTOR_MICROSTEP)

#define BTN_RUN 2
#define BTN_UP 3
#define BTN_DOWN 4
#define BTN_SELECT 5
#define MOTOR_DIR 6
#define MOTOR_STEP 7

EventLoop mainLoop;
Ssd1306 ssd = Ssd1306(&Wire, 0x3c);
Menu menu;
DRV8825 stepper = DRV8825(200, MOTOR_DIR, MOTOR_STEP);

void toggleLed();
void btnRunPressed();
void btnRunReleased();
void btnUpPressed();
void btnDownPressed();

void setup()
{
    Serial.begin(9600);

    Wire.begin();
    ssd.begin();
    ssd.setFont(Font8x10, 8, 10);

    stepper.begin(1, MOTOR_MICROSTEP);

    menu.init(&ssd);

    ButtonEventSource *btnRun = new ButtonEventSource(BTN_RUN, false);
    btnRun->setPressedHandler(btnRunPressed);
    btnRun->setReleasedHandler(btnRunReleased);
    mainLoop.addEvent(btnRun);

    ButtonEventSource *btnUp = new ButtonEventSource(BTN_UP, false);
    btnUp->setPressedHandler(btnUpPressed);
    mainLoop.addEvent(btnUp);

    ButtonEventSource *btnDown = new ButtonEventSource(BTN_DOWN, false);
    btnDown->setPressedHandler(btnDownPressed);
    mainLoop.addEvent(btnDown);
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

void btnUpPressed()
{
    menu.keyUp();
}

void btnDownPressed()
{
    menu.keyDown();
}
