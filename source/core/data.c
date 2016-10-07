
/*  data.c was generated by yup.py (yupp) 1.0b1
    out of data.yu-c 
 *//**
 *  \file  data.c (data.yu-c)
 *  \brief  Application state-space representation.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define DATA_IMPLEMENT

#include "include.h"

/**
 *  \addtogroup data
 *  \{
 */

typedef int __type_t;
typedef int __length_t;
typedef int __changed_t;

/**
 *  \brief Descriptor of state variable.
 */
struct DATA_DESCRY {
	/**  Variable name */
	const char *name;
	/**  Type */
	__type_t type;
	/**  Array length */
	__length_t len;
	/**  Data pointer */
	void *data;
	/**  value-to-string function */
	void *string;
};

typedef const struct DATA_DESCRY *data_descry_t;

static char __str[ 100 ] __attribute__(( unused ));

static __inline void __set_changed( const var_t item, const __changed_t value );

/**
 *  \brief Structure of state-space.
 */
struct DATA_SPACE {
	word error;
	byte _ut_byte;
	word _ut_word;
	dword _ut_array[ 4 ];
	float _ut_float;

	byte _ut_vote[ 4 ];
	byte _ut_vote__VALID[ 4 ];

};

/**
 *  \brief State-space.
 */
static struct DATA_SPACE data_space;

/**
 *  \brief Descriptor of state-space.
 */
static const struct DATA_DESCRY data_descry[] = {
	{ "error", type_WORD, 1, &data_space.error, ( void *) string_word_h },
	{ "_ut_byte", type_BYTE, 1, &data_space._ut_byte, ( void *) string_byte },
	{ "_ut_word", type_WORD, 1, &data_space._ut_word, ( void *) string_word_h },
	{ "_ut_array", type_DWORD, 4, &data_space._ut_array, ( void *) string_dword_h },
	{ "_ut_array_1", type_DWORD, 3, data_space._ut_array + 1, ( void *) string_dword_h },
	{ "_ut_array_2", type_DWORD, 2, data_space._ut_array + 2, ( void *) string_dword_h },
	{ "_ut_array_3", type_DWORD, 1, data_space._ut_array + 3, ( void *) string_dword_h },
	{ "_ut_float", type_FLOAT, 1, &data_space._ut_float, ( void *) string_float },

	{ "_ut_vote"  , type_BYTE, 4, data_space._ut_vote    , ( void *) string_byte },
	{ "_ut_vote_1", type_BYTE, 3, data_space._ut_vote + 1, ( void *) string_byte },
	{ "_ut_vote_2", type_BYTE, 2, data_space._ut_vote + 2, ( void *) string_byte },
	{ "_ut_vote_3", type_BYTE, 1, data_space._ut_vote + 3, ( void *) string_byte },
	{ "_ut_vote__VALID"  , type_BYTE, 4, data_space._ut_vote__VALID    , string_byte },
	{ "_ut_vote__VALID_1", type_BYTE, 3, data_space._ut_vote__VALID + 1, string_byte },
	{ "_ut_vote__VALID_2", type_BYTE, 2, data_space._ut_vote__VALID + 2, string_byte },
	{ "_ut_vote__VALID_3", type_BYTE, 1, data_space._ut_vote__VALID + 3, string_byte },

	{ "none", type_COUNT, 0, NULL, string_byte }
};

static __changed_t data_changed__not_empty[ var_COUNT ];
static __changed_t data_mask__not_empty[ var_COUNT ];
static __changed_t data_changed__ut_data_1[ var_COUNT ];
static __changed_t data_mask__ut_data_1[ var_COUNT ];
static __changed_t data_changed__ut_data_2[ var_COUNT ];
static __changed_t data_mask__ut_data_2[ var_COUNT ];

/**
 *  \brief Matrix of data changes flags of variables.
 */
static __changed_t *data_changed[] = {
data_changed__not_empty,
data_changed__ut_data_1,
data_changed__ut_data_2,

};

/**
 *  \brief Matrix of watching masks.
 */
