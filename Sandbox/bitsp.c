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
#include <stddef.h>
#include <arpa/inet.h>

typedef struct btest_{
    uint32_t drop:2;
    uint32_t if_index:6;
    uint32_t rest:24;
} btest_t;


int main (int argc, char **argv)
{

    uint32_t test_val = htonl(0xAABBCCDD);
    btest_t      btest_val;
    uint32_t *tptr = (uint32_t *)&btest_val;

    *tptr = test_val;
    
    printf("uint32_t %u (0x%x) drop %d(0x%x) if_index %d(0x%x) rest %d (0x%x)\n",
	    *tptr, test_val,
            btest_val.drop, btest_val.drop, btest_val.if_index, btest_val.if_index,
            btest_val.rest, btest_val.rest);
}
