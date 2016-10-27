/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  flush.c
 *  \brief  Flush output.
 *  \author  Vitaly Kravtsov
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>

void flush( void )
{
	fflush( stdout );
}
