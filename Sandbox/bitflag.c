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
#include <string.h>
#include <stdlib.h>


unsigned long  n_dsl       = 75;
unsigned long  n_bytes     = 0;

void set_bit(char *bit_flag, unsigned long value)
{
  /*
   * Get the byte number & the bit position in the byte
   * for this value. 
   */
   bit_flag  += (value % n_dsl)/ 8;
   *bit_flag |= (0x1 << (value % 8));
}


void clear_bit(char *bit_flag, unsigned long value)
{
  /*
   * Get the byte number & the bit position in the byte
   * for this value. 
   */
   bit_flag  += (value % n_dsl)/ 8;
   *bit_flag &= ~(0x1 << (value % 8));
}

void set_n_bits(char *bit_flag, unsigned long n_bits)
{
	if (n_bits > 8) {
		memset (bit_flag, 0xFF, n_bits / 8);
		*(bit_flag + n_bits/8) = (0xFF >> (8 - (n_bits % 8)));
	}
}



int test_bit(char *bit_flag, unsigned long value)
{
  /*
   * Get the byte number & the bit position in the byte
   * for this value. 
   */
   bit_flag  += (value % n_dsl)/ 8;
   return(*bit_flag & (0x1 << (value % 8)));
}

void show_bits(char *bit_flag, unsigned long n_bits)
{
   unsigned long bit_cnt = 0;
   unsigned char mask = 0x01;
   unsigned long ban_min, ban_max;

   if (n_bits == 1)  {
      printf("\nDSL  0\n%d \n", *bit_flag & 0x01);
      return;
   }

   ban_max = (n_bits > 32) ? 31: n_bits - 1;
   printf ("\nDSL  0 --> %lu\n", ban_max);

   while (bit_cnt < n_bits) {
      printf("%d ", (*bit_flag & mask)  ? 1:0);
      bit_cnt++;
      mask <<= 1;
      if (!(bit_cnt % 8)) { 
         bit_flag++; 
         mask = 0x01;
         printf (" ");
      }
      if (!(bit_cnt % 32))  { 
        if (n_bits > bit_cnt) {
           ban_min = bit_cnt;
           ban_max = (bit_cnt + 32) > n_bits ? n_bits - 1: (bit_cnt + 31);
           printf ("\nDSL %lu --> %lu\n", ban_min, ban_max);
        } else 
           printf ("\n");
      }
   }
   if (bit_cnt % 32) 
      printf ("\n");
}

int any_bit_set (unsigned char *dbg_flag, size_t n_bytes)
{
    while (n_bytes--)
       if (*dbg_flag++)
          return 1;
    return 0;
}


int main (void)
{
  unsigned char *bit_flag    = NULL;
  unsigned long  n_dsl       = 75;

  /*
   * Get enough bytes to hold all the bits of the num_dsl.
   */
  n_bytes = (n_dsl + 7)/8;
  bit_flag = (char *)malloc(n_bytes); 
  if (bit_flag) 
     memset(bit_flag, 0, n_bytes);
  else 
     return -1;
 
  /*
   * Set a few bit positions randomly to test the bits.
   */
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  set_bit(bit_flag, 0);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  set_bit(bit_flag, 9);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  set_bit(bit_flag, 13);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  set_bit(bit_flag, 73);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  show_bits(bit_flag, 1);
  show_bits(bit_flag, n_dsl);
  show_bits(bit_flag, 72);
  clear_bit(bit_flag, 0);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  clear_bit(bit_flag, 9);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  clear_bit(bit_flag, 13);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
  clear_bit(bit_flag, 73);
  printf("Bit 0 %d 9 %d 13 %d 73 %d\n",
          test_bit(bit_flag, 0), 
          test_bit(bit_flag, 9), 
          test_bit(bit_flag, 13), 
          test_bit(bit_flag, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_flag, n_bytes));
	
  memset (bit_flag, 0, n_bytes);
  set_n_bits (bit_flag, n_dsl);	
  printf("dsl 73 bit set ? %d\n", test_bit(bit_flag, 73));
  printf("dsl 74 bit set ? %d\n", test_bit(bit_flag, 74));
  printf("dsl 75 bit set ? %d\n", test_bit(bit_flag, 75));
  printf("dsl 76 bit set ? %d\n", test_bit(bit_flag, 76));
  printf("dsl 77 bit set ? %d\n", test_bit(bit_flag, 77));
  printf("dsl 78 bit set ? %d\n", test_bit(bit_flag, 78));
  printf("dsl 79 bit set ? %d\n", test_bit(bit_flag, 79));
  printf("dsl 80 bit set ? %d\n", test_bit(bit_flag, 80));
}

