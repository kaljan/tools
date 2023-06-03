/**
 * @file    dbg_timer.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    06.11.2020
 *
 * @brief
 */
#ifndef DBG_TIMER_H
#define DBG_TIMER_H

#include "tools_debug.h"
#include "tools_opt.h"

#ifdef TOOLS_TIMER_DBG_LEVEL
#if (TOOLS_TIMER_DBG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define timer_print_v(...) print_v(__VA_ARGS__)
#define timer_log_v(...) log_v(__VA_ARGS__)
#else
#define timer_print_v(...)
#define timer_log_v(...)
#endif /* (TOOLS_TIMER_DBG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define timer_print_d(...) print_d(__VA_ARGS__)
#define timer_log_d(...) log_d(__VA_ARGS__)
#else
#define timer_print_d(...)
#define timer_log_d(...)
#endif /* (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define timer_print_i(...) print_i(__VA_ARGS__)
#define timer_log_i(...) log_i(__VA_ARGS__)
#else
#define timer_print_i(...)
#define timer_log_i(...)
#endif /* (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define timer_print_w(...) print_w(__VA_ARGS__)
#define timer_log_w(...) log_w(__VA_ARGS__)
#else
#define timer_print_w(...)
#define timer_log_w(...)
#endif /* (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define timer_print_e(...) print_e(__VA_ARGS__)
#define timer_log_e(...) log_e(__VA_ARGS__)
#else
#define timer_print_e(...)
#define timer_log_e(...)
#endif /* (TOOLS_TIMER_DBG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define timer_print_v(...)
#define timer_print_i(...)
#define timer_print_t(...)
#define timer_print_d(...)
#define timer_print_w(...)
#define timer_print_e(...)
#define timer_log_v(...)
#define timer_log_i(...)
#define timer_log_t(...)
#define timer_log_d(...)
#define timer_log_w(...)
#define timer_log_e(...)
#endif /* TOOLS_TIMER_DBG_LEVEL */

#endif /* DBG_TIMER_H */
/* EOF */
