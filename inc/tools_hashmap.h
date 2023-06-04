/**
 * @file    tools_hashmap.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    05.05.2023
 *
 * @brief
 */
#ifndef TOOLS_HASHMAP_H
#define TOOLS_HASHMAP_H

#include "tools_opt.h"

#ifdef TOOLS_HASHMAP_ENABLED

struct hashmap;
typedef struct hashmap hashmap_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

hashmap_t* tools_hashmap_new(size_t size);
void tools_hashmap_delete(hashmap_t** map);
int tools_hashmap_put(hashmap_t* map, const char* key, void* value);
void* tools_hashmap_get(hashmap_t* map, const char* key);
void tools_hashmap_remove(hashmap_t* map, const char* key);
void tools_hashmap_clear(hashmap_t* map);
void tools_hashmap_print(hashmap_t* map);
size_t tools_hashmap_count(hashmap_t* map);
size_t tools_hashmap_size(hashmap_t* map);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_HASHMAP_ENABLED */
#endif /* TOOLS_HASHMAP_H */
/* EOF */
