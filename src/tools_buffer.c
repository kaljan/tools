/**
 * @file    tools_buffer.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    04.09.2020
 *
 * @brief
 */
#include "tools_buffer.h"

#ifdef TOOLS_BUFFER_ENABLED

#include "tools_assert.h"
#include "tools_print.h"
#include "tools_misc.h"

#define BUF_ASSERT(b) \
    if (!b || !b->data || !b->size) { \
        buf_print_e("assertion failed"); \
        return; \
    }

#define BUF_ASSERT_RET(b, r) \
    if (!b || !b->data || !b->size) { \
        buf_print_e("assertion failed"); \
        return r; \
    }

#ifdef TOOLS_DEBUG_ENABLED
#define _tag context->dbg.tag
#else
#define _tag
#endif

void tools_buffer_init(tools_buffer_t* context, uint8_t* data,
    size_t size, tools_buffer_t* next, const char* name, const char* parent) {
    ASSERT_ARG(context)
    else ASSERT_ARG(data)
    else ASSERT_ARG(size)

    context->data = data;
    context->size = size;
    context->bytes = 0;
    context->next = next;
#ifdef TOOLS_DEBUG_ENABLED
    create_tag(&context->dbg, "tools_buffer_t", name, parent);
    buf_log_v(_tag, "buffer initialized");
#endif /* TOOLS_DEBUG_ENABLED */
}

/**
 * Clear buffer
 *
 * @param context pointer to buffer instance
 */
void tools_buffer_flush(tools_buffer_t* context) {
    BUF_ASSERT(context)
    memset(context->data, 0, context->size);
    buf_log_v(_tag, "skip %llu bytes", context->bytes);
    context->bytes = 0;
}

/**
 * @brief Remove data from buffer
 *
 * Remove data from start of buffer to bytes.
 *
 * @param context pointer to buffer instance
 * @param bytes bytes to remove
 * @return size_t bytes left in buffer
 */
size_t tools_buffer_remove(tools_buffer_t* context, size_t bytes) {
    size_t ret = 0;

    BUF_ASSERT_RET(context, STATUS_ERROR)
    else if (context->bytes > bytes) {
        buf_log_v(_tag, "skip %llu bytes", bytes);
        context->bytes -= bytes;
        memmove(context->data, context->data + bytes, context->bytes);
        buf_log_v(_tag, "bytes left %llu", context->bytes);
        ret = context->bytes;
    } else {
        buf_log_v(_tag, "skip %llu bytes", context->bytes);
        context->bytes = 0;
    }

    return ret;
}

/**
 * Write data to buffer
 *
 * @param context   pointer to buffer instance
 * @param data  pointer to data
 * @param size  size of data
 *
 * @return bytes written to buffer of -1 if fail. or 0 when buffer is
 *         full.
 */
int tools_buffer_write(context_t ctx,
    const void* data, size_t size) {
    GET_OBJECT(tools_buffer_t, context, ctx);
    BUF_ASSERT_RET(context, STATUS_ERROR)
    else if (!size) {
        buf_log_v(_tag, "input data size = 0");
        return 0;
    } else if (size > context->size - context->bytes) {
        size = context->size - context->bytes;
        buf_log_v(_tag, "trunkate data size to %llu", size);
    }

    memmove(context->data + context->bytes, data, size);
    context->bytes += size;
    buf_log_v(_tag, "bytes in buffer: %llu; bytes written: %llu"
        , context->bytes, context->size);
    return size;
}

/**
 * Read data from buffer.
 *
 * @param context   pointer to buffer instance
 * @param data  pointer to data
 * @param size  size of data
 *
 * @return Bytes were read. -1 if fails. 0 if buffer empty
 */
int tools_buffer_read(context_t ctx,
    void* data, size_t size) {
    GET_OBJECT(tools_buffer_t, context, ctx);
    BUF_ASSERT_RET(context, STATUS_ERROR)
    else if (!context->bytes) {
        buf_log_d(_tag, "Buffer empty");
        return STATUS_SUCCESS;
    }

    buf_log_v(_tag, "bytes requested: %llu; bytes read: %llu", size, context->bytes);
    if (size > context->bytes) {
        size = context->bytes;
    }

    memmove(data, context->data, size);
    context->bytes -= size;

    if (context->bytes) {
        memmove(context->data, (context->data + size), context->bytes);
    }

    buf_log_v(_tag, "bytes read: %llu; bytes left: %llu", size, context->bytes);
    return (int)size;
}

