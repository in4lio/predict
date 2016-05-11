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
#define _EXT
#define _EXT_INIT( dec, init ) \
	dec = init
#define _INL extern inline
#else
#define _EXT extern
#define _EXT_INIT( dec, init ) \
	extern dec
#define _INL inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup rtc Real-time clock
 *  \ingroup hardware
 *  \{
 */

_EXT void rtc_init_clock( void );
_EXT int rtc_gettimeofday( struct timeval *ptimeval, void *ptimezone );

/** \} */

#ifdef __cplusplus
}
#endif

#undef _EXT
#undef _EXT_INIT
#undef _INL

#endif /* RTC_H */
