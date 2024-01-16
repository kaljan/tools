/**
 * @file    tools_demux.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    17.10.2020
 *
 * @brief
 */

#include "tools_demux.h"
#include "tools_assert.h"
#include "tools_misc.h"
#include "tools_print.h"

#ifdef TOOLS_DEMUX_ENABLED

#ifdef TOOLS_DEBUG_ENABLED
#define _tag context->dbg.tag
#else
#define _tag
#endif

void tools_mux_channel_init(mux_channel_t* context, const char* name, const char* parent) {
    ASSERT_ARG(context)
#ifdef TOOLS_DEBUG_ENABLED
    create_tag(&context->dbg, "tools_buffer_t", name, parent);
    demux_log_v(_tag, "buffer initialized");
#endif /* TOOLS_DEBUG_ENABLED */
}

void tools_demux_init(demux_t* context, const char* name, const char* parent) {
    ASSERT_ARG(context)
#ifdef TOOLS_DEBUG_ENABLED
    create_tag(&context->dbg, "tools_buffer_t", name, parent);
    demux_log_v(_tag, "buffer initialized");
#endif /* TOOLS_DEBUG_ENABLED */
}


/**
 * @brief
 *
 * @param ctx
 * @param data
 * @param size
 * @return int
 */
int tools_mux_data(context_t ctx, const void* data, size_t size) {
    ASSERT_OBJECT_RET(mux_channel_t, context, ctx, STATUS_ERROR)

    if (size > context->size) {
        demux_log_e(_tag, "large data; max size: %d; size: %d", context->size, size);
        return STATUS_ERROR;
    } else if (tools_buffer_avail(context->buffer) < (size + sizeof(demux_header_t))) {
        demux_log_e(_tag, "Space available %d; data size: %d", tools_buffer_avail(context->buffer), size);
        return STATUS_SUCCESS;
    }

    demux_header_t hdr;
    hdr.channel = context->channel;
    hdr.size = (uint8_t)(size & 0x000000FFUL);
    demux_log_v(_tag, "write header: channel id: %d; data size: %d", hdr.channel, hdr.size);
    int ret = tools_buffer_write(context->buffer,
        (const uint8_t *)&hdr, sizeof(demux_header_t));
    demux_log_v(_tag, "write header returned: %d", ret);
    if (ret <= 0) {
        demux_log_e(_tag, "Write header failed");
        return STATUS_ERROR;
    } else if (data && size) {
        demux_log_v(_tag, "write data");
        ret = tools_buffer_write(context->buffer, data, size);
        demux_log_v(_tag, "write data returned: %d", ret);
        if (ret < 0) {
            demux_log_e(_tag, "Write data failed");
        }
    } else {
        return STATUS_SUCCESS;
    }

    return ret;
}

/**
 * @brief
 *
 * @param demux
 * @param channel
 * @param data
 * @param size
 * @return int
 */
static int p_tools_demux_data(demux_t * demux,
    uint8_t channel, const void* data, size_t size) {
    if (demux && demux->channel_list &&
        demux->channel_list[channel].recv) {
        demux->channel_list[channel].recv(
            demux->channel_list[channel].arg, data, size);
    }
    return 0;
}

/**
 * @brief Demux data
 *
 * @param ctx   pointer to demux_t context
 * @param data  pointer to data
 * @param size  size of data
 * @return int  return 0, if data not found, -1 if parser failed or
 * number of parsed bytes
 */
int tools_demux_data(context_t ctx, const void* data, size_t size) {
    ASSERT_OBJECT_RET(demux_t, context, ctx, STATUS_ERROR)
    ASSERT_ARG_RET(data, STATUS_ERROR)

    if (size < sizeof(demux_header_t)) {
        demux_log_w(_tag, "Not enough data");
        return 0;
    }

    size_t bytes = 0;

    while (bytes < size - sizeof(demux_header_t)) {
        const demux_header_t * hdr = (const demux_header_t *)(data + bytes);

        if (hdr->channel < context->max_channel &&
            hdr->size < TOOLS_DEMUX_MAX_SIZE) {
            if (hdr->size > size - bytes) {
                break;
            }
            bytes += sizeof(demux_header_t);
            if (hdr->size) {
                p_tools_demux_data(context, hdr->channel,
                    data + bytes, (size_t)hdr->size);
                bytes += hdr->size;
            } else {
                p_tools_demux_data(context, hdr->channel, NULL, 0);
            }
        } else {
            return STATUS_ERROR;
        }
    }
    return 0;
}
#endif /* TOOLS_DEMUX_ENABLED */
