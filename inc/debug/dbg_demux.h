/**
 * @file    dbg_demux.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    07.11.2020
 *
 * @brief
 */
#ifndef DBG_DEMUX_H
#define DBG_DEMUX_H

#include "tools_debug.h"

#ifdef TOOLS_DEMUX_DEBUG_LEVEL
#if (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define demux_print_v(...) tools_debug_print(TOOLS_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_print_v(...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define demux_print_d(...) tools_debug_print(TOOLS_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_print_d(...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define demux_print_i(...) tools_debug_print(TOOLS_LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_print_i(...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define demux_print_w(...) tools_debug_print(TOOLS_LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_print_w(...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define demux_print_e(...) tools_debug_print(TOOLS_LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_print_e(...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define demux_print_v(...)
#define demux_print_d(...)
#define demux_print_i(...)
#define demux_print_w(...)
#define demux_print_e(...)
#endif /* TOOLS_DEMUX_DEBUG_LEVEL */


#ifdef TOOLS_DEMUX_DEBUG_LEVEL
#if (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define demux_log_v(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_VERBOSE, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_log_v(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define demux_log_d(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_DEBUG, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_log_d(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define demux_log_i(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_INFO, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_log_i(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define demux_log_w(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_WARNING, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_log_w(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define demux_log_e(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_ERROR, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_log_e(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define demux_log_v(TAG, ...)
#define demux_log_d(TAG, ...)
#define demux_log_i(TAG, ...)
#define demux_log_w(TAG, ...)
#define demux_log_e(TAG, ...)
#endif /* TOOLS_DEMUX_DEBUG_LEVEL */


#ifdef TOOLS_DEMUX_DEBUG_LEVEL
#if (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define demux_trace_print_v(TAG, ...) tools_trace_print(TOOLS_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_print_v(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define demux_trace_print_d(TAG, ...) tools_trace_print(TOOLS_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_print_d(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define demux_trace_print_i(TAG, ...) tools_trace_print(TOOLS_LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_print_i(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define demux_trace_print_w(TAG, ...) tools_trace_print(TOOLS_LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_print_w(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define demux_trace_print_e(TAG, ...) tools_trace_print(TOOLS_LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_print_e(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define demux_trace_print_v(TAG, ...)
#define demux_trace_print_d(TAG, ...)
#define demux_trace_print_i(TAG, ...)
#define demux_trace_print_w(TAG, ...)
#define demux_trace_print_e(TAG, ...)
#endif /* TOOLS_DEMUX_DEBUG_LEVEL */


#ifdef TOOLS_DEMUX_DEBUG_LEVEL
#if (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define demux_trace_log_v(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_VERBOSE, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_log_v(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define demux_trace_log_d(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_DEBUG, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_log_d(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define demux_trace_log_i(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_INFO, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_log_i(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define demux_trace_log_w(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_WARNING, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_log_w(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define demux_trace_log_e(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_ERROR, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define demux_trace_log_e(TAG, ...)
#endif /* (TOOLS_DEMUX_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define demux_trace_log_v(TAG, ...)
#define demux_trace_log_d(TAG, ...)
#define demux_trace_log_i(TAG, ...)
#define demux_trace_log_w(TAG, ...)
#define demux_trace_log_e(TAG, ...)
#endif /* TOOLS_DEMUX_DEBUG_LEVEL */

#endif /* DBG_DEMUX_H */
/* EOF */
