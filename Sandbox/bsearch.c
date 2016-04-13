/*
 *
 ******************************************************************************* 
   The MIT License (MIT)
   Copyright (c) <2016> <Anand Girish>
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
#include <stdlib.h>


int comp_int (const void *a, const void *b)
{
		if (*((int *)a) == *((int *)b))
				return 0;
		else if (*((int *)a) < *((int *)b))
				return -1;
		return 1;
}

int b_search (int data[], int size, int val)
{
		static int recurs = 0;
		int s, m, e;

		s = 0;
		e = s + size - 1;
		m = (s + e) / 2 ;

		printf ("recurs(%d): start %d mid %d end %d, val %d\n", recurs, s, m, e, val);

		// check and return if we have the match
		if (data[m] == val) {
				return m;
		}

		// if we have atleast two elements to check...
		if (s < e) {
				// If data is less than mod, go search from left section
				// Cannot add if the index was negative still.
				if (val < data[m]) {
						int r;

						recurs++;
						r =  b_search(&data[s], (m - s), val);
						if (r >= 0)
								return s + r;
				}  

				// data must be greater than mid value and so look in the right side.
				if (val > data[m]) {
						int r;

						recurs++;
						r =  b_search(&data[m + 1], (e - m), val);
						if (r >= 0)
								return m + 1 + r;
				}  
		} 
		return -1;
}


void main (void)
{
		int data[] = { 10, 20, 30, 400, 533, 789, 1000, 2000, 2011};
		int i, val, size = sizeof(data)/sizeof(data[0]);

		while (1) {

				i = 0;
				while (i < size) {
						data[i] = data[i] + (rand() % 2321);
						i++;
				}

				qsort(data, sizeof(data)/sizeof(data[0]), sizeof(data[0]), comp_int);

				i = 0;
				while (i < size) {
						printf("Data[%2d] : %3d\n", i, data[i]);
						i++;
				}

				printf("\n\nPlease Enter the number to search in the above data ? \n");
				scanf("%d", &val);

				printf("\n\nSearching %d ....\n\n", val);

				i = b_search(data, size, val);

				if (i < 0)
						printf("\n\nCould not find %d ....\n\n", val);
				else 
						printf("\n\nFound %d at position %d\n\n", val, i);
		}
}
