#include <Arduino.h>
#include "buttoneventsource.h"

/**
 * Initializes a new instance of the class.
 * 
 * @param pin The pin number that will be used for the button.
 * @param interval The number of milliseconds for the debounce delay.
 * @param highIsPressed True if the pin going high counts as a
 * button press, otherwise the pin going low will count as a
 * button press.
 */
ButtonEventSource::ButtonEventSource(int pin, uint16_t interval, bool highIsPressed)
{
    m_pin = pin;
    m_debounceInterval = interval;
    m_highIsPressed = highIsPressed;

    if (m_highIsPressed)
    {
        pinMode(m_pin, INPUT);
    }
    else
    {
        pinMode(m_pin, INPUT_PULLUP);
    }
}

/**
 * Sets the handler to be called when the button is pressed.
 * 
 * @param handler The handler to be called.
 */
void ButtonEventSource::setPressedHandler(void (*handler)())
{
    m_pressedHandler = handler;
}

/**
 * Sets the handler to be called when the button is released.
 * 
 * @param handler The handler to be called.
 */
void ButtonEventSource::setReleasedHandler(void (*handler)())
{
    m_releasedHandler = handler;
}

/**
 * Runs logic to determine if the event should be triggered. Overrides
 * should internally call setTriggered() if to trigger the event.
 */
void ButtonEventSource::checkEvent()
{
    uint64_t current_millis = millis();

    if (current_millis - m_lastReadTime > m_debounceInterval)
    {
        m_lastReadTime = current_millis;
        bool state = m_highIsPressed ? digitalRead(m_pin) == HIGH : digitalRead(m_pin) == LOW;

        if (m_currentState != state)
        {
            m_currentState = state;

            setTriggered();
        }
    }
}

/**
 * Executes the user-level event processing code.
 */
void ButtonEventSource::executeEvent()
{
    if (m_currentState && m_pressedHandler != NULL)
    {
        m_pressedHandler();
    }
    else if (!m_currentState && m_releasedHandler != NULL)
    {
        m_releasedHandler();
    }
}
