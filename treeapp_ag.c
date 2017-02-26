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
 *				  to test the Binary Search Tree implementation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree_ag.h"

#define		MAX_NAME_LEN	80
#define		GET_INT(x)		(*(int *)(x))

int comp_int (void *ref_data, void *new_data)
{
	return (GET_INT(ref_data) - GET_INT(new_data));
}

void disp_int(void *item_data)
{
	printf (" %d", GET_INT(item_data));
}

int comp_str (void *ref_data, void *new_data)
{
	return strcmp ((char *)ref_data, (char *)new_data);
}

void disp_name(void *item_data)
{
	printf (" %s\n", (char *)item_data);
}

int main (void)
{
	bst_t	*bst_int, *bst_name;
	int 				n_items;
	int					item_cnt;

	bst_int = create_bst (sizeof(int), comp_int);
	printf ("\tNo of Items in the Binary Search Tree ? : ");
	scanf ("%d", &n_items);

	item_cnt = 1;
	while (item_cnt <= n_items)  {
		int 	item;
		printf ("\tInteger %d ? : ", item_cnt++);
		scanf ("%d", &item);
		insert_item (bst_int, &item);
		if (lookup_bst(bst_int, &item) == NULL) 
			printf ("Lookup fails on inserted item!!\n");
	}
	display_bst(bst_int, disp_int);
	
	item_cnt = item_cnt - 1;	
	while (item_cnt-- > 0)  {
		int 	item;
		printf ("\tDelete Integer ? : ");
		scanf ("%d", &item);
		delete_item (bst_int, &item);
		display_bst(bst_int, disp_int);
	}
	display_bst(bst_int, disp_int);
	
	item_cnt = 1;
	while (item_cnt <= n_items)  {
		int 	item;
		printf ("\tInteger %d ? : ", item_cnt++);
		scanf ("%d", &item);
		insert_item (bst_int, &item);
		if (lookup_bst(bst_int, &item) == NULL) 
			printf ("Lookup fails on inserted item!!\n");
	}
	display_bst(bst_int, disp_int);
	
	
	bst_name = create_bst (MAX_NAME_LEN, comp_str);
	printf ("\tNo of Items in the Binary Search Tree ? : ");
	fflush(stdin);
	scanf ("%d", &n_items);
	fflush(stdin);
	
	item_cnt = 1;
	while (item_cnt <= n_items)  {
		char 	item[80];
		printf ("\tName %d ? : ", item_cnt++);
		gets (item);
		insert_item (bst_name, item);
		if (lookup_bst(bst_name, &item) == NULL) 
			printf ("Lookup fails on inserted item!!\n");
	}
	display_bst(bst_name, disp_name);

	item_cnt = item_cnt - 1;	
	while (item_cnt-- > 0)  {
		char 	item[80];
		printf ("\tDelete Name ? : ");
		gets (item);
		delete_item (bst_name, item);
		display_bst(bst_name, disp_name);
	}
	display_bst(bst_name, disp_name);
	
	item_cnt = 1;
	while (item_cnt <= n_items)  {
		char 	item[80];
		printf ("\tName %d ? : ", item_cnt++);
		gets (item);
		insert_item (bst_name, item);
		if (lookup_bst(bst_name, &item) == NULL) 
			printf ("Lookup fails on inserted item!!\n");
	}
	display_bst(bst_name, disp_name);
}
