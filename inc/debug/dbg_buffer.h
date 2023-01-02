/**
 * @file    dbg_buffer.h
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    Nov 7, 2020
 *
 * @brief
 */
#ifndef DBG_BUFFER_H
#define DBG_BUFFER_H

#include "tools_debug.h"

#ifdef TOOLS_BUF_DEBUG_LEVEL
#if (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define buf_print_v(...) tools_debug_print(TOOLS_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_print_v(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define buf_print_d(...) tools_debug_print(TOOLS_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_print_d(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define buf_print_i(...) tools_debug_print(TOOLS_LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_print_i(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define buf_print_w(...) tools_debug_print(TOOLS_LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_print_w(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define buf_print_e(...) tools_debug_print(TOOLS_LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_print_e(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define buf_print_v(...)
#define buf_print_d(...)
#define buf_print_i(...)
#define buf_print_w(...)
#define buf_print_e(...)
#endif /* TOOLS_BUF_DEBUG_LEVEL */


#ifdef TOOLS_BUF_DEBUG_LEVEL
#if (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define buf_log_v(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_VERBOSE, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_log_v(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define buf_log_d(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_DEBUG, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_log_d(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define buf_log_i(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_INFO, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_log_i(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define buf_log_w(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_WARNING, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_log_w(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define buf_log_e(TAG, ...) tools_debug_log(TOOLS_LOG_LEVEL_ERROR, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_log_e(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define buf_log_v(TAG, ...)
#define buf_log_d(TAG, ...)
#define buf_log_i(TAG, ...)
#define buf_log_w(TAG, ...)
#define buf_log_e(TAG, ...)
#endif /* TOOLS_BUF_DEBUG_LEVEL */


#ifdef TOOLS_BUF_DEBUG_LEVEL
#if (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define buf_trace_print_v(...) tools_trace_print(TOOLS_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_print_v(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define buf_trace_print_d(...) tools_trace_print(TOOLS_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_print_d(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define buf_trace_print_i(...) tools_trace_print(TOOLS_LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_print_i(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define buf_trace_print_w(...) tools_trace_print(TOOLS_LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_print_w(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define buf_trace_print_e(...) tools_trace_print(TOOLS_LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_print_e(...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define buf_trace_print_v(...)
#define buf_trace_print_d(...)
#define buf_trace_print_i(...)
#define buf_trace_print_w(...)
#define buf_trace_print_e(...)
#endif /* TOOLS_BUF_DEBUG_LEVEL */


#ifdef TOOLS_BUF_DEBUG_LEVEL
#if (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE)
#define buf_trace_log_v(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_VERBOSE, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_log_v(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL == TOOLS_LOG_LEVEL_VERBOSE) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG)
#define buf_trace_log_d(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_DEBUG, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_log_d(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_DEBUG) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO)
#define buf_trace_log_i(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_INFO, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_log_i(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_INFO) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING)
#define buf_trace_log_w(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_WARNING, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_log_w(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_WARNING) */
#if (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR)
#define buf_trace_log_e(TAG, ...) tools_trace_log(TOOLS_LOG_LEVEL_ERROR, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define buf_trace_log_e(TAG, ...)
#endif /* (TOOLS_BUF_DEBUG_LEVEL <= TOOLS_LOG_LEVEL_ERROR) */
#else
#define buf_trace_log_v(TAG, ...)
#define buf_trace_log_d(TAG, ...)
#define buf_trace_log_i(TAG, ...)
#define buf_trace_log_w(TAG, ...)
#define buf_trace_log_e(TAG, ...)
#endif /* TOOLS_BUF_DEBUG_LEVEL */
#endif /* DBG_BUFFER_H */
/* EOF */