static __changed_t *data_mask[] = {
data_mask__not_empty,
data_mask__ut_data_1,
data_mask__ut_data_2,

};

static const char *data_type_string[] = {
__stringify( byte ),
__stringify( word ),
__stringify( dword ),
__stringify( float ),
__stringify( int ),

};

/**
 *  \brief value-to-string functions prototypes.
 */
typedef char *( *string_byte_t )( char *, byte );
typedef char *( *string_word_t )( char *, word );
typedef char *( *string_dword_t )( char *, dword );
typedef char *( *string_float_t )( char *, float );
typedef char *( *string_int_t )( char *, int );

char *string_byte( char *s, byte value )
{
	sprintf( s, "%u", value );
	return ( s );
}
char *string_word( char *s, word value )
{
	sprintf( s, FMT_WORD, value );
	return ( s );
}
char *string_dword( char *s, dword value )
{
	sprintf( s, FMT_DWORD, value );
	return ( s );
}
char *string_float( char *s, float value )
{
	sprintf( s, "%.2f", value );
	return ( s );
}
char *string_int( char *s, int value )
{
	sprintf( s, "%d", value );
	return ( s );
}

static __inline void data_lock( void )
{
	if ( data_lock_callback ) data_lock_callback();
}

static __inline void data_unlock( void )
{
	if ( data_unlock_callback ) data_unlock_callback();
}

byte data_get_byte( const var_t item )
{
	byte result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return 0;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_BYTE ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_BYTE ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return 0;
		}
	} while ( 0 );
	data_lock();
	result = *(( byte *) data_descry[ item ].data );
	data_unlock();
	return ( result );
}

char *data_get_string_byte( char *s, const var_t item )
{
	char *result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return NULL;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_BYTE ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_BYTE ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return NULL;
		}
	} while ( 0 );
	data_lock();
	result = (( string_byte_t ) data_descry[ item ].string )( s, *(( byte *) data_descry[ item ].data ));
	data_unlock();
	return ( result );
}

void data_set_byte( const var_t item, byte value )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set", item );
			return ;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_BYTE ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "set"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_BYTE ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return ;
		}
	} while ( 0 );
	data_descry_t d = data_descry + item;
	byte *var = ( byte *) d->data;
	data_lock();
	if ( *var != value ) {
		*var = value;
		__set_changed( item, 1 );
		if ( ini_data_prot ) {
			if ((( *ini_data_prot_filter == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter ) != 0 ))
			&& (( *ini_data_prot_filter_skip == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter_skip ) == 0 ))) {
				printf( __CRLF__"\t" );
				printf( clock_stamp( NULL, __str ));
				printf( "   %-22s  %s"
				, d->name
				, (( string_byte_t ) d->string )( __str, *var )
				);
			}
		}
	}
	data_unlock();
}

word data_get_word( const var_t item )
{
	word result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return 0;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_WORD ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_WORD ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return 0;
		}
	} while ( 0 );
	data_lock();
	result = *(( word *) data_descry[ item ].data );
	data_unlock();
	return ( result );
}

char *data_get_string_word( char *s, const var_t item )
{
	char *result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return NULL;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_WORD ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_WORD ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return NULL;
		}
	} while ( 0 );
	data_lock();
	result = (( string_word_t ) data_descry[ item ].string )( s, *(( word *) data_descry[ item ].data ));
	data_unlock();
	return ( result );
}

void data_set_word( const var_t item, word value )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set", item );
			return ;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_WORD ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "set"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_WORD ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return ;
		}
	} while ( 0 );
	data_descry_t d = data_descry + item;
	word *var = ( word *) d->data;
	data_lock();
	if ( *var != value ) {
		*var = value;
		__set_changed( item, 1 );
		if ( ini_data_prot ) {
			if ((( *ini_data_prot_filter == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter ) != 0 ))
			&& (( *ini_data_prot_filter_skip == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter_skip ) == 0 ))) {
				printf( __CRLF__"\t" );
				printf( clock_stamp( NULL, __str ));
				printf( "   %-22s  %s"
				, d->name
				, (( string_word_t ) d->string )( __str, *var )
				);
			}
		}
	}
	data_unlock();
}

