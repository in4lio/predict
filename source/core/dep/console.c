
/*  console.c was generated by yup.py (yupp) 0.9b2
    out of console.yu-c 
 *//**
 *  \file  console.c (console.yu-c)
 *  \brief  Debug console.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define CONSOLE_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup console
 *  \{
 */

const char * const console_command[] = {
	"",
	"c_delay",
	"data",
	"d_flt",
	"d_get",
	"d_list",
	"d_prot",
	"d_set",
	"help",
	"ini",
	"quit",
	"stop",
	"time",
	"ut",
	"u_result",
	"version",

};

/**
 *  \brief Console commands identifiers.
 */
enum {
	id_NONE = 0,
	id_c_delay,
	id_data,
	id_d_flt,
	id_d_get,
	id_d_list,
	id_d_prot,
	id_d_set,
	id_help,
	id_ini,
	id_quit,
	id_stop,
	id_time,
	id_ut,
	id_u_result,
	id_version,

	id_WRONG
};

/**
 *  \brief Command parameters identifiers.
 */
enum {
	par_none = 0,
	par_c_delay, par_c_delay_0 = par_c_delay, 
		
	par_d_flt, par_d_flt_0 = par_d_flt, 
	par_d_get, par_d_get_0 = par_d_get, 
		
	par_d_prot, par_d_prot_0 = par_d_prot, 
	par_d_set, par_d_set_0 = par_d_set, par_d_set_1, 
		
	par_quit, par_quit_0 = par_quit, 
		
};

enum {
	cyclic_job_none = 0,
	cyclic_job_data,
	cyclic_job_time,

};

/**
 *  \brief Console state flags.
 */
enum {
	stt_CMD_WAIT,  /**< Wait for command. */
	stt_PAR_WAIT,  /**< Wait for command parameter. */
	stt_PAR_PARSE  /**< Handle parameter. */
};

/**
 *  \brief Console state.
 */
static int stt;

static int arg_wanted;
static char *arg_current;
static char arg[ 6 ][ RX_SIZE ];
static int arg_count;
static int arg_i;

enum {
	cyclic_stt_IDLE,
	cyclic_stt_START,
	cyclic_stt_EXEC,
	cyclic_stt_STOP
};

/**
 *  \brief Cyclic command state.
 */
static int cyclic_stt;

/**
 *  \brief Current cyclic command.
 */
static int cyclic_job;

/* Temporary variables */
static int val_int;
static void *val_ptr;
static uint32_t __uint;
static char __str[ 100 ];

static char *error;

#define msg_ERROR    __CRLF__"*** ERROR - wrong %s ***"
#define msg_CONFIRM  __CRLF__"  confirm %s (1): "

static void parse_cmd( const char *msg );
static void parse_par( const char *msg );
static int search_cmd( const char *msg );
static void wait_par( int par );
static int cyclic_start( void );
static int cyclic_exec( void );
static void cyclic_stop( void );
static bool __partoul( const char *s, uint32_t *result );

#if __PAR_64
static bool __partoull( const char *s, uint64_t *result );

#endif

#define START_CYCLIC( job ) do { \
	if ( cyclic_stt == cyclic_stt_IDLE ) { \
		cyclic_job = cyclic_job_##job; \
		cyclic_stt = cyclic_stt_START; \
	} else { \
		if ( cyclic_job == cyclic_job_##job ) { \
			cyclic_stt = cyclic_stt_STOP; \
		} \
	} \
} while ( 0 )

/**
 *  \brief Convert and check unsigned integer parameter.
 *  \hideinitializer
 */
#define msg_to__uint( MIN, MAX ) \
	( __partoul( msg, &__uint ) && ( __uint >= ( MIN )) && ( __uint <= ( MAX )))

/**
 *  \brief Convert and check unsigned integer parameter (MIN is 0).
 *  \hideinitializer
 */
#define msg_to__uint_0( MAX ) \
	( __partoul( msg, &__uint ) && ( __uint <= ( MAX )))

/* Command handles */
/**
 *  \brief Interval of cyclic command execution.
 */
static __inline void handle_cmd_c_delay( void )
{
	printf(
	__CRLF__"  cyclic_delay = %d"
	__CRLF__"  value (" __stringify( cyclic_delay_MIN )
	               ".." __stringify( cyclic_delay_MAX ) "): "
	, ini_cyclic_delay
	);
	wait_par( par_c_delay );
}

