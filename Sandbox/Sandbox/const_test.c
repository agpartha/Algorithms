#include <stdio.h>

int main (int argc, char **argv)
{
    
    const char string_test[] = "Hello World";
    char *p = string_test;

    printf("String: %s Length %d\n", p, strlen(string_test));
    
    *p = 'Y';

    printf("String: %s Length %d\n", p, strlen(string_test));
    
    p = string_test+1;

    *p = 'T';

    printf("String: %s Length %d\n", p, strlen(string_test));
    
}
