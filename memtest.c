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

void *my_memmove (unsigned char *dst, unsigned char *src, size_t n)
{
    int num = n;

    if ((dst == NULL) || (src == NULL) || (n == 0)) {
        printf("Invalid Parameters dst %p src %p size %d\n",
                dst, src, n);
        return NULL;
    }

    /*
     * In a wierd case of src == dst, nothing to do, just return dst as is
     */
    if (src == dst) {
        printf("Optimized for same source and destination\n");
        return dst;
    }
    
    
    /*
     * If the destination pointer falls between source and source + size
     * we will have an overlap. So better handle it. Else can do straight 
     * from source to destination.
     */
    if ((src < dst) && (dst < src + n)) {
        printf ("Overlap: Dest %p Src %p Size %d\n", dst, src, n);
        dst = dst + n - 1;   /* End of the buffer in Destination of n bytes */
        src = src + n - 1;   /* End of the source buffer upto n bytes       */
        while (n--) {
            printf("Dst %p Src %p Data 0x%x\n", dst, src, *src);
            *dst-- = *src--;
        }
        dst++;              /* Compensate for decrement that happend for last*/
                            /* byte copy                                     */
        printf("Overlap: Dst %p Src %p\n", dst, src);
        return dst;
    } else {
        printf ("NO Overlap: Dest %p Src %p Size %d\n", dst, src, n);
        while (n--) {
            printf("Dst %p Src %p Data 0x%x\n", dst, src, *src);
            *dst++ = *src++;
        }
        dst = dst - num;  /* In this case we are at the end              */ 
        printf("NO Overlap: Dst %p Src %p\n", dst, src);
        return dst;
    }
}


int main (int argc, char **argv)
{
    char   src[] =  "123456789abcdef";
    char   *dst;
    int    offset;
    int    size;

    printf("My Source String Data %s, Length %d\n", src, strlen(src));
    printf("Please select the destination offset within 0 & %d\n", 
                strlen(src));
    scanf("%d", &offset);
    printf("Please select the number of bytes to move within 0 & %d\n", 
                strlen(src) - offset);
    scanf("%d", &size);
    
    dst = my_memmove(&(src[0]) + offset, src, size);

    printf("memmoved: Dst %p Src %p\n", dst, src);
    printf("My Source String Data %s\n", src);
    printf("My Destination String Data %s\n", dst);
}
