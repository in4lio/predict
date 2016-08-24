
/*  error.c was generated by yup.py (yupp) 0.9b4
    out of error.yu-c 
 *//**
 *  \file  error.c (error.yu-c)
 *  \brief  Error messages.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define LOGGING
#define LINK_CONSOLE

#define LINK_UT

#define LINK_UT_UT
#define LINK_UT_CORO
#define LINK_UT_DATA

#define ERROR_IMPLEMENT

const char *const error_format[] = {
	"TEST_COUNT = %d (must be %d)",
	"ut_stage_%d is failed",
	"heap is overflowed",
	"fopen(%s): %s",
	"opendir(%s): can't open directory",
	"%s is empty",
	"fread(%s) is failed",

};