dword data_get_dword( const var_t item )
{
	dword result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return 0;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_DWORD ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_DWORD ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return 0;
		}
	} while ( 0 );
	data_lock();
	result = *(( dword *) data_descry[ item ].data );
	data_unlock();
	return ( result );
}

char *data_get_string_dword( char *s, const var_t item )
{
	char *result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return NULL;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_DWORD ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_DWORD ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return NULL;
		}
	} while ( 0 );
	data_lock();
	result = (( string_dword_t ) data_descry[ item ].string )( s, *(( dword *) data_descry[ item ].data ));
	data_unlock();
	return ( result );
}

void data_set_dword( const var_t item, dword value )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set", item );
			return ;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_DWORD ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "set"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_DWORD ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return ;
		}
	} while ( 0 );
	data_descry_t d = data_descry + item;
	dword *var = ( dword *) d->data;
	data_lock();
	if ( *var != value ) {
		*var = value;
		__set_changed( item, 1 );
		if ( ini_data_prot ) {
			if ((( *ini_data_prot_filter == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter ) != 0 ))
			&& (( *ini_data_prot_filter_skip == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter_skip ) == 0 ))) {
				printf( __CRLF__"\t" );
				printf( clock_stamp( NULL, __str ));
				printf( "   %-22s  %s"
				, d->name
				, (( string_dword_t ) d->string )( __str, *var )
				);
			}
		}
	}
	data_unlock();
}

float data_get_float( const var_t item )
{
	float result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return 0;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_FLOAT ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_FLOAT ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return 0;
		}
	} while ( 0 );
	data_lock();
	result = *(( float *) data_descry[ item ].data );
	data_unlock();
	return ( result );
}

char *data_get_string_float( char *s, const var_t item )
{
	char *result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return NULL;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_FLOAT ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_FLOAT ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return NULL;
		}
	} while ( 0 );
	data_lock();
	result = (( string_float_t ) data_descry[ item ].string )( s, *(( float *) data_descry[ item ].data ));
	data_unlock();
	return ( result );
}

void data_set_float( const var_t item, float value )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set", item );
			return ;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_FLOAT ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "set"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_FLOAT ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return ;
		}
	} while ( 0 );
	data_descry_t d = data_descry + item;
	float *var = ( float *) d->data;
	data_lock();
	if ( *var != value ) {
		*var = value;
		__set_changed( item, 1 );
		if ( ini_data_prot ) {
			if ((( *ini_data_prot_filter == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter ) != 0 ))
			&& (( *ini_data_prot_filter_skip == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter_skip ) == 0 ))) {
				printf( __CRLF__"\t" );
				printf( clock_stamp( NULL, __str ));
				printf( "   %-22s  %s"
				, d->name
				, (( string_float_t ) d->string )( __str, *var )
				);
			}
		}
	}
	data_unlock();
}

int data_get_int( const var_t item )
{
	int result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return 0;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_INT ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_INT ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return 0;
		}
	} while ( 0 );
	data_lock();
	result = *(( int *) data_descry[ item ].data );
	data_unlock();
	return ( result );
}

char *data_get_string_int( char *s, const var_t item )
{
	char *result;
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get", item );
			return NULL;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_INT ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "get"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_INT ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return NULL;
		}
	} while ( 0 );
	data_lock();
	result = (( string_int_t ) data_descry[ item ].string )( s, *(( int *) data_descry[ item ].data ));
	data_unlock();
	return ( result );
}

