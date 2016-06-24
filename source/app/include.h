/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  include.h
 *  \brief  All header files.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *      S T A N D A R D   L I B R A R I E S      *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

// WIN32 /////////////////////////////////////////
// MSDOS /////////////////////////////////////////
#if defined( __WIN32__ ) || defined( __MSDOS__ )
#include <timer.h>
#include <unistd.h>

//////////////////////////////////////////////////
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>

#ifdef __cplusplus

#endif

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *          C O N F I G U R A T I O N            *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "config.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *      C O M M O N   D E F I N I T I O N S      *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "define.h"
#include "app.h"
#include "co.h"
#include "data.h"
#include "error.h"
#include "log.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *               H A R D W A R E                 *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "clock.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *               D E B U G G I N G               *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ut.h"
#include "getch.h"
#include "char.h"
#include "console.h"

#ifdef __cplusplus

#endif

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *            A P P L I C A T I O N              *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "data-str.h"
#include "data-vote.h"
#include "ini.h"

#ifdef __cplusplus

#endif
