/**
 * @file 	tools_debug.h
 * @author	Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version	1.0.0
 * @date	Apr 14, 2019
 *
 * @brief
 */

#ifndef TOOLS_DEBUG_H
#define TOOLS_DEBUG_H

#include "tools_opt.h"

#ifdef TOOLS_DEBUG_ENABLED

/* Debug level definition */
#define TOOLS_DEBUG_LEVEL_VERBOSE  0
#define TOOLS_DEBUG_LEVEL_DEBUG    1
#define TOOLS_DEBUG_LEVEL_INFO     2
#define TOOLS_DEBUG_LEVEL_WARNING  3
#define TOOLS_DEBUG_LEVEL_ERROR    4

#if defined (TOOLS_LOG_LEVEL) || defined (TOOLS_TRACE_LOG_LEVEL)
#define TOOLS_TAG_LEN_MAX  256
#endif /* TOOLS_DEBUG_LEVEL */

#ifdef TOOLS_PRINT_LEVEL
#if (TOOLS_PRINT_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE)
#define print_v(...) tools_debug_print(TOOLS_DEBUG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define print_v(...)
#endif /* (TOOLS_PRINT_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE) */
#if (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG)
#define print_d(...) tools_debug_print(TOOLS_DEBUG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define print_d(...)
#endif /* (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG) */
#if (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_INFO)
#define print_i(...) tools_debug_print(TOOLS_DEBUG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define print_i(...)
#endif /* (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_INFO) */
#if (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING)
#define print_w(...) tools_debug_print(TOOLS_DEBUG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
#define print_w(...)
#endif /* (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING) */
#if (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR)
#define print_e(...) tools_debug_print(TOOLS_DEBUG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define print_e(...)
#endif /* (TOOLS_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR) */
#else
#define print_v(...)
#define print_d(...)
#define print_i(...)
#define print_w(...)
#define print_e(...)
#endif /* TOOLS_PRINT_LEVEL */


#ifdef TOOLS_LOG_LEVEL
#if (TOOLS_LOG_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE)
#define log_v(TAG, ...) tools_debug_log(TOOLS_DEBUG_LEVEL_VERBOSE, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define log_v(TAG, ...)
#endif /* (TOOLS_LOG_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE) */
#if (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG)
#define log_d(TAG, ...) tools_debug_log(TOOLS_DEBUG_LEVEL_DEBUG, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define log_d(TAG, ...)
#endif /* (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG) */
#if (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_INFO)
#define log_i(TAG, ...) tools_debug_log(TOOLS_DEBUG_LEVEL_INFO, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define log_i(TAG, ...)
#endif /* (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_INFO) */
#if (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING)
#define log_w(TAG, ...) tools_debug_log(TOOLS_DEBUG_LEVEL_WARNING, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define log_w(TAG, ...)
#endif /* (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING) */
#if (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR)
#define log_e(TAG, ...) tools_debug_log(TOOLS_DEBUG_LEVEL_ERROR, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define log_e(TAG, ...)
#endif /* (TOOLS_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR) */
#else
#define log_v(TAG, ...)
#define log_d(TAG, ...)
#define log_i(TAG, ...)
#define log_w(TAG, ...)
#define log_e(TAG, ...)
#endif /* TOOLS_LOG_LEVEL */


#ifdef TOOLS_TRACE_PRINT_LEVEL
#if (TOOLS_TRACE_PRINT_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE)
#define trace_print_v(...) tools_trace_print(TOOLS_DEBUG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define trace_print_v(...)
#endif /* (TOOLS_TRACE_PRINT_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE) */
#if (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG)
#define trace_print_d(...) tools_trace_print(TOOLS_DEBUG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define trace_print_d(...)
#endif /* (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG) */
#if (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_INFO)
#define trace_print_i(...) tools_trace_print(TOOLS_DEBUG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define trace_print_i(...)
#endif /* (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_INFO) */
#if (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING)
#define trace_print_w(...) tools_trace_print(TOOLS_DEBUG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
#define trace_print_w(...)
#endif /* (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING) */
#if (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR)
#define trace_print_e(...) tools_trace_print(TOOLS_DEBUG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define trace_print_e(...)
#endif /* (TOOLS_TRACE_PRINT_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR) */
#else
#define trace_print_v(...)
#define trace_print_d(...)
#define trace_print_i(...)
#define trace_print_w(...)
#define trace_print_e(...)
#endif /* TOOLS_TRACE_PRINT_LEVEL */

