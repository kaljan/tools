/**
 * @file    tools_timer.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    05.09.2020
 *
 * @brief
 */

#include "tools_timer.h"

#ifdef TOOLS_TIMER_ENABLED
#include "tools_time.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define TIMER_ASSERT(b) \
    if (!b) { \
        timer_print_e("assertion failed"); \
        return; \
    }

#define TIMER_ASSERT_ARG_RET(b, r) \
    if (!b) { \
        timer_print_e("assertion failed"); \
        return r; \
    }

#define soft_timer_get_time() tools_time_now_us()

#ifdef TOOLS_DEBUG_ENABLED
#define _tag context->dbg.tag
#else
#define _tag
#endif

void tools_timer_init(tools_timer_t* context, const char* name, const char* parent) {
    TIMER_ASSERT(context)
    memset(context, 0, sizeof(tools_timer_t));

#ifdef TOOLS_DEBUG_ENABLED
    create_tag(&context->dbg, "tools_timer_t", name, parent);
    timer_log_v(_tag, "timer initialized");
#endif /* TOOLS_DEBUG_ENABLED */
}

void tools_timer_run(tools_timer_t * context, uint64_t timeout) {
    TIMER_ASSERT(context)
    context->timeout = timeout;
    context->start_time = soft_timer_get_time();
}

void tools_timer_abort(tools_timer_t * context) {
    TIMER_ASSERT(context)
    context->timeout = 0;
}

void tools_timer_reset(tools_timer_t * context) {
    TIMER_ASSERT(context)
    print_d("%lu", context->timeout);
    if (context->timeout) {
        context->start_time = soft_timer_get_time();
    } else {
        timer_print_w("timer is not run");
    }
}

bool tools_timer_update(tools_timer_t * context) {
    TIMER_ASSERT_ARG_RET(context, false)
    if (context->timeout && context->start_time) {
        if (soft_timer_get_time() - context->start_time > context->timeout) {
            if (context->continous) {
                timer_print_v(_tag, "update timer");
                context->start_time = soft_timer_get_time();
            } else {
                timer_print_v(_tag, "timeout event");
                context->timeout = 0;
            }

            if (context->callback) {
                timer_print_v(_tag, "handler start");
                context->callback(context->parent);
                timer_print_v(_tag, "handler finish");
            }
            return true;
        }
    } else {
        //timer_print_w(_tag, "timer is not run");
    }
    return false;
}

#endif /* TOOLS_TIMER_ENABLED */
