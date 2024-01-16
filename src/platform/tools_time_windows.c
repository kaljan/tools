/**
 * @file    tools_time_windows.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    07.11.2020
 *
 * @brief
 */


#include "tools_time.h"

#ifdef TOOLS_TIME_ENABLED
#if defined(_WIN32) || defined(__CYGWIN__)

#include <windows.h>

int tools_time_current(struct timeval* tv) {
    ASSERT_PTR_RET(tv, STATUS_SUCCESS)
    static FILETIME               filetime; /* 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 00:00 UTC */
    static ULARGE_INTEGER         x;
    static ULONGLONG              usec;
    static const ULONGLONG epoch_offset_us = 11644473600000000ULL; /* microseconds betweeen Jan 1,1601 and Jan 1,1970 */

#if _WIN32_WINNT >= _WIN32_WINNT_WIN8
    GetSystemTimePreciseAsFileTime(&filetime);
#else
    GetSystemTimeAsFileTime(&filetime);
#endif
    x.LowPart =  filetime.dwLowDateTime;
    x.HighPart = filetime.dwHighDateTime;
    usec = x.QuadPart / 10  -  epoch_offset_us;
    tv->tv_sec  = (long)(usec / 1000000ULL);
    tv->tv_usec = (long)(usec % 1000000ULL);
    return 0;
}

static uint64_t p_tools_time_now_us(void) {
    /* microseconds betweeen Jan 1,1601 and Jan 1,1970 */
    static const ULONGLONG epoch_offset_us = 11644473600000000ULL;

    /* 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 00:00 UTC */
    static FILETIME filetime;

    /* Temporary time storage */
    static ULARGE_INTEGER  temp;

#if _WIN32_WINNT >= _WIN32_WINNT_WIN8
    GetSystemTimePreciseAsFileTime(&filetime);
#else
    GetSystemTimeAsFileTime(&filetime);
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN8 */
    temp.LowPart =  filetime.dwLowDateTime;
    temp.HighPart = filetime.dwHighDateTime;
    return (uint64_t)(temp.QuadPart / 10  -  epoch_offset_us);
}

/* Initial system time */
static uint64_t p_start_time = 0;

/**
 * @brief
 *
 */
void tools_time_init(void) {
    p_start_time = p_tools_time_now_us();
}

/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t tools_time_now_us(void) {
    uint64_t ret = p_tools_time_now_us();
    if (ret && ret > p_start_time) {
        return ret - p_start_time;
    } else {
        ret = 0;
    }
    return ret;
}

#else
#error ERROR: This file only for windows
#endif /* _WIN32 */
#endif /* TOOLS_TIME_ENABLED */
