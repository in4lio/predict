
/*  ut.h was generated by yup.py (yupp) 0.9b1
    out of ut.yu-h at 2016-03-06 17:31
 *//**
 *  \file  ut.h (ut.yu-h)
 *  \brief  Unit testing.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#ifndef UT_H
#define UT_H

#ifdef  UT_IMPLEMENT
#define UT_EXT
#define UT_EXT_INIT( dec, init ) \
	dec = init
#else
#define UT_EXT extern
#define UT_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LINK_UT

/**
 *  \defgroup ut Unit testing
 *  \ingroup core
 *  \{
 */

/**
 *  \brief Max length of message.
 *  \hideinitializer
 */
#define UT_STR_LIMIT  100

UT_EXT bool ut_assert_true( bool test, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_false( bool test, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_assigned( int data, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_int_equal( int expected, int actual, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_uint_equal( uint32_t expected, uint32_t actual, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_float_equal( float expected, float actual, float delta, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_double_equal( double expected, double actual, double delta, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_string_equal( const char *expected, const char *actual, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_string_ends_with( const char *expected, const char *actual, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_string_starts_with( const char *expected, const char *actual, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_string_contains( const char *expected, const char *actual, const char *path, const char *func, uint32_t line );
UT_EXT bool ut_assert_string_doesnt_contain( const char *expected, const char *actual, const char *path, const char *func, uint32_t line );

/**
 *  \brief Test failed.
 *  \param msg Message format.
 *  \param ... Message arguments.
 *  \hideinitializer
 */
#define assert_fail( msg, ... ) do { \
	char s[ UT_STR_LIMIT ]; \
	sprintf( s, msg, ## __VA_ARGS__ ); \
	ut_fault( s, __FILE__, __FUNCTION__, __LINE__ ); \
} while ( 0 )

#undef assert

/**
 *  \brief Verify expression is true.
 *  \param value Expression.
 *  \param op Operation if verification failed.
 *  \hideinitializer
 */
#define assert( value, op ) do { \
	if ( ut_assert_true( value, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_not( value, op ) do { \
	if ( ut_assert_false( value, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_assigned( value, op ) do { \
	if ( ut_assert_assigned(( int ) value, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_int_eq( expected, actual, op ) do { \
	if ( ut_assert_int_equal( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_uint_eq( expected, actual, op ) do { \
	if ( ut_assert_uint_equal( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_str_eq( expected, actual, op ) do { \
	if ( ut_assert_string_equal( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_array_eq( expected, actual, count, op ) do { \
	int i; \
	for ( i = 0; i < count; i++ ) { \
		char s[ UT_STR_LIMIT ]; \
		bool test = ( expected[ i ] == actual[ i ]); \
		if ( !test ) { \
			sprintf( s, "expected %d to be %d at pos %d", actual[ i ], expected[ i ], i ); \
			ut_fault( s, __FILE__, __FUNCTION__, __LINE__ ); \
			op; \
		} \
	} \
} while ( 0 )

#define assert_bit_1( bit, value, op ) do { \
	bool test = ((( uint32_t ) 1 << ( bit )) & ( value )); \
	if ( !test ) { \
		ut_fault( "expected bit to be set", __FILE__,  __FUNCTION__, __LINE__ ); \
		op; \
	} \
} while ( 0 )

#define assert_bit_0( bit, value, op ) do { \
	bool test = !((( uint32_t ) 1 << ( bit )) & ( value )); \
	if ( !test ) { \
		ut_fault( "expected bit not to be set", __FILE__,  __FUNCTION__, __LINE__ ); \
		op; \
	} \
} while ( 0 )

#define assert_bit_mask( value, mask, op ) do { \
	bool test = ((( value ) & ( mask )) == ( mask )); \
	if ( !test ) { \
		ut_fault( "expected mask to be set", __FILE__,  __FUNCTION__, __LINE__ ); \
		op; \
	} \
} while ( 0 )

#define assert_float_eq( expected, actual, delta, op ) do { \
	if ( ut_assert_float_equal( expected, actual, delta, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_double_eq( expected, actual, delta, op ) do { \
	if ( ut_assert_double_equal( expected, actual, delta, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_str_has( expected, actual, op ) do { \
	if ( ut_assert_string_contains( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_str_hasno( expected, actual, op ) do { \
	if ( ut_assert_string_doesnt_contain( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_str_start( expected, actual, op ) do { \
	if ( ut_assert_string_starts_with( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

#define assert_str_end( expected, actual, op ) do { \
	if ( ut_assert_string_ends_with( expected, actual, __FILE__, __FUNCTION__, __LINE__ )) { op; } \
} while ( 0 )

UT_EXT void ut_fault( const char *error, const char *path, const char *func, uint32_t line );
UT_EXT void ut_quiet( void );
UT_EXT void ut_loud( void );
UT_EXT uint32_t ut_get_quiet( void );

UT_EXT void ut_1_unit_begin( const char *path );
UT_EXT void ut_1_unit_end( void );
UT_EXT void ut_2_unit_begin( const char *path );

/**
 *  \brief Verify quiet mode is off.
 *  \hideinitializer
 */
#define ut_assert_loud() do { \
	int quiet = ut_get_quiet(); \
	if ( quiet ) { \
		char s[ UT_STR_LIMIT ]; \
		sprintf( s, "QUIET should be disabled ( %d fault(s))", quiet - 1 ); \
		ut_loud(); \
		ut_fault( s, __FILE__, __FUNCTION__, __LINE__ ); \
	} \
} while ( 0 )

/**
 *  \brief Start verification in quiet mode (without failure messages).
 *  \hideinitializer
 */
#define ut_quiet_begin() do { \
	ut_assert_loud(); \
	ut_quiet(); \
} while ( 0 )

/**
 *  \brief Complete verification in quiet mode.
 *  \param expected Expected count of failures (in quiet mode).
 *  \hideinitializer
 */
#define ut_quiet_end( expected ) do { \
	int quiet = ut_get_quiet(); \
	if ( quiet ) { \
		ut_loud(); \
		ut_assert_int_equal( expected, quiet - 1, __FILE__, __FUNCTION__, __LINE__ ); \
	} \
} while ( 0 )

/**
 *  \brief Beginning of group of unit test of 1st stage.
 *  \hideinitializer
 */
#define ut_1_begin() do { \
	ut_1_unit_begin( __FILE__ ); \
} while ( 0 )

/**
 *  \brief Run unit test of 1st stage.
 *  \param test Unit test.
 */
UT_EXT void ut_1_exec( void ( *test )( void ));

/**
 *  \brief End of group of unit test.
 *  \hideinitializer
 */
#define ut_1_end() do { \
	ut_1_unit_end(); \
} while ( 0 )

/**
 *  \brief 1st stage of unit testing.
 *  \param test Set of tests.
 */
UT_EXT bool ut_stage_1( void ( *test )( void ));

/**
 *  \brief Beginning of group of unit test of 2nd stage (coroutine).
 *  \hideinitializer
 */
#define ut_2_begin() do { \
	ut_2_unit_begin( __FILE__ ); \
} while ( 0 )

/**
 *  \brief Start unit testing of 2nd stage.
 *  \param count Tests count.
 */
UT_EXT void ut_stage_2_start( int count );

/**
 *  \brief Call test coroutines.
 *  \param test Schedule.
 *  \return true if testing is not complete.
 */
UT_EXT bool ut_stage_2( int ( *test )( void ));

/**
 *  \brief Print statistics of unit testing.
 */
UT_EXT void ut_print_statistics( void );

/**
 *  \brief Get current time (callback).
 */
UT_EXT uint32_t ( *ut_get_time_callback )( void );

/**
 *  \brief Event handler of testing stage starting (callback).
 *  \param t Stage of testing.
 */
UT_EXT void ( *ut_started_callback )( int t );

/**
 *  \brief Event handler of testing stage completion (callback).
 *  \param t Stage of testing.
 *  \param result Testing result.
 */
UT_EXT void ( *ut_finished_callback )( int t, bool result );

/**
 *  \brief Lock common data access (callback).
 */
UT_EXT void ( *ut_lock_callback )( void );

/**
 *  \brief Unlock common data access (callback).
 */
UT_EXT void ( *ut_unlock_callback )( void );

/** \} */

#else  /* LINK_UT */

#define assert_fail( msg, ... ) NULL
#undef  assert
#define assert( value, op ) NULL
#define assert_not( value, op ) NULL
#define assert_assigned( value, op ) NULL
#define assert_int_eq( expected, actual, op ) NULL
#define assert_uint_eq( expected, actual, op ) NULL
#define assert_str_eq( expected, actual, op ) NULL
#define assert_array_eq( expected, actual, count, op ) NULL
#define assert_bit_1( bit, value, op ) NULL
#define assert_bit_0( bit, value, op ) NULL
#define assert_bit_mask( value, mask, op ) NULL
#define assert_float_eq( expected, actual, delta, op ) NULL
#define assert_double_eq( expected, actual, delta, op ) NULL
#define assert_str_has( expected, actual, op ) NULL
#define assert_str_hasno( expected, actual, op ) NULL
#define assert_str_start( expected, actual, op ) NULL
#define assert_str_end( expected, actual, op ) NULL

#endif /* LINK_UT */

#ifdef __cplusplus
}
#endif

#endif

