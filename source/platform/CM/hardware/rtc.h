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
#define _EXT_C
#define _EXT_C_INIT( dec, init ) \
	dec = init
#define _INL
#else
#define _EXT extern
#define _EXT_INIT( dec, init ) \
	extern dec
#ifdef __cplusplus
#define _C "C"
#else
#define _C
#endif
#define _EXT_C extern _C
#define _EXT_C_INIT( dec, init ) \
	extern _C dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define _INL extern inline
#else
#define _INL inline
#endif
#endif

/**
 *  \defgroup rtc Real-time clock
 *  \ingroup hardware
 *  \{
 */

_EXT_C void rtc_init_clock( void );
_EXT_C int rtc_gettimeofday( struct timeval *ptimeval, void *ptimezone );

/** \} */

#undef _EXT
#undef _EXT_INIT
#undef _EXT_C
#undef _EXT_C_INIT
#undef _INL
#undef _C
#endif /* RTC_H */
