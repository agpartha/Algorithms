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


#ifndef _CDEFS_H_INCLUDED
#define _CDEFS_H_INCLUDED

/*
	for portability
*/

#define	int32	int
#define	int16	short
#define	int8	char
#define	uint32	unsigned int
#define	uint16	unsigned short
#define	uint8	unsigned char
#define uint	unsigned int
#define uchar	unsigned char
#define byte	unsigned char

#define bool    int
typedef unsigned char	tinybool;

#ifndef TRUE
	#define	TRUE	(1==1)
#endif

#ifndef true
	#define	true	(1==1)
#endif

#ifndef FALSE
	#define	FALSE	(1==0)
#endif

#ifndef false
	#define	false	(1==0)
#endif

#ifndef ERR
#define ERR		-1
#endif
#ifndef NOERR
#define NOERR	0
#endif

#ifdef OK
#	undef OK
#endif

#define OK		1

#endif /* ifndef _CDEFS_H_INCLUDED */
