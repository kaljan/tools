/**
 * @file 	tools_debug.c
 * @author	Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version	1.0.0
 * @date	Apr 14, 2019
 *
 * @brief
 */
#include "tools_debug.h"

#ifdef TOOLS_DEBUG_ENABLED

#include "tools_assert.h"
#include "tools_print.h"
#include "tools_string.h"
#include "tools_time.h"

/* Print format definitions if enabled color */
#ifdef TOOLS_COLOR_ENABLED

/* Log level color */
#define LOG_V_COLOR			F_BLUE
#define LOG_I_COLOR			F_GREEN
#define LOG_T_COLOR			F_MAGENTA
#define LOG_D_COLOR			F_CYAN
#define LOG_W_COLOR			F_YELLOW
#define LOG_E_COLOR			F_RED

/* Log level label */
static const char* p_debug_level_label[] = {
	LOG_V_COLOR "<" C_BOLD "V" C_DEFAULT LOG_V_COLOR ">\0",
	LOG_D_COLOR "<" C_BOLD "D" C_DEFAULT LOG_D_COLOR ">\0",
	LOG_I_COLOR "<" C_BOLD "I" C_DEFAULT LOG_I_COLOR ">\0",
	LOG_W_COLOR "<" C_BOLD "W" C_DEFAULT LOG_W_COLOR ">\0",
	LOG_E_COLOR "<" C_BOLD "E" C_DEFAULT LOG_E_COLOR ">\0",
};

/* TODO refactor */
static const char* p_message_color[] = {
	C_DEFAULT LOG_V_COLOR "\0",
	C_DEFAULT LOG_D_COLOR "\0",
	C_BOLD LOG_I_COLOR "\0",
	C_BOLD LOG_W_COLOR "\0",
	C_BOLD LOG_E_COLOR "\0",
};

#else

/* Log level label */
static const char* p_debug_level_label[] = {
	"<V>\0",
	"<D>\0",
	"<I>\0",
	"<W>\0",
	"<E>\0",
};
#endif /* TOOLS_COLOR_ENABLED */


/* Debug print */
#ifdef TOOLS_PRINT_LEVEL

static const char p_print_format[] =
#ifdef TOOLS_COLOR_ENABLED
    "%s [%s:%d] %s%s" C_DEFAULT C_ENDLINE;
#else
    "%s [%s:%d] %s\n";
#endif

static char p_print_str[TOOLS_DEBUG_BUF_SIZE];

/**
 * @brief Debug print
 *
 * Print message like <V> [file_name.c:123] Verbose message
 *
 * @param lvl       Debug level
 * @param file_name File name (__FILE__)
 * @param line      Line number (__LINE__)
 * @param fmt       Message format
 * @param ...       Other args
 */
void tools_debug_print(int lvl, const char* file_name, int line, const char* fmt, ...) {
    VA_ARG_UNPACK(p_print_str, fmt);

#ifdef TOOLS_COLOR_ENABLED
	printf(p_print_format, p_debug_level_label[lvl], file_name, line, p_message_color[lvl], p_print_str);
#else
	printf(p_print_format, p_debug_level_label[lvl], file_name, line, p_print_str);
#endif
    TOOLS_PRINT_UNLOCK();
}
#endif /* TOOLS_PRINT_LEVEL */


/* Debug Log */
#ifdef TOOLS_LOG_LEVEL
/* Debug log string format */
static const char p_log_format[] =
#ifdef TOOLS_COLOR_ENABLED
    "%s [%s::%s:%d] %s%s" C_DEFAULT C_ENDLINE;
#else
    "%s [%s::%s:%d] %s\n";
#endif

/* Debug log message string buffer */
static char p_log_str[TOOLS_DEBUG_BUF_SIZE];

/**
 * @brief
 *
 * @param lvl
 * @param tag
 * @param func_name
 * @param line
 * @param fmt
 * @param ...
 */
void tools_debug_log(int lvl, const char* tag, const char* func_name, int line, const char* fmt, ...) {
    VA_ARG_UNPACK(p_log_str, fmt);

#ifdef TOOLS_COLOR_ENABLED
	printf(p_log_format, p_debug_level_label[lvl], tag, func_name, line, p_message_color[lvl], p_log_str);
#else
	printf(p_log_format, p_debug_level_label[lvl], tag, func_name, line, p_log_str);
#endif
    TOOLS_PRINT_UNLOCK();
}
#endif /* TOOLS_LOG_LEVEL */


/* Trace Print */
#ifdef TOOLS_TRACE_PRINT_LEVEL