void data_set_int( const var_t item, int value )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set", item );
			return ;
		}
	} while ( 0 );
	do {
		if ( data_descry[ item ].type != type_INT ) {
			assert_fail( "attempt to %s \"%s\" (%d) as %s while it's %s"
			, "set"
			, data_descry[ item ].name
			, item
			, data_type_string[ type_INT ]
			, data_type_string[ data_descry[ item ].type ]
			);
			return ;
		}
	} while ( 0 );
	data_descry_t d = data_descry + item;
	int *var = ( int *) d->data;
	data_lock();
	if ( *var != value ) {
		*var = value;
		__set_changed( item, 1 );
		if ( ini_data_prot ) {
			if ((( *ini_data_prot_filter == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter ) != 0 ))
			&& (( *ini_data_prot_filter_skip == '\0' )
			|| ( strstr( d->name, ini_data_prot_filter_skip ) == 0 ))) {
				printf( __CRLF__"\t" );
				printf( clock_stamp( NULL, __str ));
				printf( "   %-22s  %s"
				, d->name
				, (( string_int_t ) d->string )( __str, *var )
				);
			}
		}
	}
	data_unlock();
}

char *data_get_string( char *s, const var_t item )
{
	switch ( data_descry[ item ].type ) {
	case type_BYTE:
		return data_get_string_byte( s, item );
	case type_WORD:
		return data_get_string_word( s, item );
	case type_DWORD:
		return data_get_string_dword( s, item );
	case type_FLOAT:
		return data_get_string_float( s, item );
	case type_INT:
		return data_get_string_int( s, item );

	default:
		return "?";
	}
}

void data_set_string( const var_t item, const char *s )
{
	char *end;

	switch ( data_descry[ item ].type ) {
	
	case type_BYTE:
		do {
			byte val = ( byte ) __strtoul( s, &end );
			if ( *end == '\0' ) {
				data_set_byte( item, val );
			} else {
				assert_fail( "attempt to set invalid \"%s\" %s value (%s)"
				, data_descry[ item ].name
				, data_type_string[ type_BYTE ]
				, s
				);
			}
		} while ( 0 );
		return;

	case type_WORD:
		do {
			word val = ( word ) __strtoul( s, &end );
			if ( *end == '\0' ) {
				data_set_word( item, val );
			} else {
				assert_fail( "attempt to set invalid \"%s\" %s value (%s)"
				, data_descry[ item ].name
				, data_type_string[ type_WORD ]
				, s
				);
			}
		} while ( 0 );
		return;

	case type_DWORD:
		do {
			dword val = ( dword ) __strtoll( s, &end );
			if ( *end == '\0' ) {
				data_set_dword( item, val );
			} else {
				assert_fail( "attempt to set invalid \"%s\" %s value (%s)"
				, data_descry[ item ].name
				, data_type_string[ type_DWORD ]
				, s
				);
			}
		} while ( 0 );
		return;

	case type_FLOAT:
		do {
			float val = ( float ) __strtof( s, &end );
			if ( *end == '\0' ) {
				data_set_float( item, val );
			} else {
				assert_fail( "attempt to set invalid \"%s\" %s value (%s)"
				, data_descry[ item ].name
				, data_type_string[ type_FLOAT ]
				, s
				);
			}
		} while ( 0 );
		return;

	case type_INT:
		do {
			int val = ( int ) __strtol( s, &end );
			if ( *end == '\0' ) {
				data_set_int( item, val );
			} else {
				assert_fail( "attempt to set invalid \"%s\" %s value (%s)"
				, data_descry[ item ].name
				, data_type_string[ type_INT ]
				, s
				);
			}
		} while ( 0 );
		return;

	}
}

void data_set( const var_t item, void *value )
{
	switch ( data_descry[ item ].type ) {
	case type_BYTE:
		data_set_byte( item, *( byte *) value );
		break;
	case type_WORD:
		data_set_word( item, *( word *) value );
		break;
	case type_DWORD:
		data_set_dword( item, *( dword *) value );
		break;
	case type_FLOAT:
		data_set_float( item, *( float *) value );
		break;
	case type_INT:
		data_set_int( item, *( int *) value );
		break;

	}
}

