#include <stdio.h>

enum junky_t {
       FUNKY,
       MUNKY
     };


typedef struct junky_munky_t {
       int junk;
       enum junky_t locale;
      };

typedef struct ChanData       /* The data retained for a single channel */
    {
    char Channel_State;                                 /* Usage state */
    char Protocol;                   /* Protocol in use on the channel */
    int Using_Call_ID;        /* Call_ID of the call using the channel */
    char Service_State;                  /* Service (maintenance) state*/
    int TimerID;                  /* Service message and restart timer */
    enum junky_t locale;
    }pooker_t;

int main (void)
{

enum junky_t locale;


printf ("%d ", locale);
}
