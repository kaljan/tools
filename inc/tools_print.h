/**
 * @file    tools_print.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    27.12.2022
 *
 * @brief
 */
#ifndef TOOLS_PRINT_H
#define TOOLS_PRINT_H

#include "tools_opt.h"

#ifdef TOOLS_THREAD_ENABLED
#ifdef __linux__
#include <sys/stat.h>
#include <pthread.h>
#endif /* __linux__ */
#endif /* TOOLS_THREAD_ENABLED */

/* Debug message buffer size */
#ifndef TOOLS_DEBUG_BUF_SIZE
#define TOOLS_DEBUG_BUF_SIZE   4096
#endif /* TOOLS_DEBUG_BUF_SIZE */

/* Lock when pthread enabled */
#ifdef TOOLS_THREAD_ENABLED
#ifdef __linux__
#define TOOLS_PRINT_LOCK() tools_print_lock()
#define TOOLS_PRINT_UNLOCK() tools_print_unlock()
#else
#define TOOLS_PRINT_LOCK()
#define TOOLS_PRINT_UNLOCK()
#endif /* __linux__ */
#else
#define TOOLS_PRINT_LOCK()
#define TOOLS_PRINT_UNLOCK()
#endif /* TOOLS_THREAD_ENABLED */

#ifdef TOOLS_PRINT_ENABLED

#ifdef TOOLS_COLOR_ENABLED
#define C_DEFAULT    "\33[0m"
#define C_BOLD       "\33[1m"
#define C_ITALIC     "\33[3m"
#define C_UNDERLINE  "\33[4m"
#define C_SBLINK     "\33[5m"
#define C_FBLINK     "\33[6m"
#define C_SELECTED   "\33[7m"

#define F_BLACK      "\33[30m"
#define F_RED        "\33[31m"
#define F_GREEN      "\33[32m"
#define F_YELLOW     "\33[33m"
#define F_BLUE       "\33[34m"
#define F_MAGENTA    "\33[35m"
#define F_CYAN       "\33[36m"
#define F_WHITE      "\33[37m"

#define B_BLACK      "\33[40m"
#define B_RED        "\33[41m"
#define B_GREEN      "\33[42m"
#define B_YELLOW     "\33[43m"
#define B_BLUE       "\33[44m"
#define B_MAGENTA    "\33[45m"
#define B_CYAN       "\33[46m"
#define B_WHITE      "\33[47m"

#define FB_GREY      "\33[90m"
#define FB_RED       "\33[91m"
#define FB_GREEN     "\33[92m"
#define FB_YELLOW    "\33[93m"
#define FB_BLUE      "\33[94m"
#define FB_MAGENTA   "\33[95m"
#define FB_CYAN      "\33[96m"
#define FB_WHITE     "\33[97m"

#define BB_GREY      "\33[100m"
#define BB_RED       "\33[101m"
#define BB_GREEN     "\33[102m"
#define BB_YELLOW    "\33[103m"
#define BB_BLUE      "\33[104m"
#define BB_MAGENTA   "\33[105m"
#define BB_CYAN      "\33[106m"
#define BB_WHITE     "\33[107m"
#else
#define C_DEFAULT    ""
#define C_BOLD       ""
#define C_ITALIC     ""
#define C_UNDERLINE  ""
#define C_SBLINK     ""
#define C_FBLINK     ""
#define C_SELECTED   ""

#define F_BLACK      ""
#define F_RED        ""
#define F_GREEN      ""
#define F_YELLOW     ""
#define F_BLUE       ""
#define F_MAGENTA    ""
#define F_CYAN       ""
#define F_WHITE      ""

#define B_BLACK      ""
#define B_RED        ""
#define B_GREEN      ""
#define B_YELLOW     ""
#define B_BLUE       ""
#define B_MAGENTA    ""
#define B_CYAN       ""
#define B_WHITE      ""

#define FB_GREY      ""
#define FB_RED       ""
#define FB_GREEN     ""
#define FB_YELLOW    ""
#define FB_BLUE      ""
#define FB_MAGENTA   ""
#define FB_CYAN      ""
#define FB_WHITE     ""

#define BB_GREY       ""
#define BB_RED        ""
#define BB_GREEN      ""
#define BB_YELLOW     ""
#define BB_BLUE       ""
#define BB_MAGENTA    ""
#define BB_CYAN       ""
#define BB_WHITE      ""
#endif /* TOOLS_COLOR_ENABLED */

#define C_ENDLINE        "\n"

#define TOOLS_PRINT_INFO    0
#define TOOLS_PRINT_WARNING 1
#define TOOLS_PRINT_ERROR   2

#define VA_ARG_UNPACK(str, fnm) \
    va_list vaptr; \
    va_start(vaptr, fnm); \
    TOOLS_PRINT_LOCK(); \
    vsprintf(str, fnm, vaptr); \
    va_end(vaptr);

#ifndef PRINT_MSG_BUFFER_SIZE
#define PRINT_MSG_BUFFER_SIZE 1024
#endif /* PRINT_MSG_BUFFER_SIZE */

#define msg_i(...)     print_msg(TOOLS_PRINT_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define msg_w(...)     print_msg(TOOLS_PRINT_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define msg_e(...)     print_msg(TOOLS_PRINT_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define msg_errno(...) print_errno(__FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void tools_print_lock(void);
void tools_print_unlock(void);

void print_msg(int type, const char* file, int line, const char* fmt, ...);
void print_errno(const char *file_name, int line, const char* fmt, ...);

void tools_print_stat(struct stat const* const fstat);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else
#define msg_i(...)
#define msg_w(...)
#define msg_e(...)
#define msr_errno(...)
#endif /* TOOLS_PRINT_ENABLED */
#endif /* TOOLS_PRINT_H */
