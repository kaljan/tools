/**
 * @file    tools_thread.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    29.04.2023
 *
 * @brief
 */
#include "tools_thread.h"

#ifdef TOOLS_THREAD_ENABLED
#include "tools_assert.h"
#include "tools_misc.h"
#include "tools_print.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>


#define TOOLS_THREAD_TAG_SIZE    32

struct tools_thread {
    bool init_once;
    bool in_progress;
    bool stop_request;
    context_t handle;
    tools_thread_func_t callback;
    pthread_mutex_t mutex;
    pthread_t thread;
};

tools_thread_t* tools_thread_new(void) {
    tools_thread_t* instance = (tools_thread_t*)malloc(sizeof(tools_thread_t));
    if (instance) {
        instance->in_progress = false;
        instance->stop_request = false;
        instance->init_once = false;
        instance->handle = NULL;
        instance->callback = NULL;
        pthread_mutex_init(&instance->mutex, NULL);
    }
    return instance;
}

void tools_thread_delete(tools_thread_t** instance) {
    if ((NULL != instance) && (NULL != *instance)) {
        free((void*)(*instance));
        *instance = NULL;
    }
}

static void* tools_thread_routine(void* ctx) {
    ASSERT_OBJECT_RET(tools_thread_t, context, ctx, ctx)
    ASSERT_ARG_RET(context->callback, ctx);

    pthread_mutex_lock(&context->mutex);
    context->in_progress = true;
    while (true == context->in_progress) {
        if (true == context->stop_request) {
            break;
        }
        pthread_mutex_unlock(&context->mutex);
        if (context->callback(context->handle) == false) {
            pthread_mutex_lock(&context->mutex);
            break;
        }
        pthread_mutex_lock(&context->mutex);
    }
    context->in_progress = false;
    pthread_mutex_unlock(&context->mutex);
    return ctx;
}

int tools_thread_start(tools_thread_t* context,
    tools_thread_func_t callback, context_t arg) {
    ASSERT_ARG_RET(context, -1);
    ASSERT_ARG_RET(callback, -1);

    if (true == context->init_once) {
        return 0;
    }

    context->callback = callback;
    context->handle = arg;

    if (pthread_create(&context->thread, NULL,
        tools_thread_routine, context) != 0) {
        return -1;
    }
    context->init_once = true;
    return 0;
}

void tools_thread_stop(tools_thread_t* context) {
    ASSERT_ARG(context)
    if (false == context->init_once) {
        return;
    }

    pthread_mutex_lock(&context->mutex);
    if (true == context->in_progress) {
        context->stop_request = true;
        while(true == context->in_progress) {
            pthread_mutex_unlock(&context->mutex);
            usleep(10000);
            pthread_mutex_lock(&context->mutex);
        }
    }
    pthread_mutex_unlock(&context->mutex);
    pthread_join(context->thread, NULL);
    context->stop_request = false;
    context->init_once = false;
}

#endif /* TOOLS_THREAD_ENABLED */
