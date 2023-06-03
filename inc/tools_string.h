/**
 * @file    tools_string.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    17.10.2020
 *
 * @brief   String tools
 */
#ifndef TOOLS_STRING_H
#define TOOLS_STRING_H

#include "tools_opt.h"

#ifdef TOOLS_STRING_ENABLED

/* Max string buffer size */
#define TOOLS_STRING_BUF_SIZE_MAX  4096
#define TOOLS_IS_BACKGROUND        0x00000001

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int tools_strhex(char* str, size_t str_size, const uint8_t* data, size_t data_size
    , const char* pref, const char* post, const char* delim);

void tools_string_fmt_time_ms(char* str, uint64_t value);
void tools_string_trace_time(char* str, uint64_t value, uint8_t field_len);

int tools_string_split(char* str, size_t size, char delim,
    int(*clbk)(void*, const char*, size_t), void* arg, int* c_ret);

int tools_string_loader(const char* fname, int(*callback)(void*, int, char*, size_t), void*);

int tools_color_esc(char* buf, size_t buf_size, const color_rgb_t* c, int flags);
int tools_append_str(char* buf, size_t size, const char* fmt, ...);

#ifdef TOOLS_ALLOC_ENABLED
char** tools_split_string(char* buf, size_t size, char delim, size_t* count);
#endif /* TOOLS_ALLOC_ENABLED */

#ifdef ALLOC_ENABLED
char* tools_strdup(const char* str);
#endif /* ALLOC_ENABLED */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_STRING_ENABLED */
#endif /* TOOLS_STRING_H */
