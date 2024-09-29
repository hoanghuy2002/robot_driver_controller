#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t test = 7;
    uint8_t data = test%4*8+4;
    printf("%d",data);
}