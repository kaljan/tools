/**
 * @file    tools_buffer.h
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    Sep 4, 2020
 *
 * @brief
 */
#ifndef TOOLS_BUFFER_H
#define TOOLS_BUFFER_H

#include "tools_opt.h"

#ifdef TOOLS_BUFFER_ENABLED

#ifdef TOOLS_DEBUG_ENABLED
#include "debug/dbg_buffer.h"
#endif /* TOOLS_DEBUG_ENABLED */

typedef struct tools_buffer {
	/** Debug object field*/
	DEBUG_OBJECT

	/** Pointer to data buffer */
	uint8_t* data;

	/** Size of data buffer */
	size_t size;

	/** Bytes in buffer */
	size_t bytes;

	/** Next buffer item, for double buffer mode */
	struct tools_buffer * next;
} tools_buffer_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void tools_buffer_init(tools_buffer_t* context, uint8_t* data,
	size_t size, tools_buffer_t* next, const char* name, const char* parent);
void tools_buffer_flush(tools_buffer_t* buf);
size_t tools_buffer_remove(tools_buffer_t* buf, size_t bytes);
int tools_buffer_write(context_t ctx, const void * data, size_t size);
int tools_buffer_read(context_t ctx, void * data, size_t size);
size_t tools_buffer_avail(tools_buffer_t* context);

int tools_buffer_download(tools_buffer_t* buf, read_fn_t downloader, context_t ctx);
int tools_buffer_upload(tools_buffer_t* buf, write_fn_t uploader, context_t ctx);
int tools_buffer_iterator(tools_buffer_t* buf, write_fn_t uploader, context_t ctx);
void tools_buffer_cleanup(tools_buffer_t* context);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_BUFFER_ENABLED */
#endif /* TOOLS_BUFFER_H */
/* EOF */
