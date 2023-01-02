/**
 * @file 	tools_time.c
 * @author	Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version	1.0.0
 * @date	Mar 11, 2021
 *
 * @brief
 */


#include "tools_time.h"

#ifdef TOOLS_TIME_ENABLED
#ifdef __linux__

#include <sys/time.h>
#include <time.h>

#define tools_time_to_u64(tv) (uint64_t)((tv.tv_sec* 1000000) + tv.tv_usec)

static uint64_t p_start_time = 0;
static struct timeval p_current_time;

/**
 * @brief
 *
 */
void tools_time_init(void) {
	tools_time_current(&p_current_time);
	p_start_time = tools_time_to_u64(p_current_time);
}

/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t tools_time_now_us(void) {
	tools_time_current(&p_current_time);
	uint64_t ret = tools_time_to_u64(p_current_time);
	if (ret && ret > p_start_time) {
		return ret - p_start_time;
	} else {
		ret = 0;
	}
	return ret;
}

#else
#error ERROR: This file only for linux
#endif /* __linux */
#endif /* TOOLS_TIME_ENABLED */
