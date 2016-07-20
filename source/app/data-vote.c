
/*  data-vote.c was generated by yup.py (yupp) 0.9b3
    out of data-vote.yu-c 
 *//**
 *  \file  data-vote.c (data-vote.yu-c)
 *  \brief  Data voting.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define DATA_VOTE_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup data
 *  \{
 */

bool vote_dword( dword *result
, bool valid_1, dword value_1
, bool valid_2, dword value_2
, bool valid_3, dword value_3 )
{
	if ( valid_1 && valid_2 && ( value_1 == value_2 )) {
		*result = value_1;

		return ( true );
	}
	if ( valid_2 && valid_3 && ( value_2 == value_3 )) {
		*result = value_2;

		return ( true );
	}
	if ( valid_3 && valid_1 && ( value_3 == value_1 )) {
		*result = value_3;

		return ( true );
	}

	return ( false );
}

bool vote_word( word *result
, bool valid_1, word value_1
, bool valid_2, word value_2
, bool valid_3, word value_3 )
{
	if ( valid_1 && valid_2 && ( value_1 == value_2 )) {
		*result = value_1;

		return ( true );
	}
	if ( valid_2 && valid_3 && ( value_2 == value_3 )) {
		*result = value_2;

		return ( true );
	}
	if ( valid_3 && valid_1 && ( value_3 == value_1 )) {
		*result = value_3;

		return ( true );
	}

	return ( false );
}

bool vote_byte( byte *result
, bool valid_1, byte value_1
, bool valid_2, byte value_2
, bool valid_3, byte value_3 )
{
	if ( valid_1 && valid_2 && ( value_1 == value_2 )) {
		*result = value_1;

		return ( true );
	}
	if ( valid_2 && valid_3 && ( value_2 == value_3 )) {
		*result = value_2;

		return ( true );
	}
	if ( valid_3 && valid_1 && ( value_3 == value_1 )) {
		*result = value_3;

		return ( true );
	}

	return ( false );
}

bool vote_bit_dword( dword *result
, bool _1 __attribute__(( unused )), dword value_1
, bool _2 __attribute__(( unused )), dword value_2
, bool _3 __attribute__(( unused )), dword value_3 )
{
	/* Should be two of three... */
	*result = ( value_1 & value_2 ) | (( value_1 | value_2 ) & value_3 );

	return ( true );
}

/** \} */
