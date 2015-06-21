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
 *				  This file contains the prototype declarations for 
 *				  the API functions for the Insertion Sort Implementation.
 */

#include "dlist.h"

#define BUCKET_TIME_MS    1
#define MAX_TIMER_BUCKETS 10
typedef int (*OPERATION)(void *context);

typedef struct timer_node_t {
    unsigned long interval_ms;
    unsigned long abs_sys_ticks;
    void          *context;
    OPERATION     oper;
} tnode_t;

typedef struct tnode_t *timer_handle_t;

typedef struct timer_db_t {
    unsigned long  cur_tick;
    unsigned short cur_tb;
    unsigned short timer_tick_ms;
    unsigned long max_interval_ms;  // Largest interval we can support
    LIST          timer_list[MAX_TIMER_BUCKETS];       
                                    // All timers inserted according to some
                                    // order.    
}tdb_t;

/*
 * This macro helps in reduced clutter for coding pointer 
 * arithmetic used in sequential access of the array of 
 * generic item_size.
 * start_addr + nth_item * item_size is the formula.
 */
#define	ITEM_N(x, y, z)	((char *)(x) + (y) * (z))

int     timer_db_disp (tdb_t *tdb);
int     timer_db_del (tdb_t *tdb);
int     timer_del (tdb_t *tdb, timer_handle_t th);
timer_handle_t timer_add (tdb_t *tdb, unsigned long interval,
                              void *context, OPERATION oper);
tdb_t   *timer_db_init (unsigned long max_interval_ms);

#ifdef  DEBUG
#define Printf(...) printf(__VA_ARGS__)
#else   /* DEBUG */
#define Printf(...) 
#endif  /* DEBUG */

