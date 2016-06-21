
/*  ini.h was generated by yup.py (yupp) 0.9b2
    out of ini.yu-h 
 *//**
 *  \file  ini.h (ini.yu-h)
 *  \brief  Configuration file.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#ifndef INI_H
#define INI_H

#ifdef  INI_IMPLEMENT
#define INI_EXT
#define INI_EXT_INIT( dec, init ) \
	dec = init
#define INI_INL
#else
#define INI_EXT extern
#define INI_EXT_INIT( dec, init ) \
	extern dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define INI_INL extern inline
#else
#define INI_INL inline
#endif
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup ini Configuration file
 *  \ingroup core
 *  \{
 */

/**
 *  \page ini Configuration file options
 *
 *  \section i_cyclic_delay cyclic_delay
 *  Interval of cyclic command execution (seconds).
 *
 *  \section i_data_prot data_prot
 *  Display protocol of state changing (flag).
 *
 *  \section i_data_prot_filter data_prot_filter
 *  Protocol displaying filter (substring is contained in variable name).
 *
 *  \section i_data_prot_filter_skip data_prot_filter_skip
 *  Protocol displaying filter (substring is absent in variable name).
 *
 *  \section i_log_path log_path
 *  Log-file name.
 *
 *  \section i_log_level log_level
 *  Logging level.
 */

INI_EXT_INIT( int ini_cyclic_delay, 5 );
INI_EXT_INIT( bool ini_data_prot, false );
INI_EXT_INIT( char ini_data_prot_filter[ 128 ], "" );
INI_EXT_INIT( char ini_data_prot_filter_skip[ 128 ], "_ut_" );
INI_EXT_INIT( char ini_log_path[ 64 ], "predict.log" );
INI_EXT_INIT( int ini_log_level, LOG_LEVEL_ERROR );

/**
 *  \brief Configuration file name.
 */
INI_EXT_INIT( char *ini_path, "./predict.cfg" );

INI_EXT bool ini_set_file( char *fn );

INI_EXT void ini_load( void );

INI_EXT void ini_save( void );

/** \} */

#ifdef __cplusplus
}
#endif

#endif

