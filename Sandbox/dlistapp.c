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
	insert_list (&l, "Uma", comp);
	iter2 = create_iterator (&l);
	print_list_iter (&l);
	print_list (&l);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	printf ("%s iterator validity %d\n", "iter2", valid_iterator(iter2));
	insert_list (&l, "Anand", comp);
	print_list_iter (&l);
	print_list (&l);
	insert_list (&l, "Sandy", comp);
	iter3 = create_iterator (&l);
	print_list_iter (&l);
	print_list (&l);
	lookup_list (&l, "Anand", comp);
	printf ("%s iterator validity %d\n", "iter3", valid_iterator(iter3));
	insert_list (&l, "Uma", comp);
	insert_list (&l, "Sony", comp);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	printf ("%s iterator validity %d\n", "iter2", valid_iterator(iter2));
	printf ("%s iterator validity %d\n", "iter3", valid_iterator(iter3));
	print_list_iter (&l);
	print_list (&l);
	lookup_list (&l, "Perry", comp);
	insert_list (&l, "Saby", comp);
	print_list_iter (&l);
	print_list (&l);
	delete_list (&l, "Saby", comp);
	iter4 = create_iterator (&l);
	printf ("%s iterator validity %d\n", "iter4", valid_iterator(iter4));
	insert_list (&l, "Natalie", comp);
	insert_list (&l, "Scotty", comp);
	insert_list (&l, "Shelly", comp);
	insert_list (&l, "Maddy", comp);
	printf ("%s iterator validity %d\n", "iter1", valid_iterator(iter1));
	printf ("%s iterator validity %d\n", "iter2", valid_iterator(iter2));
	printf ("%s iterator validity %d\n", "iter3", valid_iterator(iter3));
	printf ("%s iterator validity %d\n", "iter4", valid_iterator(iter4));
	insert_list (&l, "Patty", comp);
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
