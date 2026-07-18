#include <Arduino.h>

void init(void);

int main(void)
{
    init();
    setup();

    while (1)
    {
        loop();
    }
}