void voted_set_byte( const var_t item, byte h, byte value, bool ( *voter )( byte *, bool, byte, bool, byte, bool, byte ))
{
	byte result = data_get_byte( item );

	if (( h < 1 ) || ( h > 3 )) {
		assert_fail( "attempt to set invalid \"%s\" channel (%d)"
		, data_descry[ item ].name
		, h
		);
		return;
	}
	if ( data_get_byte( item + h + 4 ) == 0 ) {
		  data_set_byte( item + h + 4, 1 );
	} else {
		if ( value == data_get_byte( item + h ))
			/* Nothing changed */
			return;
	}
	data_set_byte( item + h, value );

	if ( voter( &result
	, data_get_byte( item + 5 ), data_get_byte( item + 1 )
	, data_get_byte( item + 6 ), data_get_byte( item + 2 )
	, data_get_byte( item + 7 ), data_get_byte( item + 3 ))
	) {
		data_set_byte( item, result );
		if ( !data_get_byte( item + 4 )) {
			  data_set_byte( item + 4, 1 );
			  data_set_changed( item );
		}
	} else {
		/* Invalid voted */
		if ( data_get_byte( item + 4 )) {
			 data_set_byte( item + 4, 0 );
			 data_set_changed( item );
		}
	}
}

void joint_set_byte( const var_t item, byte value )
{
	data_set_byte( item + 4,     1 );
	data_set_byte( item + 4 + 1, 1 );
	data_set_byte( item + 4 + 2, 1 );
	data_set_byte( item + 4 + 3, 1 );
	data_set_byte( item, value );
	data_set_byte( item + 1, value );
	data_set_byte( item + 2, value );
	data_set_byte( item + 3, value );
}

void voted_set_word( const var_t item, byte h, word value, bool ( *voter )( word *, bool, word, bool, word, bool, word ))
{
	word result = data_get_word( item );

	if (( h < 1 ) || ( h > 3 )) {
		assert_fail( "attempt to set invalid \"%s\" channel (%d)"
		, data_descry[ item ].name
		, h
		);
		return;
	}
	if ( data_get_byte( item + h + 4 ) == 0 ) {
		  data_set_byte( item + h + 4, 1 );
	} else {
		if ( value == data_get_word( item + h ))
			/* Nothing changed */
			return;
	}
	data_set_word( item + h, value );

	if ( voter( &result
	, data_get_byte( item + 5 ), data_get_word( item + 1 )
	, data_get_byte( item + 6 ), data_get_word( item + 2 )
	, data_get_byte( item + 7 ), data_get_word( item + 3 ))
	) {
		data_set_word( item, result );
		if ( !data_get_byte( item + 4 )) {
			  data_set_byte( item + 4, 1 );
			  data_set_changed( item );
		}
	} else {
		/* Invalid voted */
		if ( data_get_byte( item + 4 )) {
			 data_set_byte( item + 4, 0 );
			 data_set_changed( item );
		}
	}
}

void joint_set_word( const var_t item, word value )
{
	data_set_byte( item + 4,     1 );
	data_set_byte( item + 4 + 1, 1 );
	data_set_byte( item + 4 + 2, 1 );
	data_set_byte( item + 4 + 3, 1 );
	data_set_word( item, value );
	data_set_word( item + 1, value );
	data_set_word( item + 2, value );
	data_set_word( item + 3, value );
}

void voted_set_dword( const var_t item, byte h, dword value, bool ( *voter )( dword *, bool, dword, bool, dword, bool, dword ))
{
	dword result = data_get_dword( item );

	if (( h < 1 ) || ( h > 3 )) {
		assert_fail( "attempt to set invalid \"%s\" channel (%d)"
		, data_descry[ item ].name
		, h
		);
		return;
	}
	if ( data_get_byte( item + h + 4 ) == 0 ) {
		  data_set_byte( item + h + 4, 1 );
	} else {
		if ( value == data_get_dword( item + h ))
			/* Nothing changed */
			return;
	}
	data_set_dword( item + h, value );

	if ( voter( &result
	, data_get_byte( item + 5 ), data_get_dword( item + 1 )
	, data_get_byte( item + 6 ), data_get_dword( item + 2 )
	, data_get_byte( item + 7 ), data_get_dword( item + 3 ))
	) {
		data_set_dword( item, result );
		if ( !data_get_byte( item + 4 )) {
			  data_set_byte( item + 4, 1 );
			  data_set_changed( item );
		}
	} else {
		/* Invalid voted */
		if ( data_get_byte( item + 4 )) {
			 data_set_byte( item + 4, 0 );
			 data_set_changed( item );
		}
	}
}

