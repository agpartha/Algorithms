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
