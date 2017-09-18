#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

// common header
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string>

#define NULL 0

// define bytes size
#define	KB	(1024)
#define MB	(1024*1024)

#ifndef safe_delete_array
#define safe_delete_array(Address)			{ if( NULL != (Address) )	delete[](Address);	Address = NULL; }
#endif

// define data type
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int   DWORD;

#define MIN_INT_VALUE	(0x80000000)
#define MAX_INT_VALUE	(0x7FFFFFFF)
#define MIN_LONG_VALUE	(0x80000000)
#define MAX_LONG_VALUE	(0x7FFFFFFF)
#define MIN_WORD_VALUE	(0)
#define MAX_WORD_VALUE	(0xFFFF)
#define MIN_DWORD_VALUE	(0)
#ifndef MAX_DWORD_VALUE
#define	MAX_DWORD_VALUE	(0xFFFFFFFF)
#endif


/*
*	UTF8变长字节范围
*/

// 1字节	0-127												0x00-0x7F
// 2字节	192-223	128-191										0xC0-0xDF 0x80-0xBF
// 3字节	224-239	128-191	128-191								0xE0-0xEF 0x80-0xBF 0x80-0xBF
// 4字节	240-247	128-191	128-191	128-191						0xF0-0xF7 0x80-0xBF 0x80-0xBF 0x80-0xBF
// 5字节	248-251	128-191	128-191	128-191	128-191				0xF8-0xFB 0x80-0xBF 0x80-0xBF 0x80-0xBF 0x80-0xBF
// 6字节	252-253	128-191	128-191	128-191	128-191	128-191		0xFC-0xFD 0x80-0xBF 0x80-0xBF 0x80-0xBF 0x80-0xBF 0x80-0xBF

#define	UTF8_1BYTE_END_VALUE	0x7F	//0111 1111		//127
#define	UTF8_2BYTE_END_VALUE	0xDF	//1101 1111		//223
#define	UTF8_3BYTE_END_VALUE	0xEF	//1110 1111		//239
#define	UTF8_4BYTE_END_VALUE	0xF7	//1111 0111		//247
#define	UTF8_5BYTE_END_VALUE	0xFB	//1111 1011		//251
#define	UTF8_6BYTE_END_VALUE	0xFD	//1111 1101		//253

#define	UTF8_OTHER_BYTE_BEGIN_VALUE	0x80//1000 0000		//128
#define	UTF8_OTHER_BYTE_END_VALUE	0xBF//1011 1111		//191

// ansi encoding end value
#define ASCII_BYTE_END_VALUE	0x7F

#endif // __COMMON_DEF_H__
