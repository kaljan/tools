/**
 * @file    tools_time.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    7.11.2020
 *
 * @brief
 */
#include "tools_time.h"

#ifdef TOOLS_TIME_ENABLED

// #ifdef __linux__
// #include <sys/time.h>
// #endif /* __linux__ */

#include <time.h>

/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t tools_time_now_ms(void) {
    return tools_time_now_us() / 1000;
}

/**
 * @brief
 *
 * @param t
 */
void tools_delay_us(uint64_t us) {
    uint64_t timestamp = tools_time_now_us();
    while (tools_time_now_us() - timestamp < us);
}

/**
 * @brief
 *
 * @param ms
 */
void tools_delay_ms(uint64_t ms)
{
    uint64_t timestamp = tools_time_now_ms();
    while (tools_time_now_ms() - timestamp < ms);
}

/**
 * @brief
 *
 * @param str
 * @param len
 * @param fmt
 * @return const char*
 */
const char* tools_time_currstr(char* str, size_t len, const char* fmt) {
    time_t curr_time = time(NULL);
    struct tm * local_time_ptr = localtime(&curr_time);
    if (local_time_ptr) {
        strftime(str, len, fmt, local_time_ptr);
    }
    return str;
}

#ifdef __linux__

void tools_time_to_tm(struct tm* dst, const time_t* src) {
    struct tm* temp = localtime(src);
    if (NULL != temp) {
        memcpy(dst, temp, sizeof(struct tm));
    }
}

#endif /* __linux__ */
#endif /* TOOLS_TIME_ENABLED */
