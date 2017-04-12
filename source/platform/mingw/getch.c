
/*  getch.c was generated by yup.py (yupp) 1.0b6
    out of getch.yu-c 
 *//**
 *  \file  getch.c (getch.yu-c)
 *  \brief  Read from debug interface.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define GETCH_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup char
 *  \{
 */

static struct timeval getch_t = { 0, 0 };

void getch_init( void )
{
}

void getch_uninit( void )
{
}

__inline int getch_1( void )
{
	if ( clock_time_before( getch_t )) return EOF;
	getch_t = clock_t_set( 100 );

	/* Unfortunately, this version of kbhit() has long delay. */
	return ( kbhit() ? _getch() : EOF );
}

int getch_escseq( int chr )
{
	static int seq = 0;

	if (( chr == 0 ) || ( chr == 0xE0 )) {
		seq = 1;
		return ( ESCSEQ_INSIDE );
	}
	if ( seq == 1 ) {
		seq = 0;
		return ( ESCSEQ_OK );
	}
	return ( ESCSEQ_1 );
}

/** \} */
