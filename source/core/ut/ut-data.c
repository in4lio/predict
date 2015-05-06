
/*  ut-data.c was generated by yup.py (yupp) 0.8b2
    out of ut-data.yu-c at 2015-05-06 17:38
 *//**
 *  \file  ut-data.c (ut-data.yu-c)
 *  \brief  Unit test of application state-space.
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
 *  \defgroup ut_data Unit test of application state-space
 *  \ingroup ut
 *  \{
 */

/* Count of testing cycles */
#define CYCLE_COUNT  (( int ) USHRT_MAX + 1 )

static char __str[ 100 ];

static const int _ut_data_1_watch[] = {
	var__ut_word,
	var__ut_array_3,
	var__ut_float,
	var_COUNT
};

static const int _ut_data_2_watch[] = {
	var__ut_byte,
	var__ut_array_1,
	var__ut_float,
	var__ut_vote,
	var_COUNT
};

static const int _ut_data_array_watch[] = {
	var__ut_byte,
	var__ut_array_1,
	var_COUNT
};

int _ut_data_1_init( void )
{
	return ( CO_READY ); /* CO_SKIP */
}

int coro__ut_data_1( co_t *co_p )
{
	static int i;
	if ( *co_p ) goto **co_p;
	/* begin */
		data_clear_watch( peek__ut_data_1 );
		data_watch( peek__ut_data_1, _ut_data_1_watch );

		/* Test of error messages */
		ut_quiet_begin();

		data_set_byte( var_COUNT, 0 );                   /* Wrong variable */
		data_set_dword( var__ut_word, 0 );               /* Wrong type */
		data_get_word( var_COUNT );                      /* Wrong variable */
		data_get_float( var__ut_byte );                  /* Wrong type */
		data_get_changed( peek_COUNT, var__ut_array_2 ); /* Wrong thread */

		ut_quiet_end( 5 );                               /* 5 errors */

		data_set_byte( var__ut_byte, 1 );
		data_set_dword( var__ut_array_1, 1 );
		data_set_float( var__ut_float, 0.0 );
		data_reset_all( peek__ut_data_2 );

		/* Main operations */
		for ( i = 0; i < CYCLE_COUNT; i++ ) {
	/* 1 */	data_set_byte( var__ut_byte, i );

			do {
				/* wait */
	
				*co_p = &&L__0;

				L__0:
				if (!( data_get_changed( peek__ut_data_1, var__ut_word ))) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
	/* 3 */	data_reset( peek__ut_data_1, var__ut_word );
			assert_int_eq(( word ) i, data_get_word( var__ut_word ), );

			data_set_dword( var__ut_array_1, ( dword ) i << 8 );

			do {
				/* wait */
	
				*co_p = &&L__1;

				L__1:
				if (!( data_get_changed( peek__ut_data_1, var__ut_array_3 ))) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
	/* 5 */	data_reset( peek__ut_data_1, var__ut_array_3 );
			assert_int_eq( data_get_dword( var__ut_array_1 ), data_get_dword( var__ut_array_3 ), );

			data_set_dword( var__ut_array_0, data_get_dword( var__ut_array_2 ));
			data_set_dword( var__ut_array_2, 0 );

			data_set_float( var__ut_float, data_get_float( var__ut_float ) + 0.25 );
			data_reset( peek__ut_data_1, var__ut_float );
			do {
				/* wait */
	
				*co_p = &&L__2;

				L__2:
				if (!( data_get_changed( peek__ut_data_1, var__ut_float ))) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
		}
		assert_int_eq( 0x55555555, data_get_dword( var__ut_array_0 ), );

		/* Auxiliary operations */
		data_set_all_changed( peek__ut_data_1 );
		assert(( data_get_changed( peek__ut_data_1, var__ut_word )
		&& data_get_changed( peek__ut_data_1, var__ut_array_3 )
		&& data_get_changed( peek__ut_data_1, var__ut_float )
		&& !data_get_changed( peek__ut_data_1, var__ut_array_1 )
		&& !data_get_changed( peek__ut_data_1, var__ut_array_2 ))
		, );
		data_reset_all( peek__ut_data_1 );
		assert_not( data_get_changed_any( peek__ut_data_1 ), );
		data_set_changed( var__ut_byte );
		assert_not( data_get_changed_any( peek__ut_data_1 ), );
		data_set_changed( var__ut_float );
		assert( data_get_changed_any( peek__ut_data_1 ), );

		data_clear_watch( peek__ut_data_1 );
		assert_not( data_get_changed_any( peek__ut_data_1 ), );
		data_watch_array( peek__ut_data_1, _ut_data_array_watch );
		data_set_changed( var__ut_float );
		data_set_changed( var__ut_word );
		data_set_changed( var__ut_array_0 );
		assert_not( data_get_changed_any( peek__ut_data_1 ), );
		data_set_changed( var__ut_array_1 );
		assert( data_get_changed( peek__ut_data_1, var__ut_array_1 ), );
		data_set_changed( var__ut_array_2 );
		assert( data_get_changed( peek__ut_data_1, var__ut_array_2 ), );
		data_set_changed( var__ut_array_3 );
		assert( data_get_changed( peek__ut_data_1, var__ut_array_3 ), );
		data_set_changed( var__ut_byte );
		assert( data_get_changed( peek__ut_data_1, var__ut_byte ), );

		assert_int_eq( var__ut_array, data_atovar( data_vartoa( var__ut_array_0 )), );
		assert_str_eq( "_ut_byte", data_vartoa( data_atovar( "_ut_byte" )), );

		_AS_DWORD( i ) = 0xABCDEF;
		data_set( var__ut_array_3, &i );
		assert_str_eq( "0x00ABCDEF", data_get_string( __str, var__ut_array_3 ), );
		data_set_string( var__ut_float, "8080.02" );
		assert_str_eq( "8080.02", data_get_string( __str, var__ut_float ), );

		assert_str_eq( "word", data_get_type( var__ut_word ), );
	/* end */
	*co_p = &&L__END__ut_data_1;

	L__END__ut_data_1:
	
	return CO_END;
}

int _ut_data_2_init( void )
{
	data_watch( peek__ut_data_2, _ut_data_2_watch );

	return ( CO_READY ); /* CO_SKIP */
}

int coro__ut_data_2( co_t *co_p )
{
	static int i;
	if ( *co_p ) goto **co_p;
	/* begin */
		data_set_word( var__ut_word, 1 );
		data_set_dword( var__ut_array_3, 1 );
		data_reset_all( peek__ut_data_1 );
		data_set_dword( var__ut_array_0, 0x55555555 );

		for ( i = 0; i < CYCLE_COUNT; i++ ) {

			do {
				/* wait */
	
				*co_p = &&L__3;

				L__3:
				if (!( data_get_changed( peek__ut_data_2, var__ut_byte ))) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
	/* 2 */	data_reset( peek__ut_data_2, var__ut_byte );
			assert_int_eq(( byte ) i, data_get_byte( var__ut_byte ), );

			data_set_word( var__ut_word, i );

			do {
				/* wait */
	
				*co_p = &&L__4;

				L__4:
				if (!( data_get_changed( peek__ut_data_2, var__ut_array_1 ))) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
	/* 4 */	data_reset( peek__ut_data_2, var__ut_array_1 );

			data_set_dword( var__ut_array_3, ( dword ) i << 8 );
			assert_int_eq( data_get_dword( var__ut_array_3 ), data_get_dword( var__ut_array_1 ), );

			data_set_dword( var__ut_array_2, data_get_dword( var__ut_array_0 ));
			data_set_dword( var__ut_array_0, 0 );

			do {
				/* wait */
	
				*co_p = &&L__5;

				L__5:
				if (!( data_get_changed( peek__ut_data_2, var__ut_float ))) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
	/* 6 */	data_set_float( var__ut_float, data_get_float( var__ut_float ) + 0.25 );
			data_reset( peek__ut_data_2, var__ut_float );
		}
		assert_float_eq(( float )( CYCLE_COUNT >> 1 ), data_get_float( var__ut_float ), 0.0, );

		/* Voting operations */
		/* I: -  II: -  III: -  M: -  */
		assert_not( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		assert_not( voted_valid( var__ut_vote ), );
		/* I: -  II: 0  III: -  M: -  */
		voted_set_byte( var__ut_vote, 2, 0, &vote_byte );
		assert_not( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		assert_not( voted_valid( var__ut_vote ), );
		/* I: -  II: 0  III: 0  M: 0  */
		voted_set_byte( var__ut_vote, 3, 0, &vote_byte );
		assert( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		data_reset( peek__ut_data_2, var__ut_vote );
		assert( voted_valid( var__ut_vote ), );
		assert_int_eq( 0, data_get_byte( var__ut_vote ), );
		/* I: -  II: 0  III: 1  M: -  */
		voted_set_byte( var__ut_vote, 3, 1, &vote_byte );
		assert( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		data_reset( peek__ut_data_2, var__ut_vote );
		assert_not( voted_valid( var__ut_vote ), );
		/* I: 1  II: 0  III: 1  M: 1  */
		voted_set_byte( var__ut_vote, 1, 1, &vote_byte );
		assert( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		data_reset( peek__ut_data_2, var__ut_vote );
		assert( voted_valid( var__ut_vote ), );
		assert_int_eq( 1, data_get_byte( var__ut_vote ), );
		/* I: 1  II: 0  III: 0  M: 0  */
		voted_set_byte( var__ut_vote, 3, 0, &vote_byte );
		assert( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		data_reset( peek__ut_data_2, var__ut_vote );
		assert( voted_valid( var__ut_vote ), );
		assert_int_eq( 0, data_get_byte( var__ut_vote ), );
		/* I: 1  II: 2  III: 0  M: -  */
		voted_set_byte( var__ut_vote, 2, 2, &vote_byte );
		assert( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		data_reset( peek__ut_data_2, var__ut_vote );
		assert_not( voted_valid( var__ut_vote ), );
		/* I: 3  II: 2  III: 3  M: 3  */
		voted_set_byte( var__ut_vote, 1, 3, &vote_byte );
		voted_set_byte( var__ut_vote, 3, 3, &vote_byte );
		assert( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		data_reset( peek__ut_data_2, var__ut_vote );
		assert( voted_valid( var__ut_vote ), );
		assert_int_eq( 3, data_get_byte( var__ut_vote ), );
		/* I: 3  II: 3  III: 3  M: 3  */
		voted_set_byte( var__ut_vote, 2, 3, &vote_byte );
		assert_not( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		assert( voted_valid( var__ut_vote ), );
		assert_int_eq( 3, data_get_byte( var__ut_vote ), );
		/* I: 4  II: 3  III: 3  M: 3  */
		voted_set_byte( var__ut_vote, 1, 4, &vote_byte );
		assert_not( data_get_changed( peek__ut_data_2, var__ut_vote ), );
		assert( voted_valid( var__ut_vote ), );
		assert_int_eq( 3, data_get_byte( var__ut_vote ), );
		/* RESET */
		voted_set_byte( var__ut_vote, 3, 2, &vote_byte );
		data_reset( peek__ut_data_2, var__ut_vote );
	/* end */
	*co_p = &&L__END__ut_data_2;

	L__END__ut_data_2:
	
	return CO_END;
}

int ut_data_init( void )
{
	return ( CO_READY ); /* CO_SKIP */
}

void ut_data_uninit( void )
{
}

int coro_ut_data( co_t *co_p )
{
	static co_t co__ut_data_1;
	static co_t co__ut_data_2;
	if ( *co_p ) goto **co_p;
	/* begin */
	ut_2_begin();
	do {
		/* yield */
	
		*co_p = &&L__6;
	
		return CO_YIELD;

		L__6:;
	} while ( 0 );

	co__ut_data_1 = NULL;
	_ut_data_1_init();

	co__ut_data_2 = NULL;
	_ut_data_2_init();

	do {
		/* wait */
	
		*co_p = &&L__7;

		L__7:
		if (!(!(( coro__ut_data_1( &co__ut_data_1 ) | coro__ut_data_2( &co__ut_data_2 ) ) < CO_END ))) { /* cond */
		
			return CO_WAIT;
		}
	} while ( 0 );
	/* end */
	*co_p = &&L__END_ut_data;

	L__END_ut_data:
	
	return CO_END;
}

/** \} */