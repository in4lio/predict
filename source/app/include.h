/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  include.h
 *  \brief  All header files.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *        S T A N D A R D   L I B R A R Y        *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>

// LINUX /////////////////////////////////////////
#ifdef __linux__
#include <stdint.h>

// DOS ///////////////////////////////////////////
#else
#include "stdint.h"
#include "timer.h"

//////////////////////////////////////////////////
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
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
 *       H A R D W A R E   D R I V E R S         *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "clock.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *               D E B U G G I N G               *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ut.h"
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
#include "vote.h"
#include "ini.h"

#ifdef __cplusplus

#endif