void joint_set_dword( const var_t item, dword value )
{
	data_set_byte( item + 4,     1 );
	data_set_byte( item + 4 + 1, 1 );
	data_set_byte( item + 4 + 2, 1 );
	data_set_byte( item + 4 + 3, 1 );
	data_set_dword( item, value );
	data_set_dword( item + 1, value );
	data_set_dword( item + 2, value );
	data_set_dword( item + 3, value );
}

void voted_set_float( const var_t item, byte h, float value, bool ( *voter )( float *, bool, float, bool, float, bool, float ))
{
	float result = data_get_float( item );

	if (( h < 1 ) || ( h > 3 )) {
		assert_fail( "attempt to set invalid \"%s\" channel (%d)"
		, data_descry[ item ].name
		, h
		);
		return;
	}
	if ( data_get_byte( item + h + 4 ) == 0 ) {
		  data_set_byte( item + h + 4, 1 );
	} else {
		if ( value == data_get_float( item + h ))
			/* Nothing changed */
			return;
	}
	data_set_float( item + h, value );

	if ( voter( &result
	, data_get_byte( item + 5 ), data_get_float( item + 1 )
	, data_get_byte( item + 6 ), data_get_float( item + 2 )
	, data_get_byte( item + 7 ), data_get_float( item + 3 ))
	) {
		data_set_float( item, result );
		if ( !data_get_byte( item + 4 )) {
			  data_set_byte( item + 4, 1 );
			  data_set_changed( item );
		}
	} else {
		/* Invalid voted */
		if ( data_get_byte( item + 4 )) {
			 data_set_byte( item + 4, 0 );
			 data_set_changed( item );
		}
	}
}

void joint_set_float( const var_t item, float value )
{
	data_set_byte( item + 4,     1 );
	data_set_byte( item + 4 + 1, 1 );
	data_set_byte( item + 4 + 2, 1 );
	data_set_byte( item + 4 + 3, 1 );
	data_set_float( item, value );
	data_set_float( item + 1, value );
	data_set_float( item + 2, value );
	data_set_float( item + 3, value );
}

void voted_set_int( const var_t item, byte h, int value, bool ( *voter )( int *, bool, int, bool, int, bool, int ))
{
	int result = data_get_int( item );

	if (( h < 1 ) || ( h > 3 )) {
		assert_fail( "attempt to set invalid \"%s\" channel (%d)"
		, data_descry[ item ].name
		, h
		);
		return;
	}
	if ( data_get_byte( item + h + 4 ) == 0 ) {
		  data_set_byte( item + h + 4, 1 );
	} else {
		if ( value == data_get_int( item + h ))
			/* Nothing changed */
			return;
	}
	data_set_int( item + h, value );

	if ( voter( &result
	, data_get_byte( item + 5 ), data_get_int( item + 1 )
	, data_get_byte( item + 6 ), data_get_int( item + 2 )
	, data_get_byte( item + 7 ), data_get_int( item + 3 ))
	) {
		data_set_int( item, result );
		if ( !data_get_byte( item + 4 )) {
			  data_set_byte( item + 4, 1 );
			  data_set_changed( item );
		}
	} else {
		/* Invalid voted */
		if ( data_get_byte( item + 4 )) {
			 data_set_byte( item + 4, 0 );
			 data_set_changed( item );
		}
	}
}

void joint_set_int( const var_t item, int value )
{
	data_set_byte( item + 4,     1 );
	data_set_byte( item + 4 + 1, 1 );
	data_set_byte( item + 4 + 2, 1 );
	data_set_byte( item + 4 + 3, 1 );
	data_set_int( item, value );
	data_set_int( item + 1, value );
	data_set_int( item + 2, value );
	data_set_int( item + 3, value );
}

