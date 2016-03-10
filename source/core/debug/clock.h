
/*  clock.h was generated by yup.py (yupp) 0.9b2
    out of clock.yu-h 
 *//**
 *  \file  clock.h (clock.yu-h)
 *  \brief  Real-time clock.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#ifndef CLOCK_H
#define CLOCK_H

#ifdef  CLOCK_IMPLEMENT
#define CLOCK_EXT
#define CLOCK_EXT_INIT( dec, init ) \
	dec = init
#else
#define CLOCK_EXT extern
#define CLOCK_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup hardware Hardware
 *  \{
 *
 *  \defgroup clock Real-time clock
 *  \{
 */

#define TICK_PER_SEC  1000  /**< Ticks per second. \hideinitializer */

/**
 *  \brief Initialize clock.
 */
CLOCK_EXT void clock_init( void );

/**
 *  \brief time-to-string converting.
 *  \param tval time pointer (current time is used in case of NULL).
 *  \param str String buffer.
 *  \return String.
 */
CLOCK_EXT const char *clock_stamp( const struct timeval *tval, char *str );

/**
 *  \brief time-to-string converting without centiseconds.
 *  \param str String buffer.
 *  \return String.
 */
CLOCK_EXT const char *clock_stamp_short( char *str );

/**
 *  \brief Current time setup.
 *  \param Hours.
 *  \param m Minutes.
 *  \param s Seconds.
 *  \param cs Centiseconds.
 *  Function is not implemented.
 */
CLOCK_EXT void clock_set_time( uint32_t h, uint32_t m, uint32_t s, uint32_t cs );

/**
 *  \brief Get time of program running.
 *  \return Time in centiseconds.
 */
CLOCK_EXT uint32_t clock_time_running( void );

/**
 *  \brief Calculate time when timer interval has expired (timeout).
 *  \param mc Interval in milliseconds.
 *  \return Timeout.
 */
CLOCK_EXT struct timeval clock_t_set( const int mc );

CLOCK_EXT void __clock_t_add( struct timeval *t, const int mc );
CLOCK_EXT int __clock_time_after( struct timeval *t );
CLOCK_EXT int __clock_t_rest( struct timeval *t );

/**
 *  \brief Prolong timeout.
 *  \param t Timeout.
 *  \param mc Additional interval in milliseconds.
 */
#define clock_t_add( t, mc ) __clock_t_add(&( t ), ( mc ))

/**
 *  \brief Check timeout.
 *  \param t Timeout.
 *  \return Timeout flag.
 */
#define clock_time_after( t ) __clock_time_after( &( t ))

/**
 *  \brief Check timeout.
 *  \param t Timeout.
 *  \return NO timeout flag.
 */
#define clock_time_before( t ) ( !clock_time_after( t ))

/**
 *  \brief Calculate remaining time until timeout.
 *  \param t Timeout.
 *  \return Remaining time.
 */
#define clock_t_rest( t ) __clock_t_rest( &( t ))

/** \} */

/** \} */

#ifdef __cplusplus
}
#endif

#endif

