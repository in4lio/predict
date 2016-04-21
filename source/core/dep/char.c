
/*  char.c was generated by yup.py (yupp) 0.9b2
    out of char.yu-c 
 *//**
 *  \file  char.c (char.yu-c)
 *  \brief  Debug interface.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define CHAR_IMPLEMENT

#include "include.h"

/** \mainpage <CENTER><BR>predict - an embedded application framework</CENTER>

<CENTER><TT><BR>
                 _ _     _     <BR>
   ___ ___ ___ _| |_|___| |_   <BR>
  |   |  _   _|   | |  _   _|  <BR>
  |  _|_| |___ ___|_|___  |    <BR>
  |_|                   |_|    <BR><BR><BR><BR>
</TT></CENTER>
 */

/**
 *  \addtogroup char
 *  \{
 */

/**
 *  \brief Debug interface title message.
 *  \hideinitializer
 */
static const char * const TITLE = __CRLF__
#ifdef __CONSOLE_TITLE__
	__CONSOLE_TITLE__;
#else
	"               _ _     _   " __CRLF__
	" ___ ___ ___ _| |_|___| |_ " __CRLF__
	"|   |  _   _|   | |  _   _|" __CRLF__
	"|  _|_| |___ ___|_|___  |  " __CRLF__
	"|_|                   |_|  " __CRLF__;
#endif

/**
 *  \brief Program version format.
 *  \hideinitializer
 */
const char * const VERSION_STRING =
	__CRLF__ "predict" " " "0.3a2" " (" "0.3a2" ")"
	__CRLF__ "Compiled with " "gcc" " " __VERSION__;

/**
 *  \brief Input buffer.
 */
static char rx_buf[ RX_SIZE ];
static uint32_t rx_pos;
static bool is_msg;

#define FINE_BACKSPACE  "\x08\x20\x08"  /**< Sequence for delete last input char. \hideinitializer */
#define CLEAR_CMD       "                    \r" CONSOLE_PROMPT /**< Clear command line. \hideinitializer */

static const char USED_CHAR_LIST[] = "0123456789_abcdefghijklmnopqrstuvwxyz";

// UNIX //////////////////////////////////////////
#if defined( __linux__ )

#include <sys/ioctl.h>

static __inline void console_resol( void )
{
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
	console_row_count = w.ws_row;
	console_col_count = w.ws_col;
}

// WIN32 /////////////////////////////////////////
// MSDOS /////////////////////////////////////////
// CORTEX_M //////////////////////////////////////
#else
static __inline void console_resol( void )
{
}

//////////////////////////////////////////////////
#endif

/**
 *  \brief Print greeting and initialize debug interface.
 */
int receive_char_init( void )
{
	printf( TITLE );
	print_version();
	printf( __CRLF__ );

	rx_pos = 0;
	is_msg = false;

	char_echo = 1;
	getch_init();
	console_resol();

	return ( CO_READY ); /* CO_SKIP */
}

void receive_char_uninit( void )
{
	getch_uninit();
}

/**
 *  \brief Coroutine of message receiving on debug interface.
 */
