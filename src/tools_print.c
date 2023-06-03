/**
 * @file    tools_print.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    27.12.2022
 *
 * @brief
 */
#include "tools_print.h"

#ifdef TOOLS_PRINT_ENABLED

#define PRINT_INFO_COLOR    C_BOLD F_GREEN
#define PRINT_WARNING_COLOR C_BOLD F_YELLOW
#define PRINT_ERROR_COLOR   C_BOLD F_RED

/* Lock when pthread enabled */
#ifdef TOOLS_THREAD_ENABLED
#ifdef __linux__

static pthread_mutex_t tools_print_mutex;

void tools_print_lock(void) {
    pthread_mutex_lock(&tools_print_mutex);
}

void tools_print_unlock(void) {
    pthread_mutex_unlock(&tools_print_mutex);
}

#endif /* __linux__ */
#endif /* TOOLS_THREAD_ENABLED */

#ifdef TOOLS_COLOR_ENABLED
static const char* print_msg_color[] = {
    PRINT_INFO_COLOR,
    PRINT_WARNING_COLOR,
    PRINT_ERROR_COLOR
};
#endif /* TOOLS_COLOR_ENABLED */

static const char* print_msg_label[] = {
    "INFO", "WARNING", "ERROR"
};

#ifdef TOOLS_COLOR_ENABLED
static const char print_msg_format[] = "%s[%s:%d] %s: %s" C_DEFAULT "\n";
#else
static const char print_msg_format[] = "[%s:%d] %s: %s\n";
#endif

static char print_msg_buffer[PRINT_MSG_BUFFER_SIZE];

/**
 * @brief
 *
 * @param type
 * @param file
 * @param line
 * @param fmt
 * @param ...
 */
void print_msg(int type, const char* file, int line, const char* fmt, ...) {
    VA_ARG_UNPACK(print_msg_buffer, fmt)

    if (type > TOOLS_PRINT_ERROR) {
        TOOLS_PRINT_UNLOCK();
        return;
    }
    // TOOLS_PRINT_LOCK();
#ifdef TOOLS_COLOR_ENABLED
    printf(print_msg_format, print_msg_color[type], file,
        line, print_msg_label[type], print_msg_buffer);
#else
    printf(print_msg_format, file, line,
        print_msg_label[type], print_msg_buffer);
#endif
    TOOLS_PRINT_UNLOCK();
}

/* errno print format string */
static const char print_errno_format[] =
#ifdef TOOLS_COLOR_ENABLED
    F_RED C_BOLD  "[%s:%d] %s; ERROR(%d) %s" C_DEFAULT C_ENDLINE;
#else
    "[%s:%d] %s; ERROR(%d) %s\n";
#endif

static char print_errno_buffer[PRINT_MSG_BUFFER_SIZE];

/**
 * @brief
 *
 * @param file_name
 * @param line
 * @param fmt
 * @param ...
 */
void print_errno(const char *file_name, int line, const char* fmt, ...) {
    VA_ARG_UNPACK(print_errno_buffer, fmt);
    printf(print_errno_format, file_name, line,
        print_errno_buffer, errno, strerror(errno));
    TOOLS_PRINT_UNLOCK();
}


#endif /* TOOLS_PRINT_ENABLED */
