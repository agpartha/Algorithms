/*
 * Filename 	: dlist.h
 * HoweWork 2 	: Advanced Data Structures in C.
 * Author 		: Anand Girish 
 * Created		: Apr 17 1998
 * Description	: 
 *				  This file contains the prototype declarations of 
 *				  the API functions for the Doubly linked list implementation.
 */

/*
 * The container of the doubly linked list data structure. 
 */
typedef struct node {
			struct node	*next;
			struct node	*prev;
			void 		*data;
		}NODE;
		
/*
 * The List structure. The magic is used to validate the iterators which
 * operate on this list.
 */
typedef	struct list {
			struct node 	*head;
			size_t			item_size;
			unsigned long	magic;
		}LIST;


/*
 * The iterators are nothing but structures with a validated pointer to  
 * node in the list. These are used for sequential accesss into the list
 * and also we can have many of them operating on the same list.
 */
typedef struct {
			LIST		  *plist;		/* List we are associated with */	
			NODE		  *cur_node;	/* The node we are looking at  */
			unsigned long magic;		/* The magic number to match   */
										/* that of the List for 	   */
										/* validation of the iterator  */
		}ITERATOR;	


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


/* Initialize the list */
extern void init_list (LIST *l, size_t item_size);

/* Insert an item to the list */
extern int insert_list (LIST *l, void *new_item, COMPARATOR comp);

/* Search an item from the list */
extern void *lookup_list (LIST *l, void *srch_item, COMPARATOR comp);

/* Delete an item from the list */
extern int delete_list (LIST *l, void *srch_item, COMPARATOR comp);

/* 
 * Destroy the list -> Delete all items, free the storage, clear the 
 * List structure.
 */
extern void destroy_list (LIST *l);

/* Tester function for list empty */
extern int empty_list (LIST l); 

/*
 * Create the iterator. The magic number from the list is copied into
 * the iterator used for validation.
 */
extern ITERATOR *create_iterator (LIST *l);

/*
 * Check if this iterator is still valid by comparing the magic numbers.
 * If they are different the list is modified.
 */
extern int valid_iterator (ITERATOR *iter);

/* 
 * Return the next unread item in the list using this iterator. 
 */
extern void *next_item (ITERATOR *iter);

/* Destroy the iterator. */
extern void destroy_iterator (ITERATOR *iter);
 
 
