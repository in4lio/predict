
/*  ut-coro.c was generated by yup.py (yupp) 1.0c2
    out of ut-coro.yu-c 
 *//**
 *  \file  ut-coro.c (ut-coro.yu-c)
 *  \brief  Unit test of coroutines.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#include "include.h"

/**
 *  \defgroup ut_coro Unit test of coroutines
 *  \ingroup ut
 *  \{
 */

#define CYCLE_COUNT  1024

#define B_SIZE  8
static int buf[ B_SIZE ];
static int pos = 0;

static semaphore_t b_full, b_empty;

static int answer = 0;
static int answer_last = 0;

static int inside_test_3;

static void b_set( int mark )
{
	buf[ pos ] = mark;
	pos = ( pos + 1 ) % B_SIZE;
}

static int b_get( void )
{
	int mark = buf[ pos ];
	pos = ( pos + 1 ) % B_SIZE;

	return mark;
}

static int create_mark( void )
{
	static int mark = 0;

	return mark++;
}

static void check_mark( int mark )
{
	assert_int_eq( answer++, mark );
}

int test_1_init( void )
{
	return ( CO_READY ); /* CO_SKIP */
}

int coro_test_1( co_t *co_p )
{
	static int i;
	if ( *co_p ) goto **co_p;
	/* begin */
	for ( i = 0; i < CYCLE_COUNT; i++ ) {
		do {
			/* acquire */
			do {
				/* wait */
				*co_p = &&L__0;

				L__0:
				if (!( b_full > 0 )) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
			--b_full;
		} while ( 0 );

		b_set( create_mark());

		do {
			/* release */
			++b_empty;
		} while ( 0 );
	}
	/* end */
	*co_p = &&L__END_test_1;

	L__END_test_1:
	
	return CO_END;
}

int test_2_init( void )
{
	return ( CO_READY ); /* CO_SKIP */
}

int coro_test_2( co_t *co_p )
{
	static int i;
	if ( *co_p ) goto **co_p;
	/* begin */
	for ( i = 0; i < CYCLE_COUNT; i++ ) {
		do {
			/* acquire */
			do {
				/* wait */
				*co_p = &&L__1;

				L__1:
				if (!( b_empty > 0 )) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
			--b_empty;
		} while ( 0 );

		check_mark( b_get());

		do {
			/* release */
			++b_full;
		} while ( 0 );
	}
	/* end */
	*co_p = &&L__END_test_2;

	L__END_test_2:
	
	return CO_END;
}

int test_3_init( void )
{
	inside_test_3 = 0;

	return ( CO_READY ); /* CO_SKIP */
}

int coro_test_3( co_t *co_p )
{
	static int i = 1;

	++inside_test_3;
	if ( *co_p ) goto **co_p;
	/* begin */
	switch ( i ) {

	case 1:
		i = 2;
		do {
			/* yield */
			*co_p = &&L__2;
			--inside_test_3;
			return CO_YIELD;

			L__2:;
		} while ( 0 );
		assert_int_eq( 2, i );

		i = 3;
		do {
			/* yield */
			*co_p = &&L__3;
			--inside_test_3;
			return CO_YIELD;

			L__3:;
		} while ( 0 );
		assert_int_eq( 3, i );

		i = 4;
		do {
			/* yield */
			*co_p = &&L__4;
			--inside_test_3;
			return CO_YIELD;

			L__4:;
		} while ( 0 );
		assert_int_eq( 4, i );

		do {
			/* wait */
			*co_p = &&L__5;

			L__5:
			if (!( ++i < 10)) { /* cond */
				--inside_test_3;
				return CO_WAIT;
			}
		} while ( 0 );
		for ( ; i < 20; i++ ) {
			do {
				/* yield */
				*co_p = &&L__6;
				--inside_test_3;
				return CO_YIELD;

				L__6:;
			} while ( 0 );
		}
		assert_int_eq( 20, i );

		i = -1;
		do {
			/* restart */
			*co_p = NULL;
			--inside_test_3;
			return CO_YIELD;
		} while ( 0 );

	default:
		assert_fail( "unreachable instruction" );
		break;

	case -1:
		i = 1;
		--inside_test_3;
		do {
			/* quit */
			*co_p = &&__label;

			__label:
			--inside_test_3;
			return CO_END;
		} while ( 0 );
	}
	assert_fail( "unreachable instruction" );
	--inside_test_3;
	/* end */
	*co_p = &&L__END_test_3;

	L__END_test_3:
	--inside_test_3;
	return CO_END;
}

int test_4_init( void )
{
	return ( CO_READY ); /* CO_SKIP */
}

int coro_test_4( co_t *co_p )
{
	
	if ( *co_p ) goto **co_p;
	/* begin */
	do {
		assert_not( inside_test_3 );
		do {
			/* yield */
			*co_p = &&L__7;
	
			return CO_YIELD;

			L__7:;
		} while ( 0 );
	} while ( inside_test_3 != -1 );
	/* end */
	*co_p = &&L__END_test_4;

	L__END_test_4:
	
	return CO_END;
}

int ut_coro_init( void )
{
	return ( CO_READY ); /* CO_SKIP */
}

void ut_coro_uninit( void )
{
}

int coro_ut_coro( co_t *co_p )
{
	static co_t co_test_1;
	static co_t co_test_2;
	static co_t co_test_3;
	static co_t co_test_4;
	if ( *co_p ) goto **co_p;
	/* begin */
	ut_2_begin();
	do {
		/* yield */
		*co_p = &&L__8;
	
		return CO_YIELD;

		L__8:;
	} while ( 0 );

	answer_last += CYCLE_COUNT;

	b_empty = 0;
	b_full = B_SIZE;

	co_test_1 = NULL;
	test_1_init();

	co_test_2 = NULL;
	test_2_init();

	do {
		/* wait */
		*co_p = &&L__9;

		L__9:
		if (!(!((  coro_test_1( &co_test_1 ) | coro_test_2( &co_test_2 ) ) < CO_END ))) { /* cond */
		
			return CO_WAIT;
		}
	} while ( 0 );
	assert_int_eq( answer_last, answer );

	co_test_3 = NULL;
	test_3_init();

	co_test_4 = NULL;
	test_4_init();

	do {
		/* wait */
		*co_p = &&L__10;

		L__10:
		if (!(!((  coro_test_3( &co_test_3 ) | coro_test_4( &co_test_4 ) ) < CO_END ))) { /* cond */
		
			return CO_WAIT;
		}
	} while ( 0 );
	/* end */
	*co_p = &&L__END_ut_coro;

	L__END_ut_coro:
	
	return CO_END;
}

/** \} */
