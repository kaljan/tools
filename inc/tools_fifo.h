/**
 * @file    tools_fifo.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    17.11.2020
 *
 * @brief   FIFO (First In First Out)
 */
#ifndef TOOLS_FIFO_H
#define TOOLS_FIFO_H

#include "tools_opt.h"

#ifdef TOOLS_FIFO_ENABLED

/**
 * FIFO (First In First Out) object
 */
typedef struct _tools_fifo_t {
    /** Pointer to data buffer size */
    uint8_t* data;

    /** Size of data buffer */
    uint16_t size;

    /** Bytes in buffer */
    uint16_t bytes;

    /** Start data cursor */
    uint16_t head;

    /** End data cursor */
    uint16_t tail;
} tools_fifo_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
int tools_fifo_put(tools_fifo_t* context, uint8_t c);
int tools_fifo_get(tools_fifo_t* context, uint8_t* const c);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_FIFO_ENABLED */
#endif /* TOOLS_FIFO_H */
