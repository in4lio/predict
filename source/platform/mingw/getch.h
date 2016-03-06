
/*  getch.h was generated by yup.py (yupp) 0.9b1
    out of getch.yu-h at 2016-03-06 17:31
 *//**
 *  \file  getch.h (getch.yu-h)
 *  \brief  Read from debug interface.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#ifndef GETCH_H
#define GETCH_H

#ifdef  GETCH_IMPLEMENT
#define GETCH_EXT
#define GETCH_EXT_INIT( dec, init ) \
	dec = init
#else
#define GETCH_EXT extern
#define GETCH_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LINK_CONSOLE

#include <conio.h>

/**
 *  \addtogroup char
 *  \{
 */

GETCH_EXT void getch_init( void );
GETCH_EXT void getch_uninit( void );
GETCH_EXT int getch_1( void );
GETCH_EXT bool getch_esc( int chr );

/** \} */

#endif /* LINK_CONSOLE */

/**
 *  \defgroup char_char Characters definitions
 *  \ingroup char
 *  \{
 */

#define CHAR_TAB        '\x09'
#define CHAR_LF         '\x0A'
#define CHAR_CR         '\x0D'
#define CHAR_ESC        '\x1B'
#define CHAR_SPACE      '\x20'
#define LAST_CHAR       '\x7E'  /**< Last character to be displayed. */

#define CHAR_BACKSPACE  '\x08'
#define CHAR_UP         '\x48'
#define CHAR_DOWN       '\x50'
#define CHAR_RIGHT      '\x4D'
#define CHAR_LEFT       '\x4B'

#define CHAR_ENTER      CHAR_CR
#define __CRLF__        "\x0A"

/** \} */

#ifdef __cplusplus
}
#endif

#endif

