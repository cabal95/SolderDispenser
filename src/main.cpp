#include <Arduino.h>
#include <LiquidCrystal.h>
#include "eventloop.h"
#include "timerevent.h"
#include "button.h"
#include "menu.h"

#define LED_EXT 2
#define BTN 3

#define LCD_RS 14
#define LCD_EN 15
#define LCD_D4 16
#define LCD_D5 17
#define LCD_D6 18
#define LCD_D7 19

Menu *menu;
EventLoop mainLoop;
int btnCount = 0;

void buttonPressed(Button *button)
{
    digitalWrite(LED_EXT, HIGH);
    btnCount += 1;

    Serial.println("Button Pressed");
}

void buttonReleased(Button *button);
bool ledState = false;

void setup()
{
    Serial.begin(9600);

    LiquidCrystal *lcd = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    lcd->begin(16, 2);
    menu = new Menu(lcd);

    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_EXT, OUTPUT);

    Button *btn = new Button(BTN, false);
    btn->setPressedHandler(buttonPressed);
    btn->setReleasedHandler(buttonReleased);
    mainLoop.addEvent(new TimerEvent(1000, [] {
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
    }));
    mainLoop.addEvent(btn);
}

void loop()
{
    mainLoop.runOnce();

    if (Serial.available() > 0)
    {
        int c = Serial.read();

        if (c == 'u')
        {
            menu->keyUp();
            Serial.println("Up");
        }
        else if (c == 'd')
        {
            menu->keyDown();
        }
        else if (c == 's')
        {
            menu->keySelect();
        }
    }
}

void buttonReleased(Button *button)
{
    digitalWrite(LED_EXT, LOW);

    Serial.println("Button Released");
}
