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
#include "timer_ag.h"

#define		GET_INT(x)		(*(int *)(x))

#define MAX_TIMER 10

static const char *timer_name[MAX_TIMER] = {
                                    "One",
                                    "Two",
                                    "Three",
                                    "Four",
                                    "Five",
                                    "Six",
                                    "Seven",
                                    "Eight",
                                    "Nine",
                                    "Ten",
                                    };

static int comp_int (void *ref_data, void *new_data)
{
	return (GET_INT(ref_data) - GET_INT(new_data));
}

static int disp_str (void *name_str)
{
    if (name_str)
        printf("\t: %s\n", (char *)name_str);
    else
        printf("\t: No name Timer\n");
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
    int   timer_num = 0;
    timer_handle_t  th[MAX_TIMER];
    tdb_t *tdb;

    tdb = timer_db_init(10);
    
    // Add timers 
    th[timer_num] = timer_add(tdb, 1, timer_name[(timer_num++ % MAX_TIMER)], disp_str);
    th[timer_num] = timer_add(tdb, 20, timer_name[(timer_num++ % MAX_TIMER)], disp_str);
    th[timer_num] = timer_add(tdb, 4, timer_name[(timer_num++ % MAX_TIMER)], disp_str);
    th[timer_num] = timer_add(tdb, 9, timer_name[(timer_num++ % MAX_TIMER)], disp_str);
    th[timer_num] = timer_add(tdb, 3, timer_name[(timer_num++ % MAX_TIMER)], disp_str);

    // Display all of them
    timer_db_disp(tdb);

    // Delete timer and disp again.
    timer_del(tdb, th[--timer_num]);
    // Display all of them
    timer_db_disp(tdb);
    timer_del(tdb, th[1]);
    // Display all of them
    timer_db_disp(tdb);
    timer_del(tdb, th[0]);
    // Display all of them
    timer_db_disp(tdb);

    // Repeat, Also add a loop where we remove one timer every sec if it's time 
    // is up
}
