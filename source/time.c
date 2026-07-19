#include <Arduino.h>
#include <N76E003.h>

static volatile uint32_t timer0_overflow_count = 0;

void timer0_isr(void) __interrupt(1)
{
    timer0_overflow_count++;
}

void init(void)
{
    /* Set 16-bit timer mode for Timer0 */
    TMOD = (TMOD & 0xF0) | 0x01;

    /* Ensure Fosc/12 mode for Timer0 */
    CKCON &= ~(1 << 3);

    /* Reset Timer0 */
    TL0 = 0;
    TH0 = 0;

    /* Enable Timer0 interrupt and global interrupts */
    ET0 = HIGH;
    EA = HIGH;

    /* Start Timer0 */
    TR0 = HIGH;
}

uint32_t micros(void)
{
    uint8_t high, low;
    uint16_t timer;
    uint32_t overflows;

    EA = LOW;

    overflows = timer0_overflow_count;

    /* Handle TL0 overflow */
    do
    {
        high = TH0;
        low = TL0;
    } while (high != TH0);

    /* Handle timer overflow */
    if (TF0 == 1 && high < 128)
    {
        overflows++;
    }

    EA = HIGH;

    timer = ((uint16_t)high << 8) | low;

    /* 65536 ticks/overflow, 0.75 us/tick */
    return ((overflows * 65536UL) + timer) * 3UL / 4UL;
}

void delay(uint32_t ms)
{
    uint32_t start = micros();

    while ((micros() - start) < ms * 1000UL)
        ;
}
