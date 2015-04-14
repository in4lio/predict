
/*  app.h was generated by yup.py (yupp) 0.8b2
    out of app.yu-h at 2015-04-14 13:48
 *//**
 *  \file  app.h (app.yu-h)
 *  \brief  Application.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING

#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT

#define LINK_UT_CORO

#define LINK_UT_DATA

#ifndef APP_H
#define APP_H

#ifdef  APP_IMPLEMENT
#define APP_EXT
#define APP_EXT_INIT( dec, init ) \
	dec = init
#else
#define APP_EXT extern
#define APP_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup app Application
 *  \{
 */

/**
 *  \brief Show-must-go-on flag.
 */
APP_EXT int app_alive;

/**
 *  \brief Application exit status.
 */
APP_EXT_INIT( int app_return, 0 );

/**
 *  \brief Initialize application.
 */
APP_EXT int app_init( int argc, char *argv[]);

/**
 *  \brief Uninitialize application.
 */
APP_EXT void app_uninit( void );

/**
 *  \brief Debug interface title message.
 *  \hideinitializer
 */
;
/** \} */

#ifdef __cplusplus
}
#endif

#endif

