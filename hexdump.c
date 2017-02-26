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

#include <ctype.h>
#include <stdio.h>

void hexdump(void *ptr, int buflen) {
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;

    // Loop 16 bytes at a time
    for (i = 0; i < buflen; i += 16) {
        // The Address or the offset
        printf("%06x: ", i);
        // Each byte of the row
        for (j = 0; j < 16; j++) 
            // If row is short of full 16 bytes
            if ((i + j) < buflen)
                printf("%02x ", buf[i + j]);
            else
                printf("   ");
        // Column Seperator
        printf(" ");
        // Consolidated printable character dump
        for (j = 0; j < 16; j++) 
            if ((i + j) < buflen)
                printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
        // Next Row Seperator
        printf("\n");
  }
}

int main (int argc, char **argv)
{
    unsigned char data[32] = {'A'};

    data[0] = 0;
    data[1] = 1;
    data[2] = 'A';
    data[3] = 'U';
    data[4] = 'K';
    data[5] = 'I';
    data[6] = 'N';
    data[7] = ' ';

    hexdump(data, sizeof(data));
    
    return 0;
}
