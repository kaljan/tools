/**
 * @file    tools_timer.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    05.09.2020
 *
 * @brief
 */
#ifndef TOOLS_TIMER_H
#define TOOLS_TIMER_H

#include "tools_opt.h"

#ifdef TOOLS_TIMER_ENABLED

#ifdef TOOLS_DEBUG_ENABLED
#include "debug/dbg_timer.h"
#endif /* TOOLS_DEBUG_ENABLED */

typedef struct _tools_timer_t {
    /* Debug object field*/
    DEBUG_OBJECT

    bool continous;
    uint64_t timeout;
    uint64_t start_time;
    callback_t callback;
    context_t parent;
} tools_timer_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void tools_timer_init(tools_timer_t* context, const char* name, const char* parent);
void tools_timer_run(tools_timer_t* context, uint64_t timeout);
void tools_timer_abort(tools_timer_t* context);
void tools_timer_reset(tools_timer_t* context);
bool tools_timer_update(tools_timer_t* context);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_TIMER_ENABLED */
#endif /* TOOLS_TIMER_H */
/* EOF */
