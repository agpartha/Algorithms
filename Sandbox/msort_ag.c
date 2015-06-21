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
 *				  This file contains the infrastructure routines
 *				  to implement Merge Sort with general interface.
 */

#include <stdio.h>
#include <errno.h>
#include "msort_ag.h"


/* Sort the array of data using Quick Sort algorithm & the
 * the comparartor function.
 */
void    msort_ag (
            void        *base_addr,
            size_t      item_size,
            size_t      n_items,
            COMPARATOR  comp)
{
    void *temp_addr = malloc (item_size * n_items);
    
    if (NULL == temp_addr) {
        printf ("Cannot alloc memory errno %d\n", errno);
        return;
    }
	rmsort_ag (base_addr, temp_addr, 0, n_items - 1, item_size, comp);
}

/*
 * The routine to swap the two items whose type is not known. 
 */
void swap_data (void *first_item, void *second_item, size_t item_size)
{
	void *temp;
	if (!(temp = (void *)malloc (item_size))) {
		printf ("Unrecoverable Error: No Memory..!!!\n");
		return;
	}
	memcpy (temp, first_item, item_size);
	memcpy (first_item, second_item, item_size);
	memcpy (second_item, temp, item_size);	
}


/*
 * The merge function where we marge two halfs of the array seperately fully sorted
 * but together not sorted.
 */
void merge_ag (void *base_addr, void *output_addr, int start, int end, int mid,
               size_t item_size, COMPARATOR  comp)
{
    int left, right, out_index;
      
    left = start;
    right = mid;
    out_index = left;

    /*
     * Compare the two halfs and get lowest item and output to output array.
     */
    while ( (left < mid) && (right <= end) ) {
        if (comp(ITEM_N(base_addr, left, item_size), 
                 ITEM_N(base_addr, right, item_size)) < 0) {
            memcpy(ITEM_N(output_addr, out_index, item_size), 
                   ITEM_N(base_addr, left, item_size), item_size);
            printf("%s(%d): left %d out_index %d\n", __FUNCTION__, __LINE__, 
                    left, out_index); 
            out_index++;
            left++;
         } else {
            memcpy(ITEM_N(output_addr, out_index, item_size), 
                   ITEM_N(base_addr, right, item_size), item_size);
            printf("%s(%d): right %d out_index %d\n", __FUNCTION__, __LINE__, 
                    right, out_index); 
            out_index++;
            right++;
        }
    }
        
    /*
     * We have taken items upto mid or half of the array into output with smallest of 
     * items in the first and second half combined. By that token all items in the 
     * first half are smaller than the remaining ones in the second half.
     * So just scoop the remaining items from the first half first and second half
     * next.
     * Start from the indices left wherever they are till mid for first half 
     * end for second half max.
     */
     while (left < mid) {
        memcpy(ITEM_N(output_addr, out_index, item_size), 
               ITEM_N(base_addr, left, item_size), item_size);
        printf("%s(%d): left %d out_index %d\n", __FUNCTION__, __LINE__, 
                left, out_index); 
        out_index++;
        left++;
     }
     while (right <= end) {
        memcpy(ITEM_N(output_addr, out_index, item_size), 
               ITEM_N(base_addr, right, item_size), item_size);
        printf("%s(%d): right %d out_index %d\n", __FUNCTION__, __LINE__, 
                right, out_index); 
        out_index++;
        right++;
     }

    /*
     * We now have to make sure the Input array has the merged data so that any
     * further calls to merge works on this one array. So copy back the temp array 
     * data back to input, again the range is start, end.
     */
    out_index = start;
    while (out_index <= end)  {
        printf("%s(%d): out_index %d\n", __FUNCTION__, __LINE__, 
                out_index); 
        memcpy(ITEM_N(base_addr, out_index, item_size),
               ITEM_N(output_addr, out_index, item_size), item_size);
        out_index++;
    }
}



/*
 * The mergesort function which operates on an array of data items.
 */
void rmsort_ag (void        *base_addr, void *output_addr, int start, int end, 
                size_t      item_size,
				COMPARATOR  comp)
{
    static int recurs_counter = 0;
     int recurs_count;
	int mid; 
	
    recurs_counter++;
    recurs_count = recurs_counter;
	/*
	 * In the recursive call sequence the indices can cross & that 
	 * situation is not a valid case anymore for partitioning & sorting.
	 */
	if (start < end) {

        mid = (start + end) / 2;
        printf("\n%s(%d) R(%d):: First Half : start %d, mid %d : end %d\n",
                __FUNCTION__, __LINE__, recurs_count, start, end, mid); 
        // Sort the first half  
        rmsort_ag (base_addr, output_addr, start, mid, item_size, comp); 
        // Sort the second half  
        printf("\n%s(%d) R(%d):: Second Half : (mid + 1) %d, end %d : start %d\n",
                __FUNCTION__, __LINE__, recurs_count, mid + 1, end, start); 
        rmsort_ag (base_addr, output_addr, mid + 1, end, item_size, comp);   
        // Merge both
        printf("\n%s(%d) R(%d):: Merge Halves : start %d end %d : mid %d\n",
                __FUNCTION__, __LINE__, recurs_count, start, end, mid); 
        merge_ag (base_addr, output_addr, start, end, mid + 1, item_size, comp); 
    } else {
        // Terminated recursion.
        recurs_counter = 0;
    }
}

