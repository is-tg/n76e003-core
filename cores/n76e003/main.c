#include <Arduino.h>
#include <N76E003.h>

void timer0_init(void);

int main(void)
{
        /* Enable all interrupt */
        EA = HIGH;
        timer0_init();

        setup();

        while (1)
        {
                loop();
        }
}
