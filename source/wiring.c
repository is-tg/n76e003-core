#include <Arduino.h>
#include <N76E003.h>

static volatile uint32_t timer0_overflow_count = 0;

void timer0_isr(void) __interrupt(1)
{
    timer0_overflow_count++;
}

uint32_t micros(void)
{
    uint16_t timer;
    uint32_t overflows;

    TR0 = LOW;
    EA = LOW;

    overflows = timer0_overflow_count;
    timer = ((uint16_t)TH0 << 8) | TL0;

    EA = HIGH;
    TR0 = HIGH;

    return ((overflows * 65536UL) + timer) * 3UL / 4UL;
}

void delay(uint32_t ms)
{
    uint32_t start = micros();

    while ((micros() - start) < ms * 1000UL)
        ;
}
