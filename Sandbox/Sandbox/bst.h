/*
 * Filename 	: bst.h
 * HoweWork 7 	: Advanced Data Structures in C.
 * Author 		: Anand Girish 
 * Created		: June 20 1998
 * Description	: 
 *				  This file contains the prototype declarations for 
 *				  the API functions for the Binary search tree 
 * 				  implementation.
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
 

typedef	struct node{
				struct node	*left;		/* Left subtree		*/
				struct node	*right;		/* Right subtree 	*/
				void		*data;		/* Ptr to data 		*/
			   }NODE;


typedef struct {
				NODE		*root;		/* Root of the tree 		*/
				size_t		data_size;	/* data size in bytes		*/
				COMPARATOR	order_func;	/* Determines linear order	*/	
				}BINARY_SEARCH_TREE;

/*
 * The following are the API functions to be used by the binary 
 * search tree application. 
 * The code for the API will implement the Binary search tree.
 *
 * All functions return 0 for failure & 1 for success. If returning
 * pointers will return a valid pointer or NULL.
 *
 */
/*
 * Initialise the binary search tree. Make root empty. 
 */
int		create_bst	(BINARY_SEARCH_TREE *, size_t, 
						COMPARATOR);

/* Insert an item to Binary Search Tree. */
int		insert_bst	(BINARY_SEARCH_TREE  *, void *);

/* Find an item in the  Binary Search Tree. */
void 	*lookup_bst	(BINARY_SEARCH_TREE  *, void *);

/* Delete an item from the Binary Search Tree. */
int 	delete_bst	(BINARY_SEARCH_TREE *, void *);

/* Display the Binary Search Tree in the infix order */
void	display_bst	(BINARY_SEARCH_TREE *, void (*)(void *));


