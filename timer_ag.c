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
 *				  this file contains the infrastructure routines
 *				  to implement timer wheels.
 */

#include <stdio.h>
#include <errno.h>
#include "timer_ag.h"

#define     GET_INT(x)      (*(int *)(x))

static int comp_thandle (void *ref_data, void *new_data)
{
    return (GET_INT(ref_data) - GET_INT(new_data));
}

/*
 * the routine to swap the two items whose type is not known. 
 */
void swap_data (void *first_item, void *second_item, size_t item_size)
{
	void *temp;
	if (!(temp = (void *)malloc (item_size))) {
		Printf ("unrecoverable error: no memory..!!!\n");
		return;
	}
	memcpy (temp, first_item, item_size);
	memcpy (first_item, second_item, item_size);
	memcpy (second_item, temp, item_size);	
}

int     timer_db_disp (tdb_t *tdb)
{
    ITERATOR    *iter;
    tnode_t     *tnode;

    iter = create_iterator(&tdb->timer_list);
    
    while (tnode = (tnode_t *)next_item(iter))  {
        printf("Timer interval %u, context %p, oper %p\n",
                tnode->interval_ms, tnode->context, tnode->oper);
        if (tnode->oper)
            tnode->oper(tnode->context);
    }
    destroy_iterator(iter);
}

int     timer_db_del (tdb_t *tdb);

int     timer_del (tdb_t *tdb, timer_handle_t th)
{
    int rv;
    
    Printf("Deleting timer\n");
    if (th)  
        ((tnode_t *)th)->oper(((tnode_t *)th)->context);
    else 
        return 0;

    // find the timer in the list and remove it
    rv = delete_list(&tdb->timer_list, (tnode_t *)th, comp_thandle);
    if (0 == rv) 
        Printf("Could not find timer in the databse\n");
    else 
        free((tnode_t *)th);
    return rv;
}

timer_handle_t timer_add (tdb_t *tdb, unsigned long interval, 
                              void *context, OPERATION oper)
{
    tnode_t *tnode;

    if (interval > tdb->max_interval_ms) {
        printf("%s(%d): timer interval %u exceeds allowed max interval %u\n",
                __FUNCTION__, __LINE__, interval, tdb->max_interval_ms);
        return (timer_handle_t)NULL;
    }
    
    tnode = (tnode_t *)malloc(sizeof(tnode_t));

    tnode->interval_ms = interval;
    tnode->context     = context;
    tnode->oper        = oper;
    // Use the timer interval to insert into the list.
    insert_list(&tdb->timer_list, tnode, comp_thandle);
    Printf("%s(%d): timer %p interval %u added\n", 
            __FUNCTION__, __LINE__, tnode, tnode->interval_ms);
    return (timer_handle_t)tnode;
}

/*
 * the insertion sort function which operates on an array of data items.
 */
tdb_t *timer_db_init (unsigned long max_interval_ms)
{
    tdb_t *tdb;
    Printf("\n%s(%d) max_interval_ms %d\n", __FUNCTION__, __LINE__, max_interval_ms); 
    
    tdb = (tdb_t *)malloc(sizeof(tdb));
    tdb->max_interval_ms = max_interval_ms;
    init_list(&tdb->timer_list, sizeof(tnode_t));
    return tdb;
}
