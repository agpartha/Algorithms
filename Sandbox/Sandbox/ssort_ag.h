/*
 * Filename 	: ssort.h
 * Author 		: Anand Girish 
 * Created		: Mar 22 2014
 * Description	: 
 *				  This file contains the prototype declarations for 
 *				  the API functions for the Selection Sort Implementation.
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
void	ssort_ag (	
			void 		*base_addr,		
			size_t		item_size,		
			size_t		n_items,
			COMPARATOR	c);

#define sort_ag(input, item_size, n_items, comp)  ssort_ag((input), (item_size), (n_items), (comp))
