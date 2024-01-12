/**
 * @file    tools_opt.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    27.12.2022
 *
 * @brief
 */
#ifndef TOOLS_OPT_H
#define TOOLS_OPT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "tools_types.h"

#ifdef TOOLS_OPT
#include TOOLS_OPT
#else
#define TOOLS_ALLOC_ENABLED
#define TOOLS_ASSERT_ENABLED
#define TOOLS_BUFFER_ENABLED
#define TOOLS_COLOR_ENABLED
#define TOOLS_CRC_ENABLED
#define TOOLS_CLIOPT_ENABLED
#define TOOLS_DEBUG_ENABLED
#define TOOLS_DEMUX_ENABLED
#define TOOLS_DLIST_ENABLED
#define TOOLS_DTC_ENABLE
#define TOOLS_FIFO_ENABLED
#define TOOLS_HASHMAP_ENABLED
#define TOOLS_HEXDUMP_ENABLED
#define TOOLS_PRINT_ENABLED
#define TOOLS_RANDOM_ENABLED
#define TOOLS_SLIST_ENABLED
#define TOOLS_STRING_ENABLED
#define TOOLS_THREAD_ENABLED
#define TOOLS_TIME_ENABLED
#define TOOLS_TIMER_ENABLED

#ifdef TOOLS_DEBUG_ENABLED
#define TOOLS_PRINT_LEVEL       TOOLS_DEBUG_LEVEL_DEBUG
#define TOOLS_LOG_LEVEL         TOOLS_DEBUG_LEVEL_DEBUG
#define TOOLS_TRACE_PRINT_LEVEL TOOLS_DEBUG_LEVEL_DEBUG
#define TOOLS_TRACE_LOG_LEVEL   TOOLS_DEBUG_LEVEL_DEBUG

#define TOOLS_THREAD_DBG_LEVEL  TOOLS_DEBUG_LEVEL_WARNING
#endif /* TOOLS_DEBUG_ENABLED */
#endif /* TOOLS_OPT */

#endif /* TOOLS_OPT_H */
