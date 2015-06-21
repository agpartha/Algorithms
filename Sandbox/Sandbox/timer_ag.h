/*
 * Filename 	: timer_ag.h
 * Author 		: Anand Girish 
 * Description	: 
 *				  This file contains the prototype declarations for 
 *				  the API functions for the Insertion Sort Implementation.
 */

#include "dlist.h"

typedef int (*OPERATION)(void *context);

typedef struct timer_node_t {
    unsigned long interval_ms;
    void          *context;
    OPERATION     oper;
} tnode_t;

typedef struct tnode_t *timer_handle_t;

typedef struct timer_db_t {
    unsigned long max_interval_ms;  // Largest interval we can support
    LIST          timer_list;       // All timers inserted according to some
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

