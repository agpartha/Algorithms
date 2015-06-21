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
#include "timerw_ag.h"

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
    int         tb;

   for (tb = 0; tb < MAX_TIMER_BUCKETS; tb++) { 
    iter = create_iterator(&tdb->timer_list[tb]);
    
    while (tnode = (tnode_t *)next_item(iter))  {
        printf("Timer interval %u, context %p, oper %p\n",
                tnode->interval_ms, tnode->context, tnode->oper);
        if (tnode->oper)
            tnode->oper(tnode->context);
    }
    destroy_iterator(iter);
    }
}


int timer_tick (tdb_t *tdb)
{
    tdb->cur_tick++;
    // Once we have hit our bucket's time 
    // have to visit the timers in this bucket and move the current bucket
    // to next bucket
    if (0 == (tdb->cur_tick % BUCKET_TIME_MS)) {
        tdb->cur_tb = (tdb->cur_tb + 1) % MAX_TIMER_BUCKETS;
        Printf("Advacing Timer bucket to %d\n", tdb->cur_tb);
    }
}

int     timer_del (tdb_t *tdb, timer_handle_t th)
{
    int rv;
    int tb;
    tnode_t *tnode = (tnode_t *)th;
    
    // Simulate timer ticking by advancing each time we do any operation....
    // Reality we shoud be driving this by another event or thread....
    //
    Printf("Deleting timer\n");
    if (tnode)  
        ((tnode_t *)th)->oper(((tnode_t *)th)->context);
    else 
        return 0;

    // From the timer's absolute time for expiry see 
    // if we are past current tick time, if so we will have expired unless it 
    // was recurring.
    if (tnode->abs_sys_ticks < tdb->cur_tick) {
        printf("%s(%d): Timer with context %p oper %p abs_ticks %lu cur_tick %lu "
               "not found\n",
                __FUNCTION__, __LINE__, tnode->context, tnode->oper, 
                tnode->abs_sys_ticks, tdb->cur_tick);
        return 0;
    }
    
    tb = (tdb->cur_tb + ((tnode->abs_sys_ticks - tdb->cur_tick)/ tdb->timer_tick_ms)) % MAX_TIMER_BUCKETS;

    printf("%s(%d): Timer with context %p oper %p abs_ticks %lu cur_tick %lu "
               "found in bucket %d\n",
                __FUNCTION__, __LINE__, tnode->context, tnode->oper, 
                tnode->abs_sys_ticks, tdb->cur_tick, tb);
    // find the timer in the list and remove it
    rv = delete_list(&tdb->timer_list[tb], (tnode_t *)th, comp_thandle);
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

    // Simulate timer ticking by advancing each time we do any operation....
    // Reality we shoud be driving this by another event or thread....
    //
    tdb->cur_tick++;
    if (interval > tdb->max_interval_ms) {
        printf("%s(%d): timer interval %lu exceeds allowed max interval %lu\n",
                __FUNCTION__, __LINE__, interval, tdb->max_interval_ms);
        return (timer_handle_t)NULL;
    }
    
    tnode = (tnode_t *)malloc(sizeof(tnode_t));

    tnode->interval_ms = interval;
    // Figure out how many ticks away this timer needs to expire.
    tnode->abs_sys_ticks = tdb->cur_tick + (interval / tdb->timer_tick_ms);
    tnode->context     = context;
    tnode->oper        = oper;
    // Use the timer interval to insert into the list.
    // Key here is to find the right bucket for the 
    // list.
    //
    // Simple way is to put the timer to a bucket to which the time interval belongs.
    // We always move from bucket to next bucket after the time for first bucket is done.
    // 
    int tb;
    tb = (tdb->cur_tb + (interval / tdb->timer_tick_ms)) % MAX_TIMER_BUCKETS;
    insert_list(&tdb->timer_list[tb], tnode, comp_thandle);
    Printf("%s(%d): timer %p interval %u added to tb %d abs ticks %lu cur_tick %lu\n", 
            __FUNCTION__, __LINE__, tnode, tnode->interval_ms, tb, tnode->abs_sys_ticks,
            tdb->cur_tick);
    return (timer_handle_t)tnode;
}

/*
 * the insertion sort function which operates on an array of data items.
 */
tdb_t *timer_db_init (unsigned long max_interval_ms)
{
    tdb_t *tdb;
    int   tb;

    Printf("\n%s(%d) max_interval_ms %d\n", __FUNCTION__, __LINE__, max_interval_ms); 
    
    tdb = (tdb_t *)malloc(sizeof(tdb));
    tdb->cur_tick        = 0;
    tdb->cur_tb          = 0;
    tdb->timer_tick_ms   = BUCKET_TIME_MS;
    tdb->max_interval_ms = max_interval_ms;
    
    for (tb = 0; tb < MAX_TIMER_BUCKETS; tb++)
        init_list(&tdb->timer_list[tb], sizeof(tnode_t));
    return tdb;
}
