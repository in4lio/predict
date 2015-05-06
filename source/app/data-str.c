
/*  data-str.c was generated by yup.py (yupp) 0.8b2
    out of data-str.yu-c at 2015-05-06 17:35
 *//**
 *  \file  data-str.c (data-str.yu-c)
 *  \brief  String converting.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING

#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT

#define LINK_UT_CORO

#define LINK_UT_DATA

#define DATA_STR_IMPLEMENT

#include "include.h"

char *string_byte_h( char *s, byte val )
{
	sprintf( s, "0x%02X", val );
	return ( s );
}

char *string_word_h( char *s, word val )
{
	sprintf( s, "0x%04X", val );
	return ( s );
}

char *string_dword_h( char *s, dword val )
{
	sprintf( s, "0x%08X", val );
	return ( s );
}
