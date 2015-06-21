/*
 * filename 	: bsort_ag.c
 * author 		: anand girish 
 * created		: mar 22 2014
 * description	: 
 *				  this file contains the infrastructure routines
 *				  to implement bubble sort with general interface.
 */

#include <stdio.h>
#include <errno.h>
#include "bsort_ag.h"


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
void    bsort_ag (          
            void        *base_addr,   
            size_t      item_size,
            size_t      n_items,
            COMPARATOR  comp)
{
    int loop_count = 0;
    int end_index = n_items - 1;
    int swap_done;
    int i;
    
    /*
     * idea here is to move the largest value to the right succesively and 
     * after all n items are done, the array should have it sorted.
     * the key here is that after first run, highest element is the last one.
     * further loops should inly run till last but one and last but two...etc.
     * instead of looping for all n items, if there were no swap done in one iteration 
     * we can terminate the loop.
     */
    do {
        swap_done = 0;
        loop_count++;
        printf("\n%s(%d) L(%d):: end_index %d, n_items %d\n",
                __FUNCTION__, __LINE__, loop_count, end_index, n_items); 
        for (i = 0; i < end_index; i++) {
            if (comp(ITEM_N(base_addr, i, item_size),
                 ITEM_N(base_addr, i + 1, item_size)) > 0) {
                printf("\n%s(%d) L(%d):: swapping item at %d with %d\n",
                __FUNCTION__, __LINE__, loop_count, i, i + 1); 
                swap_data(ITEM_N(base_addr, i, item_size),
                       ITEM_N(base_addr, i + 1, item_size), item_size);
                swap_done = 1;
            }
        }
    } while (swap_done && (--end_index));
    printf("\n%s(%d) L(%d):: end_index %d, n_items %d\n",
                __FUNCTION__, __LINE__, loop_count, end_index, n_items); 
}

