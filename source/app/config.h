
/*  config.h was generated by yup.py (yupp) 0.9b2
    out of config.yu-h 
 *//**
 *  \file  config.h (config.yu-h)
 *  \brief  Configuration.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef  CONFIG_IMPLEMENT
#define CONFIG_EXT
#define CONFIG_EXT_INIT( dec, init ) \
	dec = init
#else
#define CONFIG_EXT extern
#define CONFIG_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

/**
 *  \defgroup config Configuration
 *  \ingroup app
 *  \{
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

/** \} */

#endif

