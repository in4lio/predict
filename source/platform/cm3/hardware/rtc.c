/*                 _ _     _
	 ___ ___ ___ _| |_|___| |_
	|   |  _   _|   | |  _   _|
	|  _|_| |___ ___|_|___  |
	|_|                   |_|
 *//**
 *  \file  rtc.c
 *  \brief  Real-time clock (prototype).
 *  \author  Vitaly Kravtsov
 *  \copyright  See the LICENSE file.
 */

#define RTC_IMPLEMENT
#include "include.h"

#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_bkp.h"

/**
 *  \addtogroup rtc
 *  \{
 */

#define PRESCALER  32000

void rtc_init( void )
{
	/* Enable HSI clock for BKP control */
	RST_CLK_PCLKcmd( RST_CLK_PCLK_BKP, ENABLE );
	/* RTC reset */
	BKP_RTC_Reset( ENABLE );
	BKP_RTC_Reset( DISABLE );
	/* Configure LSI as RTC clock source */
	RST_CLK_LSIadjust( 12 );
	BKP_RTCclkSource( BKP_RTC_LSIclk );
	while ( RST_CLK_LSIstatus() != SUCCESS );
	/* Set RTC prescaler value */
	BKP_RTC_WaitForUpdate();
	BKP_RTC_SetPrescaler( PRESCALER );
	/* Set RTC counter value */
	BKP_RTC_WaitForUpdate();
	BKP_RTC_SetCounter( 0 );
	/* RTC enable */
	BKP_RTC_WaitForUpdate();
	BKP_RTC_Enable( ENABLE );
}

int rtc_gettimeofday( struct timeval* ptimeval, void* ptimezone __attribute__(( unused )))
{
	ptimeval->tv_sec = BKP_RTC_GetCounter();
	ptimeval->tv_usec = 0;
	return 0;
}

/** \} */
