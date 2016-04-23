/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  clock.c
 *  \brief  Real-time clock.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define CLOCK_IMPLEMENT
#include "include.h"

// CORTEX_M //////////////////////////////////////
#if defined( __ARM_ARCH )

#include "rtc.h"

// UNIX //////////////////////////////////////////
// WIN32 /////////////////////////////////////////
// MSDOS /////////////////////////////////////////
#else

//////////////////////////////////////////////////
#endif

/**
 *  \addtogroup clock
 */

#define U_PER_CSEC  ( 1000 * 10 )
#define C_PER_SEC   ( 100 )

static struct timeval __clock_time_started;

void clock_init( void )
{
// CORTEX_M //////////////////////////////////////
#if defined( __ARM_ARCH )

	rtc_init_clock();

// UNIX //////////////////////////////////////////
// WIN32 /////////////////////////////////////////
// MSDOS /////////////////////////////////////////
#else

//////////////////////////////////////////////////
#endif

	gettimeofday( &__clock_time_started, NULL );
}

void clock_set_time( uint32_t h __attribute__(( unused )), uint32_t m  __attribute__(( unused ))
                   , uint32_t s __attribute__(( unused )), uint32_t cs __attribute__(( unused )))
{
	// struct timeval now = { .tv_sec = ( h * ( 100 * 60 * 60 ) + m * ( 100 * 60 ) + s, .tv_usec = cs * U_PER_CSEC };
}

uint32_t clock_time_running( void )
{
	struct timeval now, dt;

	gettimeofday( &now, NULL );
	timersub( &now, &__clock_time_started, &dt );

	return ( dt.tv_sec * C_PER_SEC + ( dt.tv_usec + U_PER_CSEC / 2 ) / U_PER_CSEC );
}

const char *clock_stamp( const struct timeval *tval, char *s )
{
	struct timeval t;
	char *p = s;
	unsigned int csec;
	time_t sec;

	if ( !tval ) {
		gettimeofday( &t, NULL );
	} else {
		t = *tval;
	}
	sec = t.tv_sec;
	csec = ( t.tv_usec + U_PER_CSEC / 2 ) / U_PER_CSEC;
	if ( csec == C_PER_SEC ) {
		++sec;
		csec = 0;
	}
	p += strftime( p, 16, "%H:%M:%S", localtime( &sec ));
	sprintf( p, ".%02u", csec );

	return ( s );
}

const char *clock_stamp_short( char *s )
{
	time_t t;

	time( &t );
	strftime( s, 16, "%H:%M:%S", localtime( &t ));

	return ( s );
}

time_t clock_stamp_datetime( char* sd, char* st )
{
	time_t t;
	struct tm *_t;

	time( &t );
	_t = localtime( &t );
	strftime( sd, 16, "%d.%m.%Y", _t );
	strftime( st, 16, "%H:%M:%S", _t );

	return ( t );
}

struct timeval clock_t_set( const int ms )
{
	struct timeval t;

	gettimeofday( &t, NULL );
	__clock_t_add( &t, ms );

	return ( t );
}

void __clock_t_add( struct timeval *t, const int ms )
{
	t->tv_sec += ms / 1000;
	t->tv_usec += ( ms % 1000 ) * 1000;

	if ( t->tv_usec > 1000000 ) {
		t->tv_sec += t->tv_usec / 1000000;
		t->tv_usec %= 1000000;
	}
}

int __clock_time_after( struct timeval *t )
{
	struct timeval now;

	gettimeofday( &now, NULL );

	return ( timercmp( &now, t, >= ));
}

int __clock_t_rest( struct timeval *t )
{
	struct timeval now, rest;

	gettimeofday( &now, NULL );
	timersub( t, &now, &rest );

	return ( rest.tv_sec * 1000 ) + ( rest.tv_usec / 1000 );
}

/** \} */