/* Trace format string */
static const char p_trace_print_format[] =
#ifdef TOOLS_COLOR_ENABLED
    "%s %s [%s:%d] %s%s" C_DEFAULT C_ENDLINE;
#else
    "%s %s [%s:%d] %s\n";
#endif

/* Trace message string buffer */
static char p_trace_print_str[TOOLS_DEBUG_BUF_SIZE];

/* Trace time string buffer */
static char p_trace_print_time_str[16];

/**
 * @brief
 *
 * @param lvl
 * @param _tag
 * @param func_name
 * @param file_name
 * @param line
 * @param fmt
 * @param ...
 */
void tools_trace_print(int lvl, const char* file_name, int line, const char* fmt, ...) {
    VA_ARG_UNPACK(p_trace_print_str, fmt);

    tools_string_trace_time(p_trace_print_time_str, tools_time_now_us(), 16);

#ifdef TOOLS_COLOR_ENABLED
	printf(p_trace_print_format, p_trace_print_time_str, p_debug_level_label[lvl],
        file_name, line, p_message_color[lvl], p_trace_print_str);
#else
	printf(p_trace_print_format, p_trace_print_time_str, p_debug_level_label[lvl],
        file_name, line, p_trace_print_str);
#endif
    TOOLS_PRINT_UNLOCK();
}
#endif /* TOOLS_TRACE_PRINT_LEVEL */


/* Trace Log */
#ifdef TOOLS_TRACE_LOG_LEVEL
/* Trace log format string */
static const char p_trace_log_format[] =
#ifdef TOOLS_COLOR_ENABLED
    "%s %s [%s::%s:%d] %s%s" C_DEFAULT C_ENDLINE;
#else
    "%s %s [%s::%s:%d] %s\n";
#endif

/* Trace log message string buffer */
static char p_trace_log_str[TOOLS_DEBUG_BUF_SIZE];

/* Trace log time string buffer */
static char p_trace_log_time_str[16];

/**
 * @brief
 *
 * @param lvl
 * @param _tag
 * @param func_name
 * @param line
 * @param fmt
 * @param ...
 */
void tools_trace_log(int lvl, const char* _tag,
    const char* func_name, int line, const char* fmt, ...) {
    VA_ARG_UNPACK(p_trace_log_str, fmt);
    tools_string_trace_time(p_trace_log_time_str, tools_time_now_us(), 16);

#ifdef TOOLS_COLOR_ENABLED
	printf(p_trace_log_format, p_trace_log_time_str, p_debug_level_label[lvl],
        _tag, func_name, line, p_message_color[lvl], p_trace_log_str);
#else
	printf(p_trace_log_format, p_trace_log_time_str, p_debug_level_label[lvl]
        , _tag, func_name, line, p_trace_log_str);
#endif
    TOOLS_PRINT_UNLOCK();
}
#endif /* TOOLS_TRACE_LOG_LEVEL */


/**
 * @brief Create a tag object
 *
 * @param d_obj
 * @param obj_type
 * @param obj_name
 * @param parent_name
 */
void create_tag(debug_object_t* d_obj, const char* obj_type, const char* obj_name, const char* parent_name) {
    ASSERT_ARG(d_obj)

    print_v("obj_type: %s", obj_type);
    print_v("obj_name: %s", obj_name);
    print_v("parent_name: %s", parent_name);

    if (!obj_type || !strlen(obj_type) ||
        !obj_name || !strlen(obj_name)) {
        print_e("assert failed");
        return;
    }

    if (d_obj->id < 0) {
        static int idx = 0;
        d_obj->id = idx;
        idx++;
    }

    snprintf(d_obj->obj_type_name, DBG_OBJ_STR_SIZE, "%s", obj_type);

    if (parent_name && strlen(parent_name)) {
        snprintf(d_obj->obj_name, DBG_OBJ_STR_SIZE, "%s.%s", parent_name, obj_name);
        snprintf(d_obj->obj_parent, DBG_OBJ_STR_SIZE, "%s", parent_name);
    } else {
        snprintf(d_obj->obj_name, DBG_OBJ_STR_SIZE, "%s", obj_name);
    }

    snprintf(d_obj->tag, DBG_OBJ_STR_SIZE * 4, "(%s)%s", d_obj->obj_type_name, d_obj->obj_name);

    print_v("obj_type_name: %s", d_obj->obj_type_name);
    print_v("obj_parent   : %s", d_obj->obj_parent);
    print_v("obj_name     : %s", d_obj->obj_name);
    print_v("tag          : %s", d_obj->tag);
}

#endif /* TOOLS_DEBUG_ENABLED */
