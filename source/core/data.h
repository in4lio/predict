
/*  data.h was generated by yup.py (yupp) 0.8b8
    out of data.yu-h at 2015-08-06 14:31
 *//**
 *  \file  data.h (data.yu-h)
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

#ifndef DATA_H
#define DATA_H

#ifdef  DATA_IMPLEMENT
#define DATA_EXT
#define DATA_EXT_INIT( dec, init ) \
	dec = init
#else
#define DATA_EXT extern
#define DATA_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup data Application state-space representation
 *  \ingroup core
 *
 *	Structure of <b>data-dict.yu</b> file:
 *
 *  <b>DATA_TYPE</b> - Dictionary of variables types.
 *  \param DATA_TYPE Data type.
 *  \param TYPE_FORMAT Format string for values output.
 *  \param TYPE_STRTO string-to-value function.
 *
 *  <b>DATA_THREAD</b> - Dictionary of threads that watch the changes of state-space (watching threads).
 *  \param DATA_THREAD Thread name.
 *
 *  <b>DATA_VAR</b> - Dictionary of variables.
 *  \param DATA_VAR Variable name.
 *  \param VAR_TYPE Variable type.
 *  \param VAR_LEN Array length (single variable if equals to 1).
 *  \param VAR_STRING value-to-string function.
 *
 *  Usage example:
 *
 *  \code
 *  // Set value of variable
 *  data_set_word( var_name, value );
 *
 *  // Check that value has been changed
 *  if ( data_get_changed( peek_thread, var_name )) {
 *
 *      // Get value
 *      value = data_get_word( var_name )
 *
 *      // Reset data changes flag of variable
 *      data_reset( peek_thread, var_name );
 *  }
 *  \endcode
 *
 *  Support of triple modular redundancy.
 *  <b>DATA_VOTED</b> - Majority opinion variable.
 *  \param DATA_VOTED Variable name.
 *  \param VOTED_TYPE Variable type.
 *  \param VOTED_STRING value-to-string function.
 *
 *  Usage example:
 *
 *  \code
 *  // Set channel value of variable
 *  voted_set_byte( var_name, channel, value, &vote_byte );
 *
 *  // Check that majority opinion has been changed
 *  if ( data_get_changed( peek_thread, var_name )) {
 *
 *      // Check that majority opinion is valid
 *      if ( voted_valid( var_name )) {
 *
 *          // Get majority opinion value
 *          value = data_get_byte( var_name )
 *      }
 *      // Reset data changes flag of variable
 *      data_reset( peek_thread, var_name );
 *  }
 *  \endcode
 *  \{
 */

typedef int thread_t;
typedef int var_t;

/**
 *  \page data List of state variables
 *
 *  \section d_error Variable error
 *  Pool of error bits. See errors dictionary \ref error-dict.yu .
 *
 *  \section d__ut_ Variables _ut_*
 *  Used for \ref ut "unit testing".
 */

/**
 *  \brief Identifiers of watching threads.
 */
enum {
	peek__not_empty,
	peek__ut_data_1,
	peek__ut_data_2,

	peek_COUNT
};

/**
 *  \brief Data types identifiers.
 */
enum {
	type_BYTE,
	type_WORD,
	type_DWORD,
	type_FLOAT,
	type_INT,

	type_COUNT
};

/**
 *  \brief Variables identifiers.
 */
enum {
	var_error, var_error_0 = var_error, 
	var__ut_byte, var__ut_byte_0 = var__ut_byte, 
	var__ut_word, var__ut_word_0 = var__ut_word, 
	var__ut_array, var__ut_array_0 = var__ut_array, var__ut_array_1, var__ut_array_2, var__ut_array_3, 
	var__ut_float, var__ut_float_0 = var__ut_float, 

	var__ut_vote, var__ut_vote_0 = var__ut_vote, var__ut_vote_1, var__ut_vote_2, var__ut_vote_3, 
	var__ut_vote__VALID, var__ut_vote__VALID_0 = var__ut_vote__VALID, var__ut_vote__VALID_1, var__ut_vote__VALID_2, var__ut_vote__VALID_3, 

	var_COUNT
};

/**
 *  \brief Set data changes flag.
 *  \param item Variable.
 */
DATA_EXT void data_set_changed( const var_t item );

/**
 *  \brief Reset data changes flag for all watching threads.
 *  \param item Variable.
 */
DATA_EXT void data_reset_changed( const var_t item );

/**
 *  \brief Set data changes flags for all variables of watching thread.
 *  \param thread Watching thread.
 */
DATA_EXT void data_set_all_changed( const thread_t thread );

/**
 *  \brief Get data changes flag of variable.
 *  \param thread Watching thread.
 *  \param item Variable.
 *  \return Change flag.
 */