static __inline void __set_changed( const var_t item, const __changed_t value )
{
	thread_t i;

	for ( i = 0; i < peek_COUNT; i++ ) {
		if ( data_mask[ i ][ item ]) data_changed[ i ][ item ] = value;
	}
}

void data_set_changed( const var_t item )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set change of", item );
			return ;
		}
	} while ( 0 );
	data_lock();
	__set_changed( item, 1 );
	data_unlock();
}

void data_reset_changed( const var_t item )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "reset change of", item );
			return ;
		}
	} while ( 0 );
	data_lock();
	__set_changed( item, 0 );
	data_unlock();
}

void data_set_all_changed( const thread_t thread )
{
	var_t i;

	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return ;
		}
	} while ( 0 );
	data_lock();
	for ( i = 0; i < var_COUNT; i++ ) {
		if ( data_mask[ thread ][ i ]) data_changed[ thread ][ i ] = 1;
	}
	data_unlock();
}

int data_get_changed( const thread_t thread, const var_t item )
{
	int result;

	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return 0;
		}
	} while ( 0 );
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get change of", item );
			return 0;
		}
	} while ( 0 );
	data_lock();
	result = (( int ) data_changed[ thread ][ item ]);
	data_unlock();

	return ( result );
}

int data_get_changed_any( const thread_t thread )
{
	var_t i;

	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return 0;
		}
	} while ( 0 );
	data_lock();
	for ( i = 0; i < var_COUNT; i++ ) {
		if ( data_changed[ thread ][ i ]) {
			data_unlock();

			return ( 1 );
		}
	}
	data_unlock();

	return ( 0 );
}

void data_watch( const thread_t thread, const var_t *vars )
{
	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return ;
		}
	} while ( 0 );
	data_lock();
	while ( *vars < var_COUNT ) data_mask[ thread ][ *vars++ ] = 1;
	data_unlock();
}

void data_watch_array( const thread_t thread, const var_t *vars )
{
	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return ;
		}
	} while ( 0 );
	data_lock();
	while ( *vars < var_COUNT ) {
		var_t i;

		for ( i = *vars + data_descry[ *vars ].len - 1; i >= *vars; i-- ) {
			data_mask[ thread ][ i ] = 1;
		}
		++vars;
	}
	data_unlock();
}

void data_clear_watch( const thread_t thread )
{
	var_t i;

	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return ;
		}
	} while ( 0 );
	data_lock();
	for ( i = 0; i < var_COUNT; i++ ) {
		data_mask[ thread ][ i ] = 0;
		data_changed[ thread ][ i ] = 0;
	}
	data_unlock();
}

void data_reset( const thread_t thread, const var_t item )
{
	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return ;
		}
	} while ( 0 );
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "set change of", item );
			return ;
		}
	} while ( 0 );
	data_lock();
	data_changed[ thread ][ item ] = 0;
	data_unlock();
}

void data_reset_all( const thread_t thread )
{
	var_t i;

	do {
		if ( thread >= peek_COUNT ) {
			assert_fail( "invalid thread inx (%d)", thread );
			return ;
		}
	} while ( 0 );
	data_lock();
	for ( i = 0; i < var_COUNT; i++ ) data_changed[ thread ][ i ] = 0;
	data_unlock();
}

bool voted_valid( const var_t item )
{
	return ( data_get_byte( item + 4 ));
}

var_t data_atovar( const char *s )
{
	var_t i;

	for ( i = 0; i < var_COUNT; i++ ) {
		if ( strcmp( data_descry[ i ].name, s ) == 0 ) return ( i );
	}
	return ( var_COUNT );
}

char *data_vartoa( const var_t item )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get name of", item );
			return "";
		}
	} while ( 0 );

	return (( char *) data_descry[ item ].name );
}

char *data_get_type( const var_t item )
{
	do {
		if ( item >= var_COUNT ) {
			assert_fail( "attempt to %s var with invalid inx (%d)", "get type of", item );
			return "";
		}
	} while ( 0 );

	return (( char *) data_type_string[ data_descry[ item ].type ]);
}

/** \} */