static __inline void handle_par_c_delay_0( const char *msg )
{
	if ( msg_to__uint( cyclic_delay_MIN, cyclic_delay_MAX )) {
		ini_cyclic_delay = __uint;
	} else {
		error = "value";
	}
}

#define __D_PER_CYCLE  10

static uint32_t __d_from;
static bool __d_value;
static bool __d_exclude;
static char __d_filter[ RX_SIZE ];
static uint16_t __cyclic_delay;

/**
 *  \brief Application state-space representation.
 */
static __inline void handle_cmd_data( void )
{
	__d_value = true;
	START_CYCLIC( data );
}

static __inline int cyclic_start_data( void )
{
	__cyclic_delay = ini_cyclic_delay;
	ini_cyclic_delay = 1;
	__d_filter[ 0 ] = '\0';
	__d_exclude = false;
	__d_from = 0;
	if ( arg_count == 1 ) {
		if ( arg[ 0 ][ 0 ] == '-' ) {
			__d_exclude = true;
			if ( arg[ 0 ][ 1 ] != '\0' ) {
				strcpy( __d_filter, arg[ 0 ] + 1 );
			}
		} else {
			strcpy( __d_filter, arg[ 0 ]);
		}
	}
	return cyclic_stt_EXEC;
}

static __inline int cyclic_exec_data( void )
{
	char *var;
	int i;
	int j = 0;

	for ( i = __d_from; i < var_COUNT; i++ ) {
		var = data_vartoa( i );

		if (( __d_filter[ 0 ] == '\0' ) || ( !strstr( var, __d_filter ) == __d_exclude )) {
			printf( __CRLF__"        %-22s  %s"
			, var
			, ( __d_value ) ? data_get_string( __str, i ) : data_get_type( i )
			);
			if ( ++j == __D_PER_CYCLE ) {
				__d_from = i + 1;
				return cyclic_stt_EXEC;
			}
		}
	}
	ini_cyclic_delay = __cyclic_delay;
	printf( __CRLF__ CONSOLE_PROMPT );
	flush();
	return cyclic_stt_STOP;
}

static __inline void cyclic_stop_data( void )
{

}

/**
 *  \brief Filter of state changing protocol.
 */
static __inline void handle_cmd_d_flt( void )
{
	printf( __CRLF__"  p_flt = (%s) -(%s)"
	, ( *ini_data_prot_filter ) ? ini_data_prot_filter : "*"
	, ( *ini_data_prot_filter_skip ) ? ini_data_prot_filter_skip : ""
	);
	printf( __CRLF__"  value (substr -substr * -): " );
	wait_par( par_d_flt );
}

static __inline void handle_par_d_flt_0( const char *msg )
{
	if ( *msg == '-' ) {
		val_ptr = ini_data_prot_filter_skip;
		++msg;
	} else {
		val_ptr = ini_data_prot_filter;
	}
	if (( *msg == '\0' ) || ( strchr( msg, '*' ) != 0 )) {
		*( char *) val_ptr = '\0';
	} else {
		strcpy( val_ptr, msg );
	}
	printf( __CRLF__"  p_flt = (%s) -(%s)"
	, ( *ini_data_prot_filter ) ? ini_data_prot_filter : "*"
	, ( *ini_data_prot_filter_skip ) ? ini_data_prot_filter_skip : ""
	);
}

/**
 *  \brief Get value of state variable.
 */
static __inline void handle_cmd_d_get( void )
{
	printf( __CRLF__"  name: " );
	wait_par( par_d_get );
}

static __inline void handle_par_d_get_0( const char *msg )
{
	val_int = data_atovar( msg );
	if ( val_int < var_COUNT ) {
		printf( __CRLF__"  %s = %s", msg, data_get_string( __str, val_int ));
	} else {
		error = "name";
	}
}

/**
 *  \brief List of state variables.
 */
static __inline void handle_cmd_d_list( void )
{
	__d_value = false;
	START_CYCLIC( data );
}

/**
 *  \brief Display protocol of state changing.
 */
static __inline void handle_cmd_d_prot( void )
{
	printf(
	__CRLF__"  data_prot = %d"
	__CRLF__"  value (0..1): "
	, ini_data_prot
	);
	wait_par( par_d_prot );
}

static __inline void handle_par_d_prot_0( const char *msg )
{
	if ( msg_to__uint_0( 1 )) {
		ini_data_prot = __uint;

		printf( __CRLF__"  data_prot = %d", ini_data_prot );
	} else {
		error = "value";
	}
}