DATA_EXT int data_get_changed( const thread_t thread, const var_t item );

/**
 *  \brief At least one variable from watching list of thread has been changed.
 *  \param thread Watching thread.
 *  \return Change flag.
 */
DATA_EXT int data_get_changed_any( const thread_t thread );

/**
 *  \brief Add variables to watching list of thread.
 *  \param thread Watching thread.
 *  \param vars Variables list (var_COUNT is list terminator).
 *  Only first variable of array will be added if array in list.
 */
DATA_EXT void data_watch( const thread_t thread, const var_t *vars );

/**
 *  \brief Add arrays to watching list of thread.
 *  \param thread Watching thread.
 *  \param vars Arrays list (var_COUNT is list terminator).
 *  Variable and the rest of array will be added if variable in list.
 */
DATA_EXT void data_watch_array( const thread_t thread, const var_t *vars );

/**
 *  \brief Clear watching list of thread.
 *  \param thread Watching thread.
 */
DATA_EXT void data_clear_watch( const thread_t thread );

/**
 *  \brief Reset data changes flag of variable.
 *  \param thread Watching thread.
 *  \param item Variable.
 */
DATA_EXT void data_reset( const thread_t thread, const var_t item );

/**
 *  \brief Reset data changes flags of all variables of thread.
 *  \param thread Watching thread.
 */
DATA_EXT void data_reset_all( const thread_t thread );

/**
 *  \brief Search variable by name.
 *  \param s Variable name.
 *  \return Variable or var_COUNT.
 */
DATA_EXT var_t data_atovar( const char *s );

/**
 *  \brief Get variable name.
 *  \param item Variable.
 */
DATA_EXT char *data_vartoa( const var_t item );

/**
 *  \brief byte-to-string converting.
 *  \param s String buffer.
 *  \param value Value.
 *  \return String.
 */
DATA_EXT char *string_byte( char *s, byte value );

/**
 *  \brief Get value of byte variable.
 *  \param item Variable.
 *  \return Value.
 */
DATA_EXT byte data_get_byte( const var_t item );

/**
 *  \brief Get value of byte variable as string.
 *  \param s String buffer.
 *  \param item Variable.
 *  \return String.
 */
DATA_EXT char *data_get_string_byte( char *s, const var_t item );

/**
 *  \brief Set value of byte variable.
 *  \param item Variable.
 *  \param value Value.
 */
DATA_EXT void data_set_byte( const var_t item, byte value );

/**
 *  \brief Set channel value of byte variable and recalculate voted value.
 *  \param item Variable.
 *  \param h Channel (1..3).
 *  \param value Channel value.
 *  \param voter Vote function.
 */
DATA_EXT void voted_set_byte( const var_t item, byte h, byte value
, bool ( *voter )( byte *, bool, byte, bool, byte, bool, byte ));

/**
 *  \brief Set voted and channels value of byte variable at once.
 *  \param item Variable.
 *  \param value Channel value.
 */
DATA_EXT void joint_set_byte( const var_t item, byte value );

/**
 *  \brief word-to-string converting.
 *  \param s String buffer.
 *  \param value Value.
 *  \return String.
 */
DATA_EXT char *string_word( char *s, word value );

/**
 *  \brief Get value of word variable.
 *  \param item Variable.
 *  \return Value.
 */
DATA_EXT word data_get_word( const var_t item );

/**
 *  \brief Get value of word variable as string.
 *  \param s String buffer.
 *  \param item Variable.
 *  \return String.
 */
DATA_EXT char *data_get_string_word( char *s, const var_t item );

/**
 *  \brief Set value of word variable.
 *  \param item Variable.
 *  \param value Value.
 */
DATA_EXT void data_set_word( const var_t item, word value );

/**
 *  \brief Set channel value of word variable and recalculate voted value.
 *  \param item Variable.
 *  \param h Channel (1..3).
 *  \param value Channel value.
 *  \param voter Vote function.
 */
DATA_EXT void voted_set_word( const var_t item, byte h, word value
, bool ( *voter )( word *, bool, word, bool, word, bool, word ));

/**
 *  \brief Set voted and channels value of word variable at once.
 *  \param item Variable.
 *  \param value Channel value.
 */
DATA_EXT void joint_set_word( const var_t item, word value );

/**
 *  \brief dword-to-string converting.
 *  \param s String buffer.
 *  \param value Value.
 *  \return String.
 */
DATA_EXT char *string_dword( char *s, dword value );

/**
 *  \brief Get value of dword variable.
 *  \param item Variable.
 *  \return Value.
 */
DATA_EXT dword data_get_dword( const var_t item );

/**
 *  \brief Get value of dword variable as string.
 *  \param s String buffer.
 *  \param item Variable.
 *  \return String.
 */