int coro_receive_char( co_t *co_p )
{
	static int chr;
	if ( *co_p ) goto **co_p;
	/* begin */
	for ( ; ; ) {
		/* Wait character */
		do {
			/* wait */
			*co_p = &&L__0;

			L__0:
			if (!(( chr = getch_1()) != EOF )) { /* cond */
		
				return CO_WAIT;
			}
		} while ( 0 );

		switch ( getch_escseq( chr )) {

		case ESCSEQ_OK:
			if ( console_command_waited()  /* Console is waiting for command, no cyclic command, */
			&& ( rx_pos == 0 )) {          /* no one input character */
				/* Choose console command from list */
				printf( CLEAR_CMD );
				flush();
				switch ( chr ) {

				case CHAR_UP:
					console_index = ( console_index > 1 ) ? console_index - 1 : CONSOLE_COMMAND_COUNT - 1;
					goto up_or_down_l;

				case CHAR_DOWN:
					console_index = ( console_index < CONSOLE_COMMAND_COUNT - 1 ) ? console_index + 1 : 1;

				up_or_down_l:
					/* Print command */
					printf( "%s\r" CONSOLE_PROMPT_LIST, console_command[ console_index ]);
					flush();
					break;

				default:
					console_index = 0;
				}
			} else {
				char *p;

				/* Input message using only UP, DOWN and RIGHT arrows */
				switch ( chr ) {

				case CHAR_UP:    /* increase last entered char */
				case CHAR_DOWN:  /* decrease */
					if ( rx_pos == 0 ) break;

					p = strchr( USED_CHAR_LIST, rx_buf[ rx_pos - 1 ]);
					if ( p ) {
						if ( chr == CHAR_UP ) {
							chr = ( p[ 1 ]) ? p[ 1 ] : USED_CHAR_LIST[ 0 ];
						} else {
							chr = ( p == USED_CHAR_LIST ) ? USED_CHAR_LIST[ sizeof( USED_CHAR_LIST ) - 2 ] : *( p - 1 );
						}
					} else {
						chr = '0';
					}
					rx_buf[ rx_pos - 1 ] = chr;
					if ( char_echo ) {
						printf( "\x08%c", chr );
						flush();
					}
					break;

				case CHAR_RIGHT: /* enter 0 */
					if ( rx_pos == RX_SIZE - 1 ) break;

					chr = '0';
					rx_buf[ rx_pos++ ] = chr;
					if ( char_echo ) {
						printf( "%c", chr );
						flush();
					}
					break;
				}
			}
			break;

		case ESCSEQ_1:
			/* FIXME: unsuitable if ENTER returns both LF and CR */
			if ( console_index && ( chr != CHAR_ENTER )) {
				/* Reset command choice */
				console_index = 0;
				printf( CLEAR_CMD );
				flush();
			}
			/* Handle character */
			switch ( chr ) {

			case CHAR_SPACE ... LAST_CHAR:
				rx_buf[ rx_pos++ ] = chr;
				if ( char_echo ) {
					printf( "%c", chr );
					flush();
				}
				if ( rx_pos < RX_SIZE - 1 ) break;
				/* fallthrough */

			case CHAR_ENTER:
				is_msg = true;
				break;

			case CHAR_BACKSPACE:
				if ( rx_pos ) {
					--rx_pos;
					if ( char_echo ) {
						printf( FINE_BACKSPACE );
						flush();
					}
				}
				break;
			}
			break;
		}
		do {
			/* yield */
			*co_p = &&L__1;
	
			return CO_YIELD;

			L__1:;
		} while ( 0 );

		/* Prepare message */
		if ( is_msg ) {
			rx_buf[ rx_pos ] = 0;
			rx_pos = 0;
			char_received = rx_buf;
			is_msg = false;

			/* Wait message is handled */
			do {
				/* wait */
				*co_p = &&L__2;

				L__2:
				if (!( char_received == NULL )) { /* cond */
		
					return CO_WAIT;
				}
			} while ( 0 );
		}
	}
	/* end */
	*co_p = &&L__END_receive_char;

	L__END_receive_char:
	
	return CO_END;
}

void char_clear_input( void )
{
	rx_pos = 0;
}

void printhr( byte *data, uint32_t len, uint32_t cols )
{
	uint32_t i;

	if ( cols == 0 ) cols = 16;

	for ( i = 0; i < len; i++ ) {
		if (( i % cols ) == 0 ) printf( __CRLF__ );
		printf( "%02X ", data[ i ]);
	}
}

void printh( byte *data, uint32_t len )
{
	while ( len-- ) printf( "%02X ", data[ len ]);
}

void print_version( void )
{
	printf( VERSION_STRING );
}

/** \} */
