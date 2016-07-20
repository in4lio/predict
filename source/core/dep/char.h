
/*  char.h was generated by yup.py (yupp) 0.9b3
    out of char.yu-h 
 *//**
 *  \file  char.h (char.yu-h)
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

#ifndef CHAR_H
#define CHAR_H

#ifdef  CHAR_IMPLEMENT
#define CHAR_EXT
#define CHAR_EXT_INIT( dec, init ) \
	dec = init
#define CHAR_INL
#else
#define CHAR_EXT extern
#define CHAR_EXT_INIT( dec, init ) \
	extern dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define CHAR_INL extern inline
#else
#define CHAR_INL inline
#endif
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LINK_CONSOLE

/**
 *  \defgroup char Debug interface
 *  \ingroup console
 *  \{
 */

#define ESCSEQ_INSIDE  0  /**< Inside of escape sequence. \hideinitializer */
#define ESCSEQ_1       1  /**< Single character. \hideinitializer */
#define ESCSEQ_OK      2  /**< Last character of escape sequence. \hideinitializer */

#define RX_SIZE  80  /**< Size of input buffer. \hideinitializer */

/**
 *  \brief Received message pointer.
 *  \note Must be reset in NULL after message handling.
 */
CHAR_EXT char *char_received;

/**
 *  \brief Flag of displaying of received characters.
 */
CHAR_EXT int char_echo;

/**
 *  \brief Clear input message.
 */
CHAR_EXT void char_clear_input( void );

/**
 *  \brief Print data in hex format.
 *  \param data Data pointer.
 *  \param len Data length.
 */
CHAR_EXT void printh( byte *data, uint32_t len );

/**
 *  \brief Print data in hex format by columns.
 *  \param data Data pointer.
 *  \param len Data length.
 *  \param cols Columns count.
 */
CHAR_EXT void printhr( byte *data, uint32_t len, uint32_t cols );

/**
 *  \brief Print program version.
 */
CHAR_EXT void print_version( void );

/** \} */

#endif /* LINK_CONSOLE */

/**
 *  \brief Flush output.
 */
extern void flush( void );

/**
 *  \brief Print message.
 *  \param PRE Message type.
 *  \param FORMAT Message format.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define __echo( PRE, FORMAT, ... ) do { \
	printf( __CRLF__ "*** " PRE " *** %s() %s (%d)" __CRLF__ "    " FORMAT, \
	__FUNCTION__, __FILE__, __LINE__, ## __VA_ARGS__ ); \
} while ( 0 )

/**
 *  \brief Print message about function call.
 *  \param FORMAT Message format.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define __echo_call( FORMAT, ... ) __echo( "CALL", FORMAT, ## __VA_ARGS__ )

/**
 *  \brief Print debug message.
 *  \param FORMAT Message format.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define __echo_debug( FORMAT, ... ) __echo( "INFO", FORMAT, ## __VA_ARGS__ )

/**
 *  \brief Print warning.
 *  \param FORMAT Message format.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define __echo_warn( FORMAT, ... ) do { \
	__echo( "WARN", ); \
	printf( FORMAT, ## __VA_ARGS__ ); \
	flush(); \
} while ( 0 )

/**
 *  \brief Print error.
 *  \param FORMAT Message format.
 *  \param err Error number.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define __echo_error( FORMAT, err, ... ) do { \
	__echo( "ERROR #%X", COMMA err ); \
	printf( FORMAT, ## __VA_ARGS__ ); \
	flush(); \
} while ( 0 )

/**
 *  \brief Console width.
 */
CHAR_EXT_INIT( int console_col_count, 80 );

/**
 *  \brief Console height.
 */
CHAR_EXT_INIT( int console_row_count, 25 );

#ifdef __cplusplus
}
#endif

#endif

