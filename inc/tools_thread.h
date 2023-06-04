/**
 * @file    tools_thread.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    29.04.2023
 *
 * @brief
 */
#ifndef TOOLS_THREAD_H
#define TOOLS_THREAD_H

#include "tools_opt.h"

#ifdef TOOLS_THREAD_ENABLED

typedef bool (*tools_thread_func_t)(context_t);

struct tools_thread;
typedef struct tools_thread tools_thread_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

tools_thread_t* tools_thread_new(void);
void tools_thread_delete(tools_thread_t** instance);
int tools_thread_start(tools_thread_t* context,
    tools_thread_func_t callback, context_t arg);
void tools_thread_stop(tools_thread_t* context);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_THREAD_ENABLED */
#endif /* TOOLS_THREAD_H */
/* EOF */