/**
 *  \brief Set value of state variable.
 */
static __inline void handle_cmd_d_set( void )
{
	printf( __CRLF__"  name: " );
	wait_par( par_d_set );
}

static __inline void handle_par_d_set_0( const char *msg )
{
	val_int = data_atovar( msg );
	if ( val_int < var_COUNT ) {
		printf( __CRLF__"  %s = %s", msg, data_get_string( __str, val_int ));
		printf( __CRLF__"  value: " );
		wait_par( par_d_set_1 );
	} else {
		error = "name";
	}
}

static __inline void handle_par_d_set_1( const char *msg )
{
	data_set_string( val_int, msg );
	printf( __CRLF__"  %s = %s", data_vartoa( val_int ), data_get_string( __str, val_int ));
}

/**
 *  \brief List of console commands.
 */
static __inline void handle_cmd_help( void )
{
	int i;
	char last = ' ';

	for ( i = 0; i < CONSOLE_COMMAND_COUNT; i++ ) {
		if ( last != *console_command[ i ]) {
			printf( __CRLF__"  " );
			last = *console_command[ i ];
		}
		printf( "%s ", console_command[ i ]);
	}
}

/**
 *  \brief Save program settings.
 */
static __inline void handle_cmd_ini( void )
{
	ini_save();
	printf( __CRLF__"*** %s saved ***", ini_path );
}

/**
 *  \brief Quit program.
 */
static __inline void handle_cmd_quit( void )
{
	printf( msg_CONFIRM, "quit" );
	arg_count = 0;
	wait_par( par_quit );
}

static __inline void handle_par_quit_0( const char *msg )
{
	if ( msg_to__uint( 1, 1 )) {
		char_echo = 0;
		app_alive = 0;
	}
}

/**
 *  \brief Stop cyclic command execution.
 */
static __inline void handle_cmd_stop( void )
{
	if ( cyclic_stt == cyclic_stt_EXEC ) cyclic_stt = cyclic_stt_STOP;
}

/**
 *  \brief Current time.
 */
static __inline void handle_cmd_time( void )
{
	if (( arg_count == 1 ) && ( strcmp( arg[ 0 ], "1" ) == 0 )) {
		printf( __CRLF__"  %s", clock_stamp_short( __str ));
	} else {
		START_CYCLIC( time );
	}
}

static __inline int cyclic_start_time( void )
{
	return cyclic_stt_EXEC;
}

static __inline int cyclic_exec_time( void )
{
	if ( char_echo ) {
		return cyclic_stt_STOP;
	}
	printf( "\r%s    \r", clock_stamp_short( __str ));
	return cyclic_stt_EXEC;
}

static __inline void cyclic_stop_time( void )
{

}

#ifdef LINK_UT

/**
 *  \brief Restart unit testing of 2nd stage.
 */
static __inline void handle_cmd_ut( void )
{
	ut_2_restart();
}

/**
 *  \brief Unit testing result.
 */
static __inline void handle_cmd_u_result( void )
{
	ut_print_statistics();
}

#endif

/**
 *  \brief Program version.
 */
static __inline void handle_cmd_version( void )
{
	print_version();
}

int console_init( void )
{
	console_index = 0;
	stt = stt_CMD_WAIT;
	arg_count = 0;
	arg_i = 0;

	return ( CO_READY ); /* CO_SKIP */
}

void console_uninit( void )
{
	printf( __CRLF__"*** ( " "predict" " ) Bye! ***"__CRLF__ );
}

/**
 *  \brief Coroutine of debug console.
 */
int coro_console( co_t *co_p )
{
	
	if ( *co_p ) goto **co_p;
	/* begin */
	/* Greeting */
	printf(
	__CRLF__"*** ( " "predict" " ) Hello! ***"
	__CRLF__ CONSOLE_PROMPT
	);
	flush();

	for ( ; ; ) {
		switch ( stt ) {

		case stt_CMD_WAIT:

			do {
				/* wait */
				*co_p = &&L__0;

				L__0:
				if (!( char_received )) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );  /* Wait for received message */
			parse_cmd( char_received );     /* Handle command */
			break;

		case stt_PAR_WAIT:

			do {
				/* wait */
				*co_p = &&L__1;

				L__1:
				if (!( char_received )) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );  /* Wait for received message */
			arg_current = char_received;
			/* fallthrough */

		case stt_PAR_PARSE:

			parse_par( arg_current );       /* Handle parameter */
			break;
		}
		char_received = NULL;               /* Reset received message */

		if ( stt == stt_CMD_WAIT ) {
			if ( char_echo ) {
				printf( __CRLF__ CONSOLE_PROMPT );
				flush();
			} else {
				printf( __CRLF__ );
			}
		}
	}
	/* end */
	*co_p = &&L__END_console;

	L__END_console:
	
	return CO_END;
}

