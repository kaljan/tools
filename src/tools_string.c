/**
 * @file 	tools_string.c
 * @author	Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version	1.0.0
 * @date	Oct 17, 2020
 *
 * @brief   String tools
 */
#include "tools_string.h"
#ifdef TOOLS_STRING_ENABLED

#include "tools_assert.h"
#include "tools_debug.h"
#include "tools_misc.h"
#include "tools_print.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define TOOLS_STRING_ASSERT(__str) \
    if (!__str || !strlen(__str)) { \
        return; \
    }

#define TOOLS_STRING_ASSERT_ARG_RET(__str, __retval) \
    if (!__str || !strlen(__str)) { \
        return __retval; \
    }

#define TOOLS_STRING_ASSERT_N(__str, __len) \
    if (!__str || !strlen(__str) || strlen(__str) > __len) { \
        return; \
    }

int tools_strhex(char* str, size_t str_size, const uint8_t* data, size_t data_size
    , const char* pref, const char* post, const char* delim) {
    int ret = -1;
    size_t cursor = 0;

    ASSERT_ARG_RET(str, ret)
    ASSERT_ARG_RET(str_size, ret)
    ASSERT_ARG_RET(data, ret)
    ASSERT_ARG_RET(data_size, ret)

    if (!pref) {
        pref = "";
    }

    if (!post) {
        post = "";
    }

    if (!delim) {
        delim = "";
    }

    for (size_t i = 0; i < data_size; i++) {
        if (str_size < cursor) {
            ret = i;
            break;
        }

        if (i < data_size - 1) {
            ret = snprintf(&str[cursor], str_size - cursor, "%s%02X%s%s", data[i], pref, post, delim);
        } else {
            ret = snprintf(&str[cursor], str_size - cursor, "%s%02X%s", data[i], pref, post);
        }
        if (ret <= 0) {
            break;
        }
        cursor += ret;
    }

    return ret;
}

/**
 * @param str
 * @param value
 */
void tools_string_fmt_time_ms(char* str, uint64_t value) {
    static const uint32_t TEMP_MAX = 64;
    char temp[TEMP_MAX];

    sprintf(temp, "%lu", value);
    size_t l = strlen(temp);
    char* ptr = temp;

    while (*ptr) {
        --l;
        *str = *ptr;
        ptr++;
        str++;
        if (l == 3) {
            *str = '.';
            str++;
        } else if ((l != 0) && (l % 3) == 0) {
            *str = '\'';
            str++;
        }
    }
    *str = 0;
}

/**
 * @param str
 * @param value
 * @param field_len
 */
void tools_string_trace_time(char* str, uint64_t value, uint8_t field_len) {
    static const uint32_t TEMP_MAX = 64;
    char temp[TEMP_MAX];

    tools_string_fmt_time_ms(temp, value);
    size_t l = strlen(temp);
    if (l > field_len) {
        return;
    }

    if (l < field_len) {
        str[0] = '<';
        memset(&str[1], '-', field_len - l - 2);
        str[field_len - l - 1] = ' ';
    }

    strncpy(&str[field_len - l], temp, l);
    str[field_len] = 0;
}

const char * tools_string_get_elapsed_us(
	uint64_t t_start, uint64_t t_stop) {
	static char str[24];
	sprintf(str, "%lu us", t_stop - t_start);
	return str;
}

const char * tools_string_get_elapsed_ms(
	uint64_t t_start_us, uint64_t t_stop_us) {
	static char str[24];
	sprintf(str, "%8.3f ms", ((double)(t_stop_us - t_start_us)) / 1000.0);
	return str;
}

/**
 * @brief
 *
 * @param str
 * @param size
 * @param delim
 * @param clbk
 * @param arg
 * @param c_ret
 * @return int
 */
int tools_string_split(char* str, size_t size, char delim,
    int(*clbk)(void*, const char*, size_t), void* arg, int* c_ret) {
    int ret = -1;
    TOOLS_STRING_ASSERT_ARG_RET(str, ret) else
    ASSERT_ARG_RET(clbk, ret) else
    ASSERT_ARG_RET(delim, ret)

    char* str_end = str + strlen(str);
    char* ptr = strchr(str, delim);

    while (ptr) {
        if (ptr < str) {
            ret = -1;
            break;
        }

        size_t s = ptr - str;
        *ptr = 0;

        ret = clbk(arg, str, s);
        if (ret) {
            *c_ret = ret;
            return -1;
        }

        str = ptr + 1;
        ptr = strchr(str, delim);
    }

    if (str < str_end) {
        print_d("%d", str_end - str);
        *c_ret = clbk(arg, str, str_end - str);
    }
    return ret;
}

/**
 * @brief
 *
 * @param fname
 * @param callback
 * @return int
 */
int tools_string_loader(const char* f_name, int(*callback)(void*, int, char*, size_t), void* arg) {
    int ret = -1;
    ASSERT_ARG_RET(f_name, ret) else
    ASSERT_ARG_RET(callback, ret)

    FILE* f_des = fopen(f_name, "r");
    if (f_des) {
        char buf[TOOLS_STRING_BUF_SIZE_MAX];
        ret = 0;
        int line_index = 0;
        while(!feof(f_des)) {
            if (!fgets(buf, TOOLS_STRING_BUF_SIZE_MAX, f_des)) {
                break;
            }
            ret = callback(arg, line_index++, buf, strlen(buf));
            if (ret < 0) {
                break;
            }
        }

    } else {
        print_e("failed to open file \"%s\"", f_name);
    }

    return ret;
}

int tools_color_esc(char* buf, size_t buf_size, const color_rgb_t* c, int flags) {
    int ret = -1;
    ASSERT_STRING_RET(buf, ret)
    ASSERT_ARG_RET(c, ret)

    ret = snprintf(buf, buf_size, "\e[%d;2;%d;%d;%dm"
        , 38 + (flags & TOOLS_IS_BACKGROUND)  ? 10 : 0
        , c->red, c->green, c->blue);

    return ret;
}

#endif /* TOOLS_STRING_ENABLED */
