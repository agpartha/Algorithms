
#include <stdio.h>

int main (int argc, char **argv)
{
    int var32 = 0;

    var32 = 0xffed91;
    printf("Integer as read 24-bit value in  32 bit register 0x%x %d\n", 
                            var32, var32);
    if (var32 & 0x100000) {
        var32 |= 0xFF000000;
        printf("Negative number is 0x%x %d\n", var32, var32);
    } else {
        printf("Positive number is 0x%x %d", var32, var32);
    }
}
