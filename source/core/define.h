/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  define.h
 *  \brief  Common definitions.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

#ifndef DEFINE_H
#define DEFINE_H

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long long qword;

/**
 *  \brief Calculate n-byte aligned value.
 *  \param value Original value.
 *  \param align Alignment boundary.
 *  \hideinitializer
 */
#define ALIGNED( value, align ) ((( value ) + (( align ) - 1 )) / ( align ) * ( align ))

/**
 *  \brief Calculate padding size.
 *  \param value Original value.
 *  \param align Alignment boundary.
 *  \hideinitializer
 */
#define PADDING( value, align ) ( ALIGNED( value, align ) - ( value ))

/**
 *  \brief Typecasting.
 *  \param type Destination type.
 *  \param x Object.
 *  \hideinitializer
 */
#define _AS_( type, x )    (( type *) &( x ))

#define _AS_PLONG( x )     _AS_( int, x )
#define _AS_LONG( x )      ( *_AS_PLONG( x ))
#define _AS_DWORD( x )     _AS_LONG( x )
#define _AS_PSHORT( x )    _AS_( short, x )
#define _AS_SHORT( x )     ( *_AS_PSHORT( x ))
#define _AS_PWORD( x )     _AS_PSHORT( x )
#define _AS_WORD( x )      _AS_SHORT( x )
#define _AS_PCHAR( x )     _AS_( char, x )
#define _AS_CHAR( x )      ( *_AS_PCHAR( x ))
#define _AS_BYTE( x )      _AS_CHAR( x )

#define _AS_VOID( x )      (( void * )( dword )( x ))

#define HIGH_BYTE( w )     ( *( _AS_( byte, w ) + 1 ))
#define LOW_BYTE( w )      (( byte )( w ))
#define HIGH_WORD( dw )    ( *( _AS_( word, dw ) + 1 ))
#define LOW_WORD( dw )     (( word )( dw ))

/**
 *  \brief Get n-th byte of value.
 *  \param n Position.
 *  \param pool Original pool.
 *  \hideinitializer
 */
#define _BYTE( n, pool )  (( byte )(( pool ) >> ( 8 * ( n ))))

/**
 *  \brief Create pool with n-th bit set.
 *  \param n Position.
 *  \hideinitializer
 */
#define BIT( n )           (( dword ) 1 << ( n ))

/**
 *  \brief Create pool with cleared masked bits in original.
 *  \param pool Original pool.
 *  \param mask Mask.
 *  \hideinitializer
 */
#define CLEAR_VALUE( pool, mask ) \
	(( pool ) & ~( mask ))

/**
 *  \brief Create pool with set masked bits in original.
 *  \param pool Original pool.
 *  \param mask Mask.
 *  \hideinitializer
 */
#define SET_VALUE( pool, mask ) \
	(( pool ) | ( mask ))

/**
 *  \brief Create pool having equal to specified values state of masked bits in original.
 *  \param pool Original pool.
 *  \param mask Mask.
 *  \param value Specified values of bits.
 *  \hideinitializer
 */
#define EQUAL_VALUE( pool, mask, value ) \
	SET_VALUE( CLEAR_VALUE( pool, mask ), value )

/**
 *  \brief Clear variable's masked bits.
 *  \param var Variable.
 *  \param mask Mask.
 *  \hideinitializer
 */
#define CLEAR_VAR( var, mask ) \
	var &= ~( mask )

/**
 *  \brief Set variable's masked bits.
 *  \param var Variable.
 *  \param mask Mask.
 *  \hideinitializer
 */
#define SET_VAR( var, mask ) \
	var |= ( mask )

/**
 *  \brief Bring variable's masked bits into accord with specified values.
 *  \param var Variable.
 *  \param mask Mask.
 *  \param value Specified values of bits.
 *  \hideinitializer
 */
#define EQUAL_VAR( var, mask, value ) \
	var = EQUAL_VALUE( var, mask, value );

/**
 *  \brief Check equality of variable's masked bits to specified values.
 *  \param var Variable.
 *  \param mask Mask.
 *  \param value Specified values of bits.
 *  \hideinitializer
 */
#define TEST_EQUAL( var, mask, value ) \
	((( var ) & ( mask )) == ( value ))

/**
 *  \brief Check variable's masked bits are set.
 *  \param var Variable.
 *  \param mask Mask.
 *  \hideinitializer
 */
#define TEST_EQUAL_1( var, mask ) \
	TEST_EQUAL( var, mask, mask )

/**
 *  \brief Check at least one masked bit of variable equals to specified value.
 *  \param var Variable.
 *  \param mask Mask.
 *  \param value Specified values of bits.
 *  \hideinitializer
 */
#define TEST_EQUAL_PART( var, mask, value ) \
	( ~(( var ) ^ ( value )) & ( mask ))

/** \hideinitializer */
#define __stringify_1( x ) #x

/**
 *  \brief Stringification.
 *  \param x Object.
 *  \hideinitializer
 */
#define __stringify( x )   __stringify_1( x )

/**
 *  \brief Length of array (vector).
 *  \param array Array.
 *  \hideinitializer
 */
#define array_length( array )  ( sizeof( array ) / sizeof(( array )[ 0 ]))

/**
 *  \brief Index of element in array (vector).
 *  \param array Array.
 *  \param element Pointer to element.
 *  \hideinitializer
 */
#define array_index( array, element ) \
	((( dword )( element ) - ( dword )( array )) / sizeof(( array )[ 0 ]))

/**
 *  \brief Create field mask.
 *  \param type Pool type.
 *  \param PRE Macro prefix.
 *  \param F Field name.
 *  \hideinitializer
 */
#define _F_MASK( type, PRE, F ) \
	(( type ) PRE##T_##F << PRE##O_##F )

/**
 *  \brief Get value of field.
 *  \param type Pool type.
 *  \param PRE Macro prefix.
 *  \param pool Pool.
 *  \param F Field name.
 *  \hideinitializer
 */
#define _F_GET( type, PRE, pool, F ) \
	((( type )( pool ) >> PRE##O_##F ) & PRE##T_##F )

/**
 *  \brief Create pool having state of field equal to specified value.
 *  \param type Pool type.
 *  \param PRE Macro prefix.
 *  \param F Field name.
 *  \param value Specified value of field.
 *  \hideinitializer
 */
#define _F_SET( type, PRE, F, value ) \
	((( type ) PRE##T_##F & ( value )) << PRE##O_##F )

#endif /* DEFINE_H */
