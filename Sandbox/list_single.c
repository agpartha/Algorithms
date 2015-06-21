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

#include <limits.h>
#include <stdio.h>

#define DEBUG_PRINT
#ifdef DEBUG_PRINT
    #define DEBUG printf
#else  /* DEBUG_PRINT */
    #define DEBUG(...) ((void)0) 
#endif /* DEBUG_PRINT */


int main (int argc, char **argv)
{
    unsigned int value, temp, max_val, lbit, rbit, lmask, rmask;
    int      rotate;

    max_val = -1;
    rotate = CHAR_BIT * sizeof(value) - 1;
    rmask = 0x01;
    lmask = rmask << rotate;

    printf("\nPlease provide hex value to swap bits\n");
    scanf("0x%x", &value);
    printf("\nValue: 0x%x\n", value);

    DEBUG("bits in a byte %d, size of value %d, lmask 0x%x, rmask 0x%x, rotate %d\n",
           CHAR_BIT, sizeof(value), lmask, rmask, rotate);

    // Keep moving from left to right and right to left with masks and instead of count
    // when these masks align we are done with swapping.
    // OR when rotate count drops to 1 in this loop you can exit.
    // OR there are no more bits set [meaning some point in loop the remaining bits are zero 
    // to check we can use the condition after applying lmask to the current iteration value 
    // if it ends with zero and also when same is true for applying rmask, that menas there are 
    // no more bits left to swap.
    // Further if the values left are all 1s too we could stop by improvising above exit condition
    // to see if after applying the reverse of the lmask and rmask the remaining bits would
    // match ?
    while (lmask != (rmask >> 1)) {
        lbit = value & lmask;
        rbit = value & rmask;

        // Another optimization would be to see if the bits are same and avoid swapping.
        if ((!(lbit) && (rbit)) || (lbit) && !(rbit))  {
            DEBUG("left bit 0x%x right bit 0x%x\n", lbit, rbit);
        
            // Get the left most bit to move figured out and rotate right by the amount and 
            // and OR it with the right most bit to swap. 
            temp = ( ( lbit >> rotate) | (value & ~rmask)  
                                                        // Got the left bit in right position
                   );
            DEBUG("L->R: Value 0x%x, New Value 0x%x, rotate %d, lmask 0x%x, rmask 0x%x\n", 
                  value, temp, rotate, lmask, rmask);

            temp = (
                     (rbit << rotate) | (temp & ~lmask) 
                                                        // Got the right bit in left position
                   );
            DEBUG("R->L: Value 0x%x, New Value 0x%x, rotate %d, lmask 0x%x, rmask 0x%x\n", 
                    value, temp, rotate, lmask, rmask);
            // Move the value to be base for next iteration
            value = temp;
        } else {
            DEBUG("Skipping...\n");
        }

        // Adjust masks one bit towards each other
        lmask >>= 1;
        rmask <<= 1;


        // Since both masks are shifting one step towards each, rotate needed is twice less for 
        // next shift and OR operation
        rotate -= 2;

        // If remaining bits are zero break.
        // full 1s mask and with lmask and rmask will expose only bits in between.
        // value left and with this bit mask and if they are all zero can quit.
        // Also can consider same optim with remaining bits all as 1s.
        DEBUG("L mask and L mask -1 0x%x, lmask 0x%x, lmask -1 0x%x \n", 
              (lmask | (lmask - 1)), lmask, lmask - 1);
//        temp = max_val & ( lmask | (lmask - 1)); 
        temp &= (lmask | (lmask - 1)); 
                                    // clear the bits leading to lmasks.
        DEBUG("L+R Mask Left clear: 0x%x, lmask 0x%x\n", temp, lmask);

        DEBUG("R mask R mask -1 0x%x, rmask 0x%x \n", ~rmask, rmask);
//        DEBUG("R mask inv 0x%x, rmask 0x%x \n", ~rmask, rmask);
//        temp &= ((max_val & ~rmask) & ~(rmask - 1) | rmask); 
        temp &= ( ~(rmask | (rmask - 1)) | rmask ); 
        
        DEBUG("Masked value 0x%x, value 0x%x, mask 0x%x\n", value & temp, value, temp); 
        if ((value & temp) == 0)  {
            printf("All bits remaining to swap are zeroes.\n");
#if 1
            break;
#endif
        }
        if ((value & temp) == (max_val & temp)) {
            printf("All bits remaining to swap are 1s.\n");
#if 1
            break;
#endif
        }
        DEBUG("\n");

    }
    printf("\nBit Swapped Value: 0x%x, Rotate Position %d\n\n", value, rotate < 0 ? 0 : rotate);
}
