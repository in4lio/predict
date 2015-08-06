
/*  app.c was generated by yup.py (yupp) 0.8b8
    out of app.yu-c at 2015-08-06 14:39
 *//**
 *  \file  app.c (app.yu-c)
 *  \brief  Application.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define APP_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup app
 *  \{
 */

#ifdef LINK_UT

/**
 *  \brief Get current time (for unit testing).
 */
static uint32_t ut_get_time( void )
{
	return ( clock_time_running() / 10 );
}

/**
 *  \brief Event handler of unit testing stage starting.
 *  \param t Stage of testing.
 */
static void ut_started( int t )
{
#ifdef LINK_CONSOLE
	if ( t == 1 ) char_retarding_fputc = 1;

#endif
}

/**
 *  \brief Event handler of unit testing stage completion.
 *  \param t Stage of testing.
 *  \param result Testing result.
 */
static void ut_finished( int t, bool result )
{
#ifdef LINK_CONSOLE
	if ( t == 1 ) char_retarding_fputc = 0;

#endif
	if ( !result ) ERROR( ut, t );
}

#endif

int app_init( int argc, char *argv[])
{
	if ( argc > 1 ) {
		ini_set_file( argv[ 1 ]);
	}
	clock_init();
	ini_load();

#ifdef LOGGING
	log_open( "a+" );

#endif

#ifdef LINK_UT
	ut_get_time_callback = ut_get_time;
	ut_started_callback = ut_started;
	ut_finished_callback = ut_finished;

#endif

	return ( 1 );
}

void app_uninit( void )
{
#ifdef LOGGING
	log_close();

#endif

}

/** \} */
