
/*  log.c was generated by yup.py (yupp) 0.8b7
    out of log.yu-c at 2015-07-27 17:49
 *//**
 *  \file  log.c (log.yu-c)
 *  \brief  Logging.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING

#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT

#define LINK_UT_CORO

#define LINK_UT_DATA

#define LOG_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup log
 *  \{
 */

const char * const warn_format[] = {
	"Don't worry, be happy!",

};

const char * const info_format[] = {
	"Hello world!",

};

uint8_t error_repeat[] = {
	LOG_EVER,
	LOG_EVER,
	LOG_EVER,
	LOG_EVER,
	LOG_EVER,
	LOG_EVER,

};

uint8_t warn_repeat[] = {
	LOG_EVER,

};

uint8_t info_repeat[] = {
	LOG_ONCE,

};

void log_open( const char *mode )
{
	char s[ 32 ];
	char sd[ 32 ];
	struct timeval t;
	time_t sec;

	gettimeofday( &t, NULL );
	sec = t.tv_sec;
	strftime( sd, sizeof( sd ), "%d.%m.%Y", localtime( &sec ));

	clock_stamp( &t, s );

	log_file = fopen( ini_log_path, mode );
	if ( log_file == NULL ) {
		fprintf( stderr, "\nopen(\"%s\") failed: %s\n", ini_log_path, strerror( errno ));
		log_file = stderr;
	}
	fprintf( log_file, "\n\n%s\tlogging started %s", s, sd );
	fflush( log_file );
}

void log_close( void )
{
	char s[ 32 ];

	if ( log_file != NULL ) {
		fprintf( log_file, "\n%s\tlogging stopped", clock_stamp( NULL, s ));
		fclose( log_file );
		log_file = NULL;
	}
}

void log_clear( void )
{
	if ( log_lock_callback ) log_lock_callback();

	log_close();
	log_open( "wa" );
	log_printf( "INFO", "log cleaned" );

	if ( log_unlock_callback ) log_unlock_callback();
}

/** \} */
