#include <Arduino.h>
#include <N76E003.h>

#define FSYS 16000000UL

/* Bytes available to read */
volatile uint8_t serialAvailable = 0;
/* Bytes available to write */
volatile uint8_t serialAvailableForWrite = 1;

void uart0_isr(void) __interrupt(INT_UART0)
{
        /* Data frame received */
        if (RI)
        {
                serialAvailable = 1;
                RI = 0;
        }
        /* Data frame trasmitted */
        if (TI)
        {
                serialAvailableForWrite = 1;
                TI = 0;
        }
}

void serialBegin(uint32_t baud, uint8_t smod)
{
        /* Set port latch bits */
        TXD = 1;
        RXD = 1;

        /* TXD push-pull */
        P0M1 &= ~0x40;
        P0M2 |= 0x40;

        /* Set Timer 1 mode to 8bit auto-reload */
        TMOD &= ~0x10;
        TMOD |= 0x20;

        /* Use system clock directly */
        CKCON |= 0x10;

        if (smod)
        {
                /* Double baud rate */
                PCON |= 0x80;
        }

        /* Table 13-3. UART Baud Rate Formulas */
        TH1 = TL1 = 256 - FSYS * (1 + smod) / 32 / baud;

        /* UART mode 1 */
        SM0 = 0;
        SM1 = 1;

        /* Receiving enable */
        REN = 1;

        /* Clear flags */
        RI = 0;
        TI = 0;

        /* Enable serial port 0 interrupt */
        ES = 1;

        /* Start Timer 1 */
        TR1 = 1;
}

uint8_t serialRead(void)
{
        serialAvailable = 0;
        return SBUF;
}

void serialWrite(uint8_t buf)
{
        SBUF = buf;
        serialAvailableForWrite = 0;
}
