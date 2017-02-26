
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

/*
 * description	: 
 *				  this file contains the infrastructure routines
 *				  to implement Selection Sort with general interface.
 */

#include <stdio.h>
#include <errno.h>
#include "ssort_ag.h"


/*
 * the routine to swap the two items whose type is not known. 
 */
void swap_data (void *first_item, void *second_item, size_t item_size)
{
	void *temp;
	if (!(temp = (void *)malloc (item_size))) {
		printf ("unrecoverable error: no memory..!!!\n");
		return;
	}
	memcpy (temp, first_item, item_size);
	memcpy (first_item, second_item, item_size);
	memcpy (second_item, temp, item_size);	
}



/*
 * the mergesort function which operates on an array of data items.
 */
void    ssort_ag (          
            void        *base_addr,   
            size_t      item_size,
            size_t      n_items,
            COMPARATOR  comp)
{
    int loop_count = 0;
    int end_index = n_items - 1;
    int i, j, min_index;
    
    /*
     * idea here is to find the smallest element and move it to ahead of the list.
     * Progressively move down the list leaving the elements from first one.
     * After next small one is put in place, start the search from remaining items
     * [3 + till end of the list].
     * the key here is that after first run, smallest element is the first one.
     * further loops should only run from second and third...etc.
     */
    for (i = 0; i <= end_index; i++) {
        loop_count++;
        printf("\n%s(%d) L(%d):: current index %d end_index %d, n_items %d\n",
                __FUNCTION__, __LINE__, loop_count, i, end_index, n_items); 
        min_index = i; 
        // find the smallest and swap it with the element at i
        for (j = i; j <= end_index; j++) {
            if (comp(ITEM_N(base_addr, j, item_size),
                 ITEM_N(base_addr, min_index, item_size)) < 0) {
                printf("\n%s(%d) L(%d):: new min item at %d current min item at %d\n",
                __FUNCTION__, __LINE__, loop_count, j, min_index); 
                min_index = j;
            }
        }
        swap_data(ITEM_N(base_addr, min_index, item_size),
                       ITEM_N(base_addr, i, item_size), item_size);
        printf("\n%s(%d) L(%d):: new min item at %d moved to %d\n",
                __FUNCTION__, __LINE__, loop_count, min_index, i); 
    } 
    printf("\n%s(%d) L(%d):: end_index %d, n_items %d\n",
                __FUNCTION__, __LINE__, loop_count, end_index, n_items); 
}

