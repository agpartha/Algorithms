/*
 * Filename 	: dlistapp.c
 * HoweWork 2 	: Advanced Data Structures in C.
 * Author 		: Anand Girish 
 * Created		: Apr 17 1998
 * Description	: 
 *				  This file contains the driver program
 *				  to test the doubly-linked list implementation.
 */

#include <stdio.h>
#include <string.h>
#include "dlist.h"


void print_list 	 (LIST *l);
void print_list_iter (LIST *l);

int main (void)
{
	LIST 		l;
	COMPARATOR 	comp = (COMPARATOR)strcmp;
	ITERATOR	*iter1, *iter2, *iter3, *iter4;
		
	printf ("Driver program for Doubly-Linked list\n");

	init_list (&l, 40);
	iter1 = create_iterator (&l);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	insert_list (&l, "Umesh", comp);
	iter2 = create_iterator (&l);
	print_list_iter (&l);
	print_list (&l);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	printf ("%s iterator validity %d\n", "iter2", valid_iterator(iter2));
	insert_list (&l, "Anand", comp);
	print_list_iter (&l);
	print_list (&l);
	insert_list (&l, "Soundarya", comp);
	iter3 = create_iterator (&l);
	print_list_iter (&l);
	print_list (&l);
	lookup_list (&l, "Anand", comp);
	printf ("%s iterator validity %d\n", "iter3", valid_iterator(iter3));
	insert_list (&l, "Urmila", comp);
	insert_list (&l, "Sonali", comp);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	printf ("%s iterator validity %d\n", "iter2", valid_iterator(iter2));
	printf ("%s iterator validity %d\n", "iter3", valid_iterator(iter3));
	print_list_iter (&l);
	print_list (&l);
	lookup_list (&l, "Prema", comp);
	insert_list (&l, "Sabax", comp);
	print_list_iter (&l);
	print_list (&l);
	delete_list (&l, "Sabax", comp);
	iter4 = create_iterator (&l);
	printf ("%s iterator validity %d\n", "iter4", valid_iterator(iter4));
	insert_list (&l, "Nethra", comp);
	insert_list (&l, "Shruthi", comp);
	insert_list (&l, "Shilpa", comp);
	insert_list (&l, "Madhuri", comp);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	printf ("%s iterator validity %d\n", "iter2", valid_iterator(iter2));
	printf ("%s iterator validity %d\n", "iter3", valid_iterator(iter3));
	printf ("%s iterator validity %d\n", "iter4", valid_iterator(iter4));
	insert_list (&l, "Pooja", comp);
	print_list_iter (&l);
	print_list (&l);
	destroy_list (&l); 
	print_list_iter (&l);
	print_list (&l);

	destroy_iterator (iter1);
	destroy_iterator (iter2);
	destroy_iterator (iter3);
	destroy_iterator (iter4);
}


void print_list (LIST *l)
{
	NODE 	*node;
	
	if (!l)
		return;
	else 
		node = l->head;

	while (node)  {
		printf ("%s\n", (char *)(node->data));
		node = node->next;
	}
	printf (" ---OooO--- \n");
}


void print_list_iter (LIST *l)
{
	ITERATOR *iter;
	char	 *data;
	iter = create_iterator (l);	
	if (!iter)
		return;
	
	while (data = next_item (iter)) 
		printf ("%s\n", data);
	printf (" ---oOOo--- \n");
}
