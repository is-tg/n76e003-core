#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>

enum
{
    LOW,
    HIGH
};

enum
{
    INPUT,            /* Input-only          */
    OUTPUT,           /* Push-pull           */
    INPUT_PULLUP,     /* Quasi-bidirectional */
    OUTPUT_OPENDRAIN, /* Open-drain          */
};

/* Active low LED */
#define LED_BUILTIN 10

void setup(void);
void loop(void);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

void delay(uint32_t ms);

#endif
