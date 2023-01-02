/**
 * @file    tools_fifo.c
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    Oct 17, 2020
 *
 * @brief
 */

#include "tools_fifo.h"
#ifdef TOOLS_FIFO_ENABLED

/**
 * Append byte to FIFO
 *
 * @param context poniter to FIFO object
 * @param c       Input dat byte
 * @return 0 if success, -1 if failed of buffer full
 */
int tools_fifo_put(tools_fifo_t* context, uint8_t c) {

    if (context && context->data && context->bytes < context->size) {
        context->data[context->head] = c;
        context->head++;
        context->bytes++;
        if (context->head >= context->size) {
            context->head = 0;
        }
        return 0;
    }
    return -1;
}

/**
 * Get byte from FIFO
 *
 * @param context poniter to FIFO object
 * @param c       pointer to destination data byte
 * @return 0 if success, of -1 if failed of buffer is empty
 */
int tools_fifo_get(tools_fifo_t* context, uint8_t* const c) {
    if (context && context->data && (context->bytes > 0) && c) {
        *c = context->data[context->tail];
        context->tail++;
        context->bytes--;
        if (context->tail >= context->size) {
            context->tail = 0;
        }
        return 0;
    }
    return -1;
}
#endif /* TOOLS_FIFO_ENABLED */
