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
