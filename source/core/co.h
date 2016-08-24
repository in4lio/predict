
/*  co.h was generated by yup.py (yupp) 0.9b4
    out of co.yu-h 
 *//**
 *  \file  co.h (co.yu-h)
 *  \brief  Coroutines and unit tests declarations.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#ifndef CO_H
#define CO_H

#ifdef  CO_IMPLEMENT
#define CO_EXT
#define CO_EXT_INIT( dec, init ) \
	dec = init
#define CO_INL
#else
#define CO_EXT extern
#define CO_EXT_INIT( dec, init ) \
	extern dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define CO_INL extern inline
#else
#define CO_INL inline
#endif
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void * co_t;
typedef unsigned int semaphore_t;

enum {
	CO_READY,
	CO_WAIT,
	CO_YIELD,
	CO_END,
	CO_SKIP,
};

/**
 *  \defgroup coro Coroutines.
 *  \ingroup core
 *  \{
 */

/**
 *  \page coro List of coroutines
 *
 *  \section t_receive_char receive_char
 *  Coroutine of message receiving on debug interface.
 *
 *  \section t_console console
 *  Coroutine of debug console.
 *
 *  \section t_console_cyclic console_cyclic
 *  Coroutine of cyclic console commands.
 *
 *  \section t_ut_2 ut_2
 *  Coroutine of unit testing of 2nd stage.
 */

/** "receive_char" coroutine local context. */
CO_EXT_INIT( co_t co_receive_char, NULL );
/** "receive_char" coroutine alive flag. */
CO_EXT_INIT( int receive_char_alive, CO_SKIP );
/** "receive_char" coroutine. */
extern int coro_receive_char( co_t *co_p );
/** Initialize "receive_char" coroutine. */
extern int receive_char_init( void );
/** Uninitialize "receive_char" coroutine. */
extern void receive_char_uninit( void );
/** "console" coroutine local context. */
CO_EXT_INIT( co_t co_console, NULL );
/** "console" coroutine alive flag. */
CO_EXT_INIT( int console_alive, CO_SKIP );
/** "console" coroutine. */
extern int coro_console( co_t *co_p );
/** Initialize "console" coroutine. */
extern int console_init( void );
/** Uninitialize "console" coroutine. */
extern void console_uninit( void );
/** "console_cyclic" coroutine local context. */
CO_EXT_INIT( co_t co_console_cyclic, NULL );
/** "console_cyclic" coroutine alive flag. */
CO_EXT_INIT( int console_cyclic_alive, CO_SKIP );
/** "console_cyclic" coroutine. */
extern int coro_console_cyclic( co_t *co_p );
/** Initialize "console_cyclic" coroutine. */
extern int console_cyclic_init( void );
/** Uninitialize "console_cyclic" coroutine. */
extern void console_cyclic_uninit( void );
/** "ut_2" coroutine local context. */
CO_EXT_INIT( co_t co_ut_2, NULL );
/** "ut_2" coroutine alive flag. */
CO_EXT_INIT( int ut_2_alive, CO_SKIP );
/** "ut_2" coroutine. */
extern int coro_ut_2( co_t *co_p );
/** Initialize "ut_2" coroutine. */
extern int ut_2_init( void );
/** Uninitialize "ut_2" coroutine. */
extern void ut_2_uninit( void );

/** \} */

#ifdef LINK_UT

/**
 *  \addtogroup ut
 *  \{
 */

/**
 * \brief Restart unit testing of 2nd stage.
 */
extern void ut_2_restart( void );

/** "ut_ut" unit test of 1st stage. */
extern void ut_ut( void );
/** "ut_data" unit test of 1st stage. */
extern void ut_data( void );

/** "ut_coro" test coroutine alive flag. */
extern int ut_coro_alive;
/** "ut_data" test coroutine alive flag. */
extern int ut_data_alive;

/** \} */

#endif /* LINK_UT */

#ifdef __cplusplus
}
#endif

#endif