/**
 * Available bytes in buffer context
 * @param context pointer to buffer instance
 * @return Bytes in buffer
 */
size_t tools_buffer_avail(tools_buffer_t* context) {
    return (context && context->bytes < context->size) ?
        context->size - context->bytes : 0;
}

/**
 * Download data in buffer.
 *
 * if donwloader.callback has pointer to read function from
 * some port of other buffer. this function reads data from this port
 * or buffer to buffer #context
 *
 * @param context pointer to buffer instance
 * @return Uploaded bytes or -1 if fails
 */
int tools_buffer_download(tools_buffer_t* context, read_fn_t downloader, context_t ctx) {
    BUF_ASSERT_RET(context, TOOLS_FAILED)
    ASSERT_ARG_RET(downloader, TOOLS_FAILED)
    if (context->bytes < context->size) {
        buf_log_v(_tag, "download data");
        int ret = downloader(ctx, context->data + context->bytes, context->size - context->bytes);
        buf_log_v(_tag, "download data returned: %d", ret);
        if (ret > 0) {
            context->bytes += ret;
            buf_log_d(_tag, "Bytes in buffer: %llu", context->bytes);
        } else if (ret < 0) {
            buf_log_e(_tag, "uploader returned error status");
        }
        return ret;
    }
    return STATUS_SUCCESS;
}

/**
 * Upload all data from buffer
 *
 * if uploader.callback has pointer to data receiver function,
 * upload all data from #context to to this pointer
 *
 * @param context pointer to buffer instance
 * @return Uploaded bytes of -1 if fails
 */
int tools_buffer_upload(tools_buffer_t* context, write_fn_t uploader, context_t ctx) {
    BUF_ASSERT_RET(context, TOOLS_FAILED)
    ASSERT_ARG_RET(uploader, TOOLS_FAILED)
    if (context->bytes > context->size) {
        print_w("context->bytes > context->size");
    }
    if (context->bytes > 0) {
        buf_log_v(_tag, "upload data");
        int ret = uploader(ctx, context->data, context->bytes);
        buf_log_v(_tag, "upload data returned: %d", ret);
        if (ret > 0) {
            buf_log_d(_tag, "Bytes in sent: %d", ret);
            if (ret <= context->bytes) {
                context->bytes -= ret;
                if (context->bytes > 0) {
                    memmove(context->data, (context->data + ret), context->bytes);
                }
            } else {
                context->bytes = 0;
            }
        } else if (ret < 0) {
            buf_log_e(_tag, "uploader returned error status");
        }
        return ret;
    }
    return 0;
}

/**
 * iterates data in buffer #context
 *
 * @param context  pointer to buffer instance
 * @return Handeled bytes of -1 if fails
 */
int tools_buffer_iterator(tools_buffer_t* context, write_fn_t clbk, context_t ctx) {
    BUF_ASSERT_RET(context, TOOLS_FAILED)
    ASSERT_ARG_RET(clbk, TOOLS_FAILED)

    size_t bytes = 0;
    int ret = 0;

    buf_log_v(_tag, "bytes in buffer: %llu", context->bytes);

    while (bytes < context->bytes) {
        buf_log_v(_tag, "bytes: %llu", bytes);

        ret = clbk(ctx, context->data + bytes, context->bytes - bytes);
        buf_log_v(_tag, "callback returned: %d", ret);

        if (ret > 0) {
            bytes += ret;
            continue;
        } else if (ret < 0) {
            buf_log_e(_tag, "uploader returned error status");
        }
        break;
    }

    if (!bytes) {
        return 0;
    } else if (context->bytes > bytes) {
        buf_log_v(_tag, "bytes handeled: %d; bytes in buffer: %d", bytes, context->bytes);
        context->bytes -= bytes;
        memmove(context->data, (context->data + bytes), context->bytes);
        buf_log_v(_tag, "bytes in buffer: %d", context->bytes);
    } else {
        buf_log_v(_tag, "all data handeled");
        context->bytes = 0;
    }
    ret = bytes;
    return ret;
}

void tools_buffer_cleanup(tools_buffer_t* context) {
    BUF_ASSERT(context)
    if (context->bytes < context->size) {
        memset(&context->data[context->bytes], 0, context->size - context->bytes);
    }
}

#endif /* TOOLS_BUFFER_ENABLED */
