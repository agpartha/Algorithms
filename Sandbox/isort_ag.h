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
 *				  This file contains the prototype declarations for 
 *				  the API functions for the Insertion Sort Implementation.
 */

/*
 * comparator function is needed for insertion, lookup functions & always
 * follows the following rules.
 *
 * comp_result = comp(ptr_to_item_in_list, ptr_to_search_item);
 * and
 * comp_result will be
 *
 * -1 if the first argument is smaller
 *  0 if both are equal
 * +1 if the first argument is larger
 */
typedef int (*COMPARATOR)(void *, void *);


/*
 * This macro helps in reduced clutter for coding pointer 
 * arithmetic used in sequential access of the array of 
 * generic item_size.
 * start_addr + nth_item * item_size is the formula.
 */
#define	ITEM_N(x, y, z)	((char *)(x) + (y) * (z))

/* Sort the array of data using Bubble Sort routine & the
 * the comparartor function.
 */
void	isort_ag (	
			void 		*base_addr,		
			size_t		item_size,		
			size_t		n_items,
			COMPARATOR	c);

#define sort_ag(input, item_size, n_items, comp)  isort_ag((input), (item_size), (n_items), (comp))