int console_cyclic_init( void )
{
	cyclic_stt = cyclic_stt_IDLE;

	return ( CO_READY ); /* CO_SKIP */
}

void console_cyclic_uninit( void )
{
}

/**
 *  \brief Coroutine of cyclic console commands.
 */
int coro_console_cyclic( co_t *co_p )
{
	static struct timeval t_cycle = { 0, 0 };
	if ( *co_p ) goto **co_p;
	/* begin */
	for ( ; ; ) {
		switch ( cyclic_stt ) {

		/* Initialize cyclic command */
		case cyclic_stt_START:

			cyclic_stt = cyclic_start();
			if ( cyclic_stt != cyclic_stt_EXEC ) break;

			char_echo = 0;
			/* fallthrough */

		/* Execute cyclic command */
		case cyclic_stt_EXEC:

			if ( clock_time_before( t_cycle )) break;

			cyclic_stt = cyclic_exec();
			if ( cyclic_stt != cyclic_stt_EXEC ) break;

			t_cycle = clock_t_set( ini_cyclic_delay * TICK_PER_SEC );
			break;

		/* Stop cyclic command */
		case cyclic_stt_STOP:

			cyclic_stop();
			cyclic_stt = cyclic_stt_IDLE;
			char_echo = 1;
			break;
		}
		do {
			/* yield */
			*co_p = &&L__2;
	
			return CO_YIELD;

			L__2:;
		} while ( 0 );
	}
	/* end */
	*co_p = &&L__END_console_cyclic;

	L__END_console_cyclic:
	
	return CO_END;
}

void console_prompt( void )
{
	if ( char_echo ) {
		if ( stt == stt_CMD_WAIT ) {
			char_clear_input();
			console_index = 0;
			printf( __CRLF__ CONSOLE_PROMPT );
			flush();
		} else {
			printf( __CRLF__ );
		}
	}
}

bool console_command_waited( void )
{
	return (( stt == stt_CMD_WAIT ) && ( cyclic_stt == cyclic_stt_IDLE ));
}

/**
 *  \brief Handle command.
 *  \param Received message.
 */
static void parse_cmd( const char *msg )
{
	char_echo = 1;

	switch( search_cmd( msg )) {

	case id_c_delay:
		handle_cmd_c_delay();
		break;
	case id_data:
		handle_cmd_data();
		break;
	case id_d_flt:
		handle_cmd_d_flt();
		break;
	case id_d_get:
		handle_cmd_d_get();
		break;
	case id_d_list:
		handle_cmd_d_list();
		break;
	case id_d_prot:
		handle_cmd_d_prot();
		break;
	case id_d_set:
		handle_cmd_d_set();
		break;
	case id_help:
		handle_cmd_help();
		break;
	case id_ini:
		handle_cmd_ini();
		break;
	case id_quit:
		handle_cmd_quit();
		break;
	case id_stop:
		handle_cmd_stop();
		break;
	case id_time:
		handle_cmd_time();
		break;
	case id_ut:
		handle_cmd_ut();
		break;
	case id_u_result:
		handle_cmd_u_result();
		break;
	case id_version:
		handle_cmd_version();
		break;

	/* Empty command */
	case id_NONE:
		break;

	default:
		printf( __CRLF__"( unknown )" );
	}
}

/**
 *  \brief Handle command parameter.
 *  \param Received message.
 */
