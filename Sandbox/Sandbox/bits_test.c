
#include <stdio.h>

int bitcnt (unsigned int a)
{
    int count = 0;
    int loop = 0;

    while (a) {
        loop++;
        count += (a & 0x01u);
        a >>= 1;
    }
    printf ("%s:   Loop count: %d\n", __FUNCTION__, loop);
    return count;
}

int bitcnt_e (unsigned int a) 
{
    int count = 0;
    int loop = 0;

    while (a) {
        loop++;
        count++;
        a = a & (a - 1);    /* Sets the most right bit to 1 */
    }
    printf ("%s:   Loop count: %d\n", __FUNCTION__, loop);
    return count;
}

int bitcnt_f (unsigned int a)
{
    int count = sizeof(a) * 8;
    int loop = 0;
    
#ifdef ALTERNATE_COMPLEMENT_METHOD
    printf("%s:  Value: 0x%x  Complement with -1: 0x%x\n",
            __FUNCTION__, a, (a ^ ((unsigned int) -1)));
    a ^= (unsigned int) -1; /* Should give us complement of bits */
#else  /* ALTERNATE_COMPLEMENT_METHOD */
    printf("%s:  Value: 0x%x  Complement with Negation: 0x%x\n",
            __FUNCTION__, a, ~a);
    a = ~a;
#endif /* ALTERNATE_COMPLEMENT_METHOD */
    while (a) {
        loop++;
        count--;    /* Reduce 1 for each 0 which is now a 1 due to negation */
        a &= (a - 1);
    }
    printf ("%s:   Loop count: %d\n", __FUNCTION__, loop);
    return count;
}

int main (int argc, char **argv)
{
    int value;

    printf("Please provide a integer for bit count test : \n");
    scanf("0x%x", &value);

    printf("Value 0x%x Bit Count %d\n", value, bitcnt(value)); 
    printf("Value 0x%x Bit Count %d\n", value, bitcnt_e(value)); 
    printf("Value 0x%x Bit Count %d\n", value, bitcnt_f(value)); 
}
