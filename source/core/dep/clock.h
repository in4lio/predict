
/*  clock.h was generated by yup.py (yupp) 1.0b4
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
#define CLOCK_EXT_C
#define CLOCK_EXT_C_INIT( dec, init ) \
	dec = init
#define CLOCK_INL
#else
#define CLOCK_EXT extern
#define CLOCK_EXT_INIT( dec, init ) \
	extern dec
#ifdef __cplusplus
#define CLOCK_C "C"
#else
#define CLOCK_C
#endif
#define CLOCK_EXT_C extern CLOCK_C
#define CLOCK_EXT_C_INIT( dec, init ) \
	extern CLOCK_C dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define CLOCK_INL extern inline
#else
#define CLOCK_INL inline
#endif
#endif

#ifndef COMMA
#define COMMA ,
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
CLOCK_EXT_C void clock_init( void );

/**
 *  \brief Time to string converting.
 *  \param tval time pointer (current time is used in case of NULL).
 *  \param s String buffer.
 *  \return String.
 */
CLOCK_EXT_C const char *clock_stamp( const struct timeval *tval, char *s );

/**
 *  \brief Current time to string converting without centiseconds.
 *  \param s String buffer.
 *  \return String.
 */
CLOCK_EXT_C const char *clock_stamp_short( char *s );

/**
 *  \brief Current datetime to string converting without centiseconds.
 *  \param sd String buffer for date.
 *  \param st String buffer for time.
 *  \return Current datetime.
 */
CLOCK_EXT_C time_t clock_stamp_datetime( char* sd, char* st );

/**
 *  \brief Current time setup.
 *  \param Hours.
 *  \param m Minutes.
 *  \param s Seconds.
 *  \param cs Centiseconds.
 *  Function is not implemented.
 */
CLOCK_EXT_C void clock_set_time( uint32_t h, uint32_t m, uint32_t s, uint32_t cs );

/**
 *  \brief Get time of program running (max 497 days).
 *  \return Time in centiseconds.
 */
CLOCK_EXT_C uint32_t clock_time_running( void );

/**
 *  \brief Calculate time when timer interval has expired (timeout).
 *  \param ms Interval in milliseconds.
 *  \return Timeout.
 */
CLOCK_EXT_C struct timeval clock_t_set( const int ms );

CLOCK_EXT_C void __clock_t_add( struct timeval *t, const int ms );
CLOCK_EXT_C int __clock_time_after( struct timeval *t );
CLOCK_EXT_C int __clock_t_rest( struct timeval *t );

/**
 *  \brief Prolong timeout.
 *  \param t Timeout.
 *  \param ms Additional interval in milliseconds.
 */
#define clock_t_add( t, ms ) __clock_t_add(&( t ), ( ms ))

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

#undef CLOCK_EXT
#undef CLOCK_EXT_INIT
#undef CLOCK_EXT_C
#undef CLOCK_EXT_C_INIT
#undef CLOCK_INL
#undef CLOCK_C
#endif

