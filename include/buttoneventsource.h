#include "triggeredeventsource.h"
#include <stddef.h>
#include <stdint.h>

#ifndef BUTTONEVENTSOURCE_H
#define BUTTONEVENTSOURCE_H

/**
 * A button event that triggers when a pin state changes.
 */
class ButtonEventSource : public TriggeredEventSource
{
private:
    /**
     * The pin that is being used by this button.
     */
    uint16_t m_pin;

    /**
     * The debounce interval that is used to detect duplicate
     * state changes.
     */
    uint16_t m_debounceInterval;

    /**
     * Determines if a state of HIGH or LOW is what is treated as
     * a button press.
     */
    bool m_highIsPressed;

    /**
     * The currently tracked state of the button for debounce purposes.
     */
    bool m_currentState = false;

    /**
     * The last time we read the pin state.
     */
    uint64_t m_lastReadTime = 0;

    /**
     * The handler that will be called when the button is pressed.
     */
    void (*m_pressedHandler)() = NULL;

    /**
     * The handler that will be called when the button is released.
     */
    void (*m_releasedHandler)() = NULL;

protected:

public:
    /**
     * Initializes a new instance of the class.
     * 
     * @param pin The pin number that will be used for the button.
     */
    ButtonEventSource(int pin)
        : ButtonEventSource(pin, true) {}

    /**
     * Initializes a new instance of the class.
     * 
     * @param pin The pin number that will be used for the button.
     * @param highIsPressed True if the pin going high counts as a
     * button press, otherwise the pin going low will count as a
     * button press.
     */
    ButtonEventSource(int pin, bool highIsPressed)
        : ButtonEventSource(pin, 25, highIsPressed) {}

    /**
     * Initializes a new instance of the class.
     * 
     * @param pin The pin number that will be used for the button.
     * @param interval The number of milliseconds for the debounce delay.
     */
    ButtonEventSource(int pin, uint16_t interval)
        : ButtonEventSource(pin, 25, true) {}

    /**
     * Initializes a new instance of the class.
     * 
     * @param pin The pin number that will be used for the button.
     * @param interval The number of milliseconds for the debounce delay.
     * @param highIsPressed True if the pin going high counts as a
     * button press, otherwise the pin going low will count as a
     * button press.
     */
    ButtonEventSource(int pin, uint16_t interval, bool highIsPressed);

    /**
     * Sets the handler to be called when the button is pressed.
     * 
     * @param handler The handler to be called.
     */
    void setPressedHandler(void (*handler)());

    /**
     * Sets the handler to be called when the button is released.
     * 
     * @param handler The handler to be called.
     */
    void setReleasedHandler(void (*handler)());

    /**
     * Runs logic to determine if the event should be triggered. Overrides
     * should internally call setTriggered() if to trigger the event.
     */
    void checkEvent() override;

    /**
     * Executes the user-level event processing code.
     */
    void executeEvent();
};

#endif
