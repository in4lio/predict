
/*  main.c was generated by yup.py (yupp) 0.8b8
    out of main.yu-c at 2015-08-06 14:40
 *//**
 *  \file  main.c (main.yu-c)
 *  \brief  predict - an embedded application framework.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define CO_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup core
 *  \{
 */

/**
 *  \brief Initialize all coroutines.
 */
static void coro_init( void )
{
	co_receive_char = NULL;
	receive_char_alive = receive_char_init();
	co_console = NULL;
	console_alive = console_init();
	co_console_cyclic = NULL;
	console_cyclic_alive = console_cyclic_init();
	co_ut_2 = NULL;
	ut_2_alive = ut_2_init();

}

/**
 *  \brief Uninitialize all coroutines.
 */
static void coro_uninit( void )
{
	receive_char_uninit();
	console_uninit();
	console_cyclic_uninit();
	ut_2_uninit();

}

/**
 *  \brief Call coroutines according to dictionary.
 */
static int coro_schedule( void )
{
	if ( (( receive_char_alive ) < CO_END ) ) receive_char_alive = coro_receive_char( &co_receive_char );
	if ( (( console_alive ) < CO_END ) ) console_alive = coro_console( &co_console );
	if ( (( console_cyclic_alive ) < CO_END ) ) console_cyclic_alive = coro_console_cyclic( &co_console_cyclic );
	if ( (( ut_2_alive ) < CO_END ) ) ut_2_alive = coro_ut_2( &co_ut_2 );

	return ( 1
	|| (( receive_char_alive ) < CO_END )
	|| (( console_alive ) < CO_END )
	|| (( console_cyclic_alive ) < CO_END )
	|| (( ut_2_alive ) < CO_END )

	);
}

#ifdef LINK_UT

/**
 *  \brief 1st stage of unit testing (before coroutines call loop).
 */
static void ut_1( void )
{
	ut_ut();

}

#endif /* LINK_UT */

/**
 *  \brief Application life-cycle.
 */
int main( int argc, char *argv[])
{
	app_alive = app_init( argc, argv );
	coro_init();

#ifdef LINK_UT
	ut_stage_1( ut_1 );

#endif
	/* Coroutines call loop */
	while ( app_alive ) {
		if ( coro_schedule() == 0 ) break;
		/* usleep( 2 );
		 */
	}
	coro_uninit();
	app_uninit();

	return ( app_return );
}

/** \} */
