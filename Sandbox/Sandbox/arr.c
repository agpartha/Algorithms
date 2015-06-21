
#include <stdio.h>

int arr3[10][2][16];

typedef int uniarr[2][16];

int main (void)
{
    uniarr     *dev_uniarr1;
    uniarr     *dev_uniarr2[2];

    dev_uniarr1   = &(arr3[0]);
    dev_uniarr2[0] = &(arr3[0]);
    dev_uniarr2[1] = &(arr3[1]);
    printf("Hello World\n");
}
