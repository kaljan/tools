/**
 * @file    tools_demux.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    17.11.2020
 *
 * @brief
 */
#ifndef TOOLS_DEMUX_H
#define TOOLS_DEMUX_H

#include "tools_opt.h"

#ifdef TOOLS_DEMUX_ENABLED

#ifdef TOOLS_DEBUG_ENABLED
#include "debug/dbg_demux.h"
#endif /* TOOLS_DEBUG_ENABLED */

#include "tools_buffer.h"

#define TOOLS_DEMUX_MAX_SIZE    1024

/* Base demux type */
typedef uint16_t demux_base_t;

#pragma pack(push, 1)

/* Demux paket header */
typedef struct demux_header {

    /* Channel ID */
    demux_base_t channel;

    /* Demux paket size (bytes) */
    demux_base_t size;
} demux_header_t;

#pragma pack(pop)

/* Multiplexor channel */
typedef struct mux_channel {
#ifdef TOOLS_DEBUG_ENABLED
    /* Debug object */
    debug_object_t dbg;
#endif /* TOOLS_DEBUG_ENABLED */
    /* Channel ID */
    demux_base_t channel;

    /* Max paket size */
    demux_base_t size;

    /* Pointer to buffer for mux data */
    tools_buffer_t* buffer;
} mux_channel_t;

/* Demux channel */
typedef struct demux_channel {

    /* Data receiver funcion pointer*/
    write_fn_t recv;

    /* Data received object pointer */
    context_t arg;
} demux_channel_t;

/* Demux */
typedef struct tools_demux {
#ifdef TOOLS_DEBUG_ENABLED
    /* Debug object */
    debug_object_t dbg;
#endif /* TOOLS_DEBUG_ENABLED */
    /* Demux channel list */
    demux_channel_t* channel_list;

    /* Channel list size  */
    demux_base_t max_channel;
} demux_t;

void tools_mux_channel_init(mux_channel_t* context, const char* name, const char* parent);
void tools_demux_init(demux_t* context, const char* name, const char* parent);
int tools_mux_data(context_t ctx, const void* data, size_t size);
int tools_demux_data(context_t ctx, const void* data, size_t size);

#endif /* TOOLS_DEMUX_ENABLED */
#endif /* TOOLS_DEMUX_H */
