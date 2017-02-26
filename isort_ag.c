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
 *				  to implement Insertion Sort with general interface.
 */

#include <stdio.h>
#include <errno.h>
#include "isort_ag.h"


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
 * the insertion sort function which operates on an array of data items.
 */
void    isort_ag (          
            void        *base_addr,   
            size_t      item_size,
            size_t      n_items,
            COMPARATOR  comp)
{
    int loop_count = 0;
    int i, j;
    void *temp_item;
    
    /*
     * idea here is to start a sorted array from left and progressively find 
     * the right place for the element just right of the sorted section in 
     * the sorted section.
     * Once you start at second element, one element array is already started.
     * after first two are compared and sorted, rest follows till all elements 
     * are inserted in place. In order to facilitate insertion, if the new element 
     * to be inserted it less than any earlier element, we start shifting the array 
     * sorted elements to right so that a space is created and once we hit the 
     * condition that satisfies the condition that inserted element is smaller than
     * the one to it's right, we insert it there. There is no swap needed anymore.
     * Important thing to note is this extra space is created by the place of the 
     * new element that potentially is going to move left [if it is smaller]
     */
    temp_item = malloc(item_size);
    for (i = 1; i < n_items; i++) {
        loop_count++;
        printf("\n%s(%d) L(%d):: current index %d n_items %d\n",
                __FUNCTION__, __LINE__, loop_count, i, n_items); 
        j = i;
        memcpy(temp_item, ITEM_N(base_addr, j, item_size), item_size);
        // Now go backwards and start shifting the elements to right if the 
        // new element is smaller than element in the sorted array. The loop
        // will not run if the last element [ j - 1 ] is already smaller saving
        // work.
        while ((j >= 1) && (comp(ITEM_N(base_addr, j - 1, item_size), temp_item) > 0)) {
            printf("\n%s(%d) L(%d):: shifting item at %d to %d\n",
                    __FUNCTION__, __LINE__, loop_count, j, j - 1); 
            memcpy(ITEM_N(base_addr, j, item_size), 
                   ITEM_N(base_addr, j - 1, item_size), item_size);
            j--;
        }
        // The point where loop stopped must be is the place where the new element 
        // needs to be inserted. The current element was already moved to the right.
        // Just copy the new element into this current index
        if (j != i) {
            memcpy(ITEM_N(base_addr, j, item_size),
                   temp_item, item_size);
            printf("\n%s(%d) L(%d):: new min item at %d moved to %d\n",
                __FUNCTION__, __LINE__, loop_count, i, j); 
        }
    } 
    printf("\n%s(%d) L(%d):: n_items %d\n",
                __FUNCTION__, __LINE__, loop_count, n_items); 
}

