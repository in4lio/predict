/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  rtc.h
 *  \brief  Real-time clock (prototype).
 *  \author  Vitaly Kravtsov
 *  \copyright  See the LICENSE file.
 */

#ifndef RTC_H
#define RTC_H

#ifdef  RTC_IMPLEMENT
#define RTC_EXT
#define RTC_EXT_INIT( dec, init ) \
	dec = init
#else
#define RTC_EXT extern
#define RTC_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup rtc Real-time clock
 *  \{
 */

RTC_EXT void rtc_init_clock( void );
RTC_EXT int rtc_gettimeofday( struct timeval *ptimeval, void *ptimezone );

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* RTC_H */
