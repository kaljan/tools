/**
 * @file    tools_types.h
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    Dec 26, 2020
 *
 * @brief
 */
#ifndef TOOLS_TYPES_H
#define TOOLS_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef enum {
    STATUS_BUSY = 1,
    STATUS_SUCCESS = 0,
    STATUS_ERROR = -1
} status_t;

typedef union word16 {
    uint16_t data16;
    uint8_t data8[2];
} word16_t;

typedef union word32 {
    uint32_t data32;
    uint16_t data16[2];
    uint8_t data8[4];
} word32_t;

typedef union word64 {
    uint64_t data64;
    uint32_t data32[2];
    uint16_t data16[4];
    uint8_t data8[8];
} word64_t;

typedef struct color_rgb {
    int red;
    int green;
    int blue;
} color_rgb_t;

typedef void* context_t;
typedef void* void_ptr_t;
typedef void* auto_t;

typedef void (*func_t)       (void);
typedef void (*callback_t)   (context_t);
typedef int  (*open_fn_t)    (context_t, const void_ptr_t);
typedef void (*close_fn_t)   (context_t);
typedef int  (*init_fn_t)    (context_t, const auto_t);
typedef void (*deinit_fn_t)  (context_t);
typedef int  (*poll_fn_t)    (context_t);
typedef int  (*write_fn_t)   (context_t, const void*, size_t);
typedef int  (*read_fn_t)    (context_t, void*, size_t);
typedef int  (*transfer_fn_t)(context_t, const void*, size_t, void*, size_t, int const*);
typedef void (*on_failed_t)  (context_t, int);
typedef void (*error_fn_t)   (context_t, int);
typedef bool (*start_fn_t)   (context_t);
typedef int  (*iterator_t)   (auto_t, context_t);

#endif /* TOOLS_TYPES_H */
/* EOF */
