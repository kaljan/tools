/**
 * @file 	tools_time.h
 * @author	Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version	1.0.0
 * @date	Mar 11, 2021
 *
 * @brief
 *
 */

#ifndef TOOLS_TIME_H
#define TOOLS_TIME_H

#include "tools_opt.h"

#ifdef TOOLS_TIME_ENABLED

#if defined(_WIN32) || defined(__CYGWIN__)
#include <winsock.h>
#endif /* _WIN32 || __CYGWIN__ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __linux__
#define tools_time_current(t) gettimeofday(t, NULL)
#else
int tools_time_current(struct timeval* t);
#endif

void tools_time_init(void);
uint64_t tools_time_now_us(void);
uint64_t tools_time_now_ms(void);
void tools_delay_us(uint64_t t);
void tools_delay_ms(uint64_t ms);

const char* tools_time_currstr(char* str, size_t len, const char* fmt);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_TIME_ENABLED */
#endif /* TOOLS_TIME_H */