#ifdef TOOLS_TRACE_LOG_LEVEL
#if (TOOLS_TRACE_LOG_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE)
#define trace_log_v(TAG, ...) tools_trace_log(TOOLS_DEBUG_LEVEL_VERBOSE, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define trace_log_v(TAG, ...)
#endif /* (TOOLS_TRACE_LOG_LEVEL == TOOLS_DEBUG_LEVEL_VERBOSE) */
#if (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG)
#define trace_log_d(TAG, ...) tools_trace_log(TOOLS_DEBUG_LEVEL_DEBUG, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define trace_log_d(TAG, ...)
#endif /* (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_DEBUG) */
#if (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_INFO)
#define trace_log_i(TAG, ...) tools_trace_log(TOOLS_DEBUG_LEVEL_INFO, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define trace_log_i(TAG, ...)
#endif /* (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_INFO) */
#if (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING)
#define trace_log_w(TAG, ...) tools_trace_log(TOOLS_DEBUG_LEVEL_WARNING, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define trace_log_w(TAG, ...)
#endif /* (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_WARNING) */
#if (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR)
#define trace_log_e(TAG, ...) tools_trace_log(TOOLS_DEBUG_LEVEL_ERROR, TAG, __func__, __LINE__, __VA_ARGS__)
#else
#define trace_log_e(TAG, ...)
#endif /* (TOOLS_TRACE_LOG_LEVEL <= TOOLS_DEBUG_LEVEL_ERROR) */
#else
#define trace_log_v(TAG, ...)
#define trace_log_d(TAG, ...)
#define trace_log_i(TAG, ...)
#define trace_log_w(TAG, ...)
#define trace_log_e(TAG, ...)
#endif /* TOOLS_TRACE_LOG_LEVEL */


#define DBG_OBJ_STR_SIZE    64

#define DEBUG_OBJECT debug_object_t dbg;

typedef struct debug_object {
    /* Debug object id */
    int id;

    /* Debug object type name */
    char obj_type_name[DBG_OBJ_STR_SIZE];

    /* Debug object name */
    char obj_name[DBG_OBJ_STR_SIZE];

    /* Debug object parent name */
    char obj_parent[DBG_OBJ_STR_SIZE];

    /* Debug object tag */
    char tag[DBG_OBJ_STR_SIZE * 4];
} debug_object_t;


#ifdef __cplusplus
extern "C" {
#endif/* __cplusplus */

#ifdef TOOLS_PRINT_LEVEL
void tools_debug_print(int lvl, const char* file_name, int line, const char* fmt, ...);
#endif /* TOOLS_PRINT_LEVEL */

#ifdef TOOLS_LOG_LEVEL
void tools_debug_log(int lvl, const char* tag, const char* func_name, int line, const char* fmt, ...);
#endif /* TOOLS_LOG_LEVEL */

#ifdef TOOLS_TRACE_PRINT_LEVEL
void tools_trace_print(int lvl, const char* file_name, int line, const char* fmt, ...);
#endif /* TOOLS_TRACE_PRINT_LEVEL */

#ifdef TOOLS_TRACE_LOG_LEVEL
void tools_trace_log(int lvl, const char* tag, const char* func_name, int line, const char* fmt, ...);
#endif /* TOOLS_TRACE_LOG_LEVEL */

void create_tag(debug_object_t* d_obj, const char* obj_type, const char* obj_name, const char* parent_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#else
#define DEBUG_OBJECT
#define create_tag(obj, obj_type_name, obj_na,e, parent_name)
#endif /* TOOLS_DEBUG_ENABLED */
#endif /* TOOLS_DEBUG_H */
