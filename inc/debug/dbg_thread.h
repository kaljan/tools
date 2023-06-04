/**
 * @file    dbg_timer.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    06.11.2020
 *
 * @brief
 */
#ifndef DBG_THREAD_H
#define DBG_THREAD_H

#include "tools_debug.h"
#include "tools_opt.h"

#ifdef TOOLS_THREAD_DBG_LEVEL
#if (TOOLS_THREAD_DBG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define thread_print_v(...) print_v(__VA_ARGS__)
#define thread_log_v(...) log_v(__VA_ARGS__)
#else
#define thread_print_v(...)
#define thread_log_v(...)
#endif /* (TOOLS_THREAD_DBG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define thread_print_d(...) print_d(__VA_ARGS__)
#define thread_log_d(...) log_d(__VA_ARGS__)
#else
#define thread_print_d(...)
#define thread_log_d(...)
#endif /* (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define thread_print_i(...) print_i(__VA_ARGS__)
#define thread_log_i(...) log_i(__VA_ARGS__)
#else
#define thread_print_i(...)
#define thread_log_i(...)
#endif /* (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define thread_print_w(...) print_w(__VA_ARGS__)
#define thread_log_w(...) log_w(__VA_ARGS__)
#else
#define thread_print_w(...)
#define thread_log_w(...)
#endif /* (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define thread_print_e(...) print_e(__VA_ARGS__)
#define thread_log_e(...) log_e(__VA_ARGS__)
#else
#define thread_print_e(...)
#define thread_log_e(...)
#endif /* (TOOLS_THREAD_DBG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define thread_print_v(...)
#define thread_print_i(...)
#define thread_print_t(...)
#define thread_print_d(...)
#define thread_print_w(...)
#define thread_print_e(...)
#define thread_log_v(...)
#define thread_log_i(...)
#define thread_log_t(...)
#define thread_log_d(...)
#define thread_log_w(...)
#define thread_log_e(...)
#endif /* TOOLS_THREAD_DBG_LEVEL */

#endif /* DBG_THREAD_H */
/* EOF */
