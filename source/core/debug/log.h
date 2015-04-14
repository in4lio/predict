
/*  log.h was generated by yup.py (yupp) 0.8b2
    out of log.yu-h at 2015-04-14 13:48
 *//**
 *  \file  log.h (log.yu-h)
 *  \brief  Logging.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING

#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT

#define LINK_UT_CORO

#define LINK_UT_DATA

#ifndef LOG_H
#define LOG_H

#ifdef  LOG_IMPLEMENT
#define LOG_EXT
#define LOG_EXT_INIT( dec, init ) \
	dec = init
#else
#define LOG_EXT extern
#define LOG_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup log_level Logging level
 *  \ingroup log
 *  \{
 */
#define LOG_LEVEL_OFF    0  /**< Logging off. \hideinitializer */
#define LOG_LEVEL_ERROR  1  /**< Errors. \hideinitializer */
#define LOG_LEVEL_WARN   2  /**< Errors and warnings. \hideinitializer */
#define LOG_LEVEL_INFO   3  /**< Errors, warnings and info. \hideinitializer */

/** \} */

#ifdef LOGGING

/**
 *  \defgroup log Logging
 *  \ingroup core
 *
 *	Structure of <b>log-dict.yu</b> file:
 *
 *  <b>LOG_WARN</b> - Dictionary of warnings.
 *  \param LOG_WARN Identifier of warning.
 *  \param WARN_FORMAT Message format.
 *  \param WARN_REPEAT Flag of repeated warning logging.
 *
 *  <b>LOG_INFO</b> - Dictionary of info messages.
 *  \param LOG_WARN Identifier of info.
 *  \param LOG_FORMAT Message format.
 *  \param LOG_REPEAT Flag of repeated info logging.
 *  \{
 */

/**
 *  \defgroup log_repeat Repeated logging flags
 *  \{
 */
#define LOG_NEVER  0    /**< Do not log message. \hideinitializer */
#define LOG_ONCE   1    /**< Log message once. \hideinitializer */
#define LOG_EVER   255  /**< Log message every time. \hideinitializer */

/** \} */

/**
 *  \brief Write message into log-file.
 *  \param pre Message type.
 *  \param format Message format.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define log_printf( pre, format, ... ) do { \
	if ( log_file == NULL ) break; \
	fprintf( log_file, "\n%s\t" pre "\t", clock_stamp( NULL, __log_str )); \
	fprintf( log_file, format, ## __VA_ARGS__ ); \
	fflush( log_file ); \
} while ( 0 )

/**
 *  \brief Write message for dictionary into log-file.
 *  \param pre Message type.
 *  \param name Identifier.
 *  \param ... Message arguments.
 *  \hideinitializer
 */

/**
 *  \brief Write error into log-file.
 *  \param name Identifier.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define LOG_ERROR( name, ... ) do { \
	if ( log_file == NULL ) break; \
	if (( ini_log_level >= LOG_LEVEL_ERROR ) && error_repeat[ error_##name ]) { \
		if ( log_lock_callback ) log_lock_callback(); \
		log_printf( "ERROR", error_format[ error_##name ], ## __VA_ARGS__ ); \
		if ( error_repeat[ error_##name ] < LOG_EVER ) { \
			if ( --error_repeat[ error_##name ] == LOG_NEVER ) { \
				fprintf( log_file, " (this message is reported last time)" ); \
			} \
		} \
		if ( log_unlock_callback ) log_unlock_callback(); \
	} \
} while ( 0 )

/**
 *  \brief Write warning into log-file.
 *  \param name Identifier.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define LOG_WARN( name, ... ) do { \
	if ( log_file == NULL ) break; \
	if (( ini_log_level >= LOG_LEVEL_WARN ) && warn_repeat[ warn_##name ]) { \
		if ( log_lock_callback ) log_lock_callback(); \
		log_printf( "WARN", warn_format[ warn_##name ], ## __VA_ARGS__ ); \
		if ( warn_repeat[ warn_##name ] < LOG_EVER ) { \
			if ( --warn_repeat[ warn_##name ] == LOG_NEVER ) { \
				fprintf( log_file, " (this message is reported last time)" ); \
			} \
		} \
		if ( log_unlock_callback ) log_unlock_callback(); \
	} \
} while ( 0 )

/**
 *  \brief Write info message into log-file.
 *  \param name Identifier.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define LOG_INFO( name, ... ) do { \
	if ( log_file == NULL ) break; \
	if (( ini_log_level >= LOG_LEVEL_INFO ) && info_repeat[ info_##name ]) { \
		if ( log_lock_callback ) log_lock_callback(); \
		log_printf( "INFO", info_format[ info_##name ], ## __VA_ARGS__ ); \
		if ( info_repeat[ info_##name ] < LOG_EVER ) { \
			if ( --info_repeat[ info_##name ] == LOG_NEVER ) { \
				fprintf( log_file, " (this message is reported last time)" ); \
			} \
		} \
		if ( log_unlock_callback ) log_unlock_callback(); \
	} \
} while ( 0 )

enum {
	warn_unused,

};

enum {
	info_unused,

};

LOG_EXT_INIT( FILE *log_file, NULL );

LOG_EXT char __log_str[ 32 ];

/**
 *  \brief Warnings formats.
 */
LOG_EXT const char * const warn_format[];

/**
 *  \brief Info messages formats.
 */
LOG_EXT const char * const info_format[];

/**
 *  \brief Error writing counters.
 */
LOG_EXT uint8_t error_repeat[];

/**
 *  \brief Warning writing counters.
 */
LOG_EXT uint8_t warn_repeat[];

/**
 *  \brief Info message writing counters.
 */
LOG_EXT uint8_t info_repeat[];

/**
 *  \brief Open log-file.
 *  \param mode "wa" or "a+".
 */
LOG_EXT void log_open( const char *mode );

/**
 *  \brief Close log-file.
 */
LOG_EXT void log_close( void );

/**
 *  \brief Clear log-file.
 */
LOG_EXT void log_clear( void );

/**
 *  \brief Lock log-file access (callback).
 */
LOG_EXT void ( *log_lock_callback )( void );

/**
 *  \brief Unlock log-file access (callback).
 */
LOG_EXT void ( *log_unlock_callback )( void );

/** \} */

#else /* LOGGING */

#define log_printf( pre, format, ... ) NULL
#define log_message( pre, name, ... ) NULL
#define LOG_ERROR( name, ... ) NULL
#define LOG_WARN( name, ... ) NULL
#define LOG_INFO( name, ... ) NULL

#endif /* LOGGING */

#ifdef __cplusplus
}
#endif

#endif