static void parse_par( const char *msg )
{
	stt = stt_CMD_WAIT;
	if ( strlen( msg ) == 0 ) return;

	switch ( arg_wanted ) {

	case par_c_delay_0:
		error = NULL;
		handle_par_c_delay_0( msg );
		if ( error ) goto l_error;
		break;

	case par_d_flt_0:
		error = NULL;
		handle_par_d_flt_0( msg );
		if ( error ) goto l_error;
		break;

	case par_d_get_0:
		error = NULL;
		handle_par_d_get_0( msg );
		if ( error ) goto l_error;
		break;

	case par_d_prot_0:
		error = NULL;
		handle_par_d_prot_0( msg );
		if ( error ) goto l_error;
		break;

	case par_d_set_0:
		error = NULL;
		handle_par_d_set_0( msg );
		if ( error ) goto l_error;
		break;
	case par_d_set_1:
		error = NULL;
		handle_par_d_set_1( msg );
		if ( error ) goto l_error;
		break;

	case par_quit_0:
		error = NULL;
		handle_par_quit_0( msg );
		if ( error ) goto l_error;
		break;

	/* Print error message */
	l_error:
		printf( msg_ERROR, error );
		break;

	default:
		printf( __CRLF__"( unknown )" );
	}
}

/**
 *  \brief Search command which starts with specified string.
 *  \param Received message.
 *  \return Command identifier.
 */
static int search_cmd( const char *msg )
{
	int len;
	int i;
	int result = id_NONE;
	int count = 0;
	char cmd[ RX_SIZE ];

	if ( strlen( msg ) == 0 ) {
		if (( console_index > 0 ) && ( console_index < CONSOLE_COMMAND_COUNT )) {
			/* Command has been selected from list */
			msg = console_command[ console_index ];
			console_index = 0;
		} else {
			/* Empty command */
			return ( id_NONE );
		}
	}
	/* Split command line */
	arg_count = sscanf( msg, "%s %s %s %s %s %s %s", cmd
	, arg[ 0 ], arg[ 1 ], arg[ 2 ], arg[ 3 ], arg[ 4 ], arg[ 5 ]) - 1;
	arg_i = 0;
	if (( len = strlen( cmd )) == 0 ) return ( id_NONE );

	/* Check full match */
	for ( i = 1; i < CONSOLE_COMMAND_COUNT; i++ ) {
		if ( strcmp( cmd, console_command[ i ]) == 0 ) {
			printf( __CRLF__"( %s )", cmd );

			return ( i );  /* Command found */
		}
	}
	/* Checking partial match */
	for ( i = 1; i < CONSOLE_COMMAND_COUNT; i++ ) {
		if ( strncmp( cmd, console_command[ i ], len ) == 0 ) {
			if ( ++count == 1 ) {
				/* First match */
				result = i;
				printf( __CRLF__"( " );
			}
			printf( "%s ", console_command[ i ]);
		}
	}
	if ( count ) {
		printf( ")" );

		return (( count == 1 ) ? result : id_NONE );
	}

	return ( id_WRONG );  /* Command not found */
}

/**
 *  \brief Wait for command parameter.
 *  \param par Parameter identifier.
 */
static void wait_par( int par )
{
	arg_wanted = par;

	if ( arg_i < arg_count ) {
		stt = stt_PAR_PARSE;
		arg_current = arg[ arg_i ];
		printf( arg_current );
		++arg_i;
	} else {
		stt = stt_PAR_WAIT;
		arg_count = 0;
	}
}

/**
 *  \brief Initialize cyclic command.
 *  \return Cyclic command state.
 */
static int cyclic_start( void )
{
	switch ( cyclic_job ) {

	case cyclic_job_data:
		return cyclic_start_data();
	case cyclic_job_time:
		return cyclic_start_time();

	default:
		return cyclic_stt_IDLE;
	}
}

/**
 *  \brief Execute cyclic command.
 *  \return Cyclic command state.
 */
static int cyclic_exec( void )
{
	switch ( cyclic_job ) {

	case cyclic_job_data:
		return cyclic_exec_data();
	case cyclic_job_time:
		return cyclic_exec_time();

	default:
		return cyclic_stt_IDLE;
	}
}

/**
 *  \brief Stop cyclic command.
 */
static void cyclic_stop( void )
{
	switch ( cyclic_job ) {

	case cyclic_job_data:
		cyclic_stop_data();
		return;
	case cyclic_job_time:
		cyclic_stop_time();
		return;

	}
}

/**
 *  \brief Convert parameter string to unsigned integer.
 *  \param s String buffer.
 *  \param result Result pointer.
 *  \return Successful converting flag.
 */
static bool __partoul( const char *s, uint32_t *result )
{
	char *end;

	*result = strtoul( s, &end, 0 );
	return ( *end == '\0' );
}

#if __PAR_64
static bool __partoull( const char *s, uint64_t *result )
{
	char *end;

	*result = strtoull( s, &end, 0 );
	return ( *end == '\0' );
}

#endif

/** \} */
