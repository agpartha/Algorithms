
#include <stdio.h>


int test_even (int a)
{
    return ((a % 2) == 0);
}

int main (int argc, char **argv)
{
    int a = 11;
    int (*fn_ptr)(int a) = NULL;

    fn_ptr = test_even;

    printf("Value %d, Result %s\n", a, fn_ptr(a) ? "Even":"Odd");
}