DATA_EXT char *data_get_string_dword( char *s, const var_t item );

/**
 *  \brief Set value of dword variable.
 *  \param item Variable.
 *  \param value Value.
 */
DATA_EXT void data_set_dword( const var_t item, dword value );

/**
 *  \brief Set channel value of dword variable and recalculate voted value.
 *  \param item Variable.
 *  \param h Channel (1..3).
 *  \param value Channel value.
 *  \param voter Vote function.
 */
DATA_EXT void voted_set_dword( const var_t item, byte h, dword value
, bool ( *voter )( dword *, bool, dword, bool, dword, bool, dword ));

/**
 *  \brief Set voted and channels value of dword variable at once.
 *  \param item Variable.
 *  \param value Channel value.
 */
DATA_EXT void joint_set_dword( const var_t item, dword value );

/**
 *  \brief float-to-string converting.
 *  \param s String buffer.
 *  \param value Value.
 *  \return String.
 */
DATA_EXT char *string_float( char *s, float value );

/**
 *  \brief Get value of float variable.
 *  \param item Variable.
 *  \return Value.
 */
DATA_EXT float data_get_float( const var_t item );

/**
 *  \brief Get value of float variable as string.
 *  \param s String buffer.
 *  \param item Variable.
 *  \return String.
 */
DATA_EXT char *data_get_string_float( char *s, const var_t item );

/**
 *  \brief Set value of float variable.
 *  \param item Variable.
 *  \param value Value.
 */
DATA_EXT void data_set_float( const var_t item, float value );

/**
 *  \brief Set channel value of float variable and recalculate voted value.
 *  \param item Variable.
 *  \param h Channel (1..3).
 *  \param value Channel value.
 *  \param voter Vote function.
 */
DATA_EXT void voted_set_float( const var_t item, byte h, float value
, bool ( *voter )( float *, bool, float, bool, float, bool, float ));

/**
 *  \brief Set voted and channels value of float variable at once.
 *  \param item Variable.
 *  \param value Channel value.
 */
DATA_EXT void joint_set_float( const var_t item, float value );

/**
 *  \brief int-to-string converting.
 *  \param s String buffer.
 *  \param value Value.
 *  \return String.
 */
DATA_EXT char *string_int( char *s, int value );

/**
 *  \brief Get value of int variable.
 *  \param item Variable.
 *  \return Value.
 */
DATA_EXT int data_get_int( const var_t item );

/**
 *  \brief Get value of int variable as string.
 *  \param s String buffer.
 *  \param item Variable.
 *  \return String.
 */
DATA_EXT char *data_get_string_int( char *s, const var_t item );

/**
 *  \brief Set value of int variable.
 *  \param item Variable.
 *  \param value Value.
 */
DATA_EXT void data_set_int( const var_t item, int value );

/**
 *  \brief Set channel value of int variable and recalculate voted value.
 *  \param item Variable.
 *  \param h Channel (1..3).
 *  \param value Channel value.
 *  \param voter Vote function.
 */
DATA_EXT void voted_set_int( const var_t item, byte h, int value
, bool ( *voter )( int *, bool, int, bool, int, bool, int ));

/**
 *  \brief Set voted and channels value of int variable at once.
 *  \param item Variable.
 *  \param value Channel value.
 */
DATA_EXT void joint_set_int( const var_t item, int value );

/**
 *  \brief Set value of variable of any type.
 *  \param item Variable.
 *  \param value Value pointer.
 *  Useful only in case variable type is unknown in compile-time.
 */
DATA_EXT void data_set( const var_t item, void *value );

/**
 *  \brief Set taken from string value of variable.
 *  \param item Variable.
 *  \param s String.
 *  Useful only in case variable type is unknown in compile-time.
 */
DATA_EXT void data_set_string( const var_t item, const char *s );

/**
 *  \brief Get value of variable as string.
 *  \param s String buffer.
 *  \param item Variable.
 *  \return String.
 *  Useful only in case variable type is unknown in compile-time.
 */
DATA_EXT char *data_get_string( char *s, const var_t item );

/**
 *  \brief Get variable type as string.
 *  \param item Variable.
 */
DATA_EXT char *data_get_type( const var_t item );

/**
 *  \brief Check voted value of variable is valid.
 *  \param item Variable.
 *  \return Validity flag.
 */
DATA_EXT bool voted_valid( const var_t item );

/**
 *  \brief Lock data access (callback).
 */
DATA_EXT void ( *data_lock_callback )( void );

/**
 *  \brief Unlock data access (callback).
 */
DATA_EXT void ( *data_unlock_callback )( void );

/** \} */

#ifdef __cplusplus
}
#endif

#endif

