
/*  data-str.c was generated by yup.py (yupp) 1.0b6
    out of data-str.yu-c 
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
	sprintf( s, "0x%04" PRIXWORD, val );
	return ( s );
}

char *string_dword_h( char *s, dword val )
{
	sprintf( s, "0x%08" PRIXDWORD, val );
	return ( s );
}
