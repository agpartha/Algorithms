
#include <stdio.h>

typedef struct btest_{
    unsigned int drop:2;
    unsigned int if_index:6;
    unsigned int rest:24;
} btest_t;


int main (int argc, char **argv)
{

    unsigned int test_val = 0xAABBCCDD;
    btest_t      btest_val;
    unsigned int *tptr = (unsigned int *)&btest_val;

    *tptr = test_val;
    
    printf("drop %d(0x%x) if_index %d(0x%x) rest %d (0x%x)\n",
            btest_val.drop, btest_val.drop, btest_val.if_index, btest_val.if_index,
            btest_val.rest, btest_val.rest);
}
