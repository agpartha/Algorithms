/*
 *
 ******************************************************************************* 

   The MIT License (MIT)

   Copyright (c) <2015> <Anand Girish>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
 
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

 *******************************************************************************
 *
 */

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
