#include <Arduino.h>
#include <N76E003.h>

#define MODE_QUASI 0b00
#define MODE_PUSHPULL 0b01
#define MODE_INPUT 0b10
#define MODE_OPENDRAIN 0b11

void pinMode(uint8_t pin, uint8_t mode)
{
        uint8_t bitmask = (1u << (pin & 7));

        uint8_t pin_mode;
        switch (mode)
        {
        case INPUT:
                pin_mode = MODE_INPUT;
                break;
        case OUTPUT:
                pin_mode = MODE_PUSHPULL;
                break;
        case INPUT_PULLUP:
                pin_mode = MODE_QUASI;
                break;
        case OUTPUT_OPENDRAIN:
                pin_mode = MODE_OPENDRAIN;
                break;
        default:
                return;
        }

        if (pin < 8)
        {
                (pin_mode & 0b10) ? (P0M1 |= bitmask) : (P0M1 &= ~bitmask);
                (pin_mode & 0b01) ? (P0M2 |= bitmask) : (P0M2 &= ~bitmask);
        }
        else if (pin < 16)
        {
                (pin_mode & 0b10) ? (P1M1 |= bitmask) : (P1M1 &= ~bitmask);
                (pin_mode & 0b01) ? (P1M2 |= bitmask) : (P1M2 &= ~bitmask);
        }
}

void digitalWrite(uint8_t pin, uint8_t value)
{
        uint8_t bitmask = (1u << (pin & 7));

        if (pin < 8)
        {
                if (value)
                        P0 |= bitmask;
                else
                        P0 &= ~bitmask;
        }
        else if (pin < 16)
        {
                if (value)
                        P1 |= bitmask;
                else
                        P1 &= ~bitmask;
        }
}

int digitalRead(uint8_t pin)
{
        uint8_t bitmask = (1u << (pin & 7));

        if (pin < 8)
        {
                return (P0 & bitmask) ? HIGH : LOW;
        }
        else if (pin < 16)
        {
                return (P1 & bitmask) ? HIGH : LOW;
        }

        return LOW;
}
