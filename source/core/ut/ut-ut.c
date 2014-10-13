/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  ut-ut.c
 *  \brief  Unit test of unit testing.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include "include.h"

#ifdef LINK_UT_UT

/**
 *  \defgroup ut_ut Unit test of unit testing
 *  \ingroup ut
 *  \{
 */

static void test_assert( void )
{
	assert( 1 == 1, );
	assert_not( 1 == 2, );
	assert_int_eq( -1, -1, );
	assert_uint_eq( 451, 451, );
	assert_float_eq( 10.2, 10.0, 0.2, );
	assert_double_eq( 20.1, 20.1, 0.0, );
}

static void test_assert_fail( void )
{
	ut_quiet_begin();

	assert( 1 == 2, );
	assert_fail( "%d %d %d...", 1, 2, 3 );

	ut_quiet_end( 2 );
}

static void test_array( void )
{
	unsigned char expected[] = { 1, 2, 3 };
	unsigned char actual[ 5 ];
	int i;

	for ( i = 0; i < 5; i++ ) actual[ i ] = i + 1;

	/* Check the first 3 bytes */
	assert_array_eq( expected, actual, 3, );
}

static void test_bit( void )
{
	assert_bit_1( 0, 0x01, );
	assert_bit_1( 2, 0x04, );
	assert_bit_0( 3, 0x02, );
}

static void test_str( void )
{
	char *s = "hello";

	assert_str_eq( "hello", s, );
	assert_str_eq( NULL, NULL, );
	assert_str_has( "amazing", "hello amazing world!", );
	assert_str_hasno( "wonderful", "hello amazing world!", );
	assert_str_end( "world!", "hello amazing world!", );
	assert_str_start( s, "hello amazing world!", );
}

void ut_ut( void )
{
	ut_1_begin();
	ut_1_exec( test_assert );
	ut_1_exec( test_assert_fail );
	ut_1_exec( test_str );
	ut_1_exec( test_array );
	ut_1_exec( test_bit );
	ut_1_end();
}

/** \} */

#endif /* LINK_UT_UT */
