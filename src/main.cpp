#include <Arduino.h>
#include <LiquidCrystal.h>
#include "eventloop.h"
#include "timereventsource.h"
#include "buttoneventsource.h"
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

void toggleLed();
void buttonPressed();
void buttonReleased();

void setup()
{
    Serial.begin(9600);

    LiquidCrystal *lcd = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    lcd->begin(16, 2);
    menu = new Menu(lcd);

    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_EXT, OUTPUT);

    ButtonEventSource *btn = new ButtonEventSource(BTN, false);
    btn->setPressedHandler(buttonPressed);
    btn->setReleasedHandler(buttonReleased);
    mainLoop.addEvent(new TimerEventSource(1000, toggleLed));
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

void toggleLed()
{
    bool ledState = digitalRead(LED_BUILTIN) == HIGH ? LOW : HIGH;
    digitalWrite(LED_BUILTIN, ledState);
}

void buttonPressed()
{
    digitalWrite(LED_EXT, HIGH);
    btnCount += 1;

    Serial.println("Button Pressed");
}

void buttonReleased()
{
    digitalWrite(LED_EXT, LOW);

    Serial.println("Button Released");
}
