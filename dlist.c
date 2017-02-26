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
 *				  to implement doubly linked list.
 */

#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"


/* Initialize the list */
void init_list (LIST *l, size_t item_size)
{
	l->head 	 = NULL;
	l->item_size = item_size;
	l->magic	 = 1;
}

/* Insert an item to the list */
int insert_list (LIST *l, void *new_item, COMPARATOR comp)
{
	NODE	*new_node;

	/*
 	 * Get the dynamic space for both the container & the data area.
	 * If either fail, cleanup & quit with error.
	 */	
	new_node = (NODE *)malloc(sizeof(NODE));
	if (!new_node)	
		return 0;
	new_node->data = malloc(l->item_size);
	if (!new_node->data) {
		free (new_node);
		return 0;
	}
	
 	memcpy(new_node->data, new_item, l->item_size);
	/*
	 * If we are the first person to arrive, take the lead. OR 
     * we do not have the ordering. Just put at the front.
	 */
	if (!comp || empty_list (*l)) {
		new_node->next = l->head;
		new_node->prev = NULL;
		/*
		 * If inserting to non-empty list let the node being pushed
		 * down know who is behind it.
		 */
		if (l->head)
			l->head->prev  = new_node;
		l->head 	   = new_node;
	}
	/*
 	 * We have an ordered list to maintain. Use the 
	 * logic supplied by the comparator function. 
	 */
	else {
		NODE	*cur_node;	
		NODE	*tail_node;			/* Needed if appending to last node */	
		
		tail_node = cur_node = l->head;	
		/*
		 * See if we can insert into the list.
		 */
		while (cur_node) {
			if (comp(cur_node->data, new_node->data) > 0)  {
				new_node->next = cur_node;
				new_node->prev = cur_node->prev;
				cur_node->prev = new_node;
			
				if (cur_node == l->head)
					l->head = new_node; 
				else
					/*
				 	 * Tell our previous neighbor that we are it's next link.
				 	 */
					new_node->prev->next = new_node;
				break;
			}
			tail_node = cur_node;
			cur_node = cur_node->next;
		}
		/*
 		 * If we did not find any slot inside the list, let's sit at the tail.
		 */
		if (!cur_node) {
			tail_node->next = new_node;
			new_node->prev  = tail_node;
			new_node->next  = NULL;
		}
	}
	
	/*
 	 * List has changed. Update the magic number. Iterators would check
	 * for this value to be same as theirs for validation.
	 */
	l->magic++;
	return 1;
}	

/* Search an item from the list */
void *lookup_list (LIST *l, void *srch_item, COMPARATOR comp)
{
	NODE *node = l->head;
	while (node) {
		if (comp(node->data, srch_item) == 0)
			return node->data;
		else 
			node = node->next;
	}
	return NULL;	
}

/* Delete an item from the list */
int delete_list (LIST *l, void *srch_item, COMPARATOR comp)
{
	NODE *node = l->head;
	while (node) {
		if (comp(node->data, srch_item) == 0)  {
			/*
			 * Link up our next & previous neighbours if any. 
			 * Atleast 1 neighbour must exist.
			 */
			if (node->next)
				node->next->prev = node->prev;
			if (node->prev)
				node->prev->next = node->next; 
			else  {							/* We removed the head node */
				l->head = node->next;		/* New List head node 		*/
				if (l->head)				/* Well! If list had 1 node */
					l->head->prev = NULL;	/* No, still more left &  	*/
											/* so head has no previous. */
			}
			/*
			 * Time to giveback all the memory for this item & node.
			 */
			free(node->data);
			free(node);
    		/*
     		 * List has changed. Update the magic number. 
     		 */
			l->magic++;
			return 1;
		}
		node = node->next;	
	}
	return 0;
}

/* 
 * Destroy the list -> Delete all items, free the storage, clear the 
 * List structure.
 */
void destroy_list (LIST *l)
{
	NODE *link;
	/*
	 * Start at the head of the list. Free the data storage area first.
	 * Then free the container node itself. Repeat till no more nodes left.
	 */
	while (l->head) {
		link = l->head->next;
		free(l->head->data);
		free(l->head);
		l->head = link;
	}
	l->magic     = 0;
	l->item_size = 1;
}


/* Tester function for list empty */
int empty_list (LIST l) 
{
	return (l.head == NULL);
} 

/*
 * Create the iterator. The magic number from the list is copied into
 * the iterator used for validation.
 */
ITERATOR *create_iterator (LIST *l)
{
	ITERATOR	*iter;
	iter = (ITERATOR *)malloc(sizeof(ITERATOR));
	if (iter) {
		iter->plist    = l;				/* The list we belong to 	  */
		iter->magic    = l->magic;		/* The most current signature */
		iter->cur_node = l->head;		/* Let's start at Head of list*/
		return iter;
	}
	else
		return NULL;	
};

/*
 * Check if this iterator is still valid by comparing the magic numbers.
 * If they are different the list is modified.
 */
int valid_iterator (ITERATOR *iter)
{
	return (iter->magic == iter->plist->magic);
}

/* 
 * Return the next unread item in the list using this iterator. 
 */
void *next_item (ITERATOR *iter)
{
	NODE  *node;
	if (!valid_iterator (iter) || !(iter->cur_node))
		return NULL;
	node = iter->cur_node;	
	iter->cur_node = iter->cur_node->next;
	return node->data;
}

/* Destroy the iterator. */
void destroy_iterator (ITERATOR *iter)
{
	if (iter)
		free(iter);
}
