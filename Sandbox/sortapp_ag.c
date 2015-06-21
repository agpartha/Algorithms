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
 *				  to test the Sort implementation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef   BUBBLE_SORT
#define SORT_STR (const)"Bubble"
#include "bsort_ag.h"
#endif
#ifdef   SELECTION_SORT
#define SORT_STR (const)"Selection"
#include "ssort_ag.h"
#endif
#ifdef   INSERTION_SORT
#define SORT_STR (const)"Insertion"
#include "isort_ag.h"
#endif
#ifdef   QUICK_SORT
#define SORT_STR (const)"Quick"
#include "qsort_ag.h"
#endif
#ifdef   MERGE_SORT
#define SORT_STR (const)"Merge"
#include "msort_ag.h"
#endif

#define		GET_INT(x)		(*(int *)(x))

static int comp_int (void *ref_data, void *new_data)
{
	return (GET_INT(ref_data) - GET_INT(new_data));
}

static void disp_int_array(int int_arry[], int n_items)
{
	int index = 0;
	while (index < n_items)
		printf ("%d ", int_arry[index++]);
	printf ("\n");
}

static int comp_str (void *ref_data, void *new_data)
{
	return strcmp (*(char **)ref_data, *(char **)new_data);
}

static void disp_name_array(char **name_array)
{
	while (*name_array)
		printf (" %s\n", *name_array++);
}

int main (void)
{
	int		int_arry[]		= {90, 23, 9, 34, 67, 1, 89, -120, 230};
	char	*name_array[]	= {"Anand", "Amir", "Zach", "Mike", "Uri",
								"Amar", "Guru", "Gir", "Parthy",
								"Sudhy", "Paapy", "Kavi", "Putt", NULL}; 
	printf ("\n\t\t %s Sort Test Program\n", SORT_STR);

	printf ("\nUnsorted Array of integers\n");
	disp_int_array (int_arry, sizeof(int_arry)/sizeof(int));
	sort_ag (int_arry, sizeof(int), sizeof(int_arry)/sizeof(int), comp_int);
	printf ("\nSorted Array of integers\n");
	disp_int_array (int_arry, sizeof(int_arry)/sizeof(int));

	printf ("\nUnsorted Array of names\n");
	disp_name_array (name_array);
	sort_ag (name_array, sizeof(char *), sizeof(name_array)/sizeof(char *) - 1, 
					comp_str);	/* size 1 less for the NULL entry */
	printf ("\nSorted Array of names\n");
	disp_name_array (name_array);
}
