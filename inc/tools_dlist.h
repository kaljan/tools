/**
 * @file    tools_dlist.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    02.04.2020
 *
 * @brief
 */
#ifndef TOOLS_DLIST_H
#define TOOLS_DLIST_H

#include "tools_opt.h"

#ifdef TOOLS_DLIST_ENABLED

typedef struct dlist {
    /* Node object owner pointer */
    void* object;

    /* Prev node in list */
    struct dlist* prev;

    /* Next node in list */
    struct dlist* next;
} dlist_t;

typedef bool(*dlist_iterator_t)(void*,dlist_t*);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef ALLOC_ENABLED
dlist_t* tools_dlist_new(void* object);
void tools_dlist_delete(dlist_t** node);
#endif /* ALLOC_ENABLED */

void tools_dlist_foreach(dlist_t* head, dlist_iterator_t callback, void* arg);
void tools_dlist_for(dlist_t* head, dlist_t* tail, dlist_iterator_t callback, void* arg);
void tools_dlist_push_back(dlist_t** head, dlist_t** tail, dlist_t* item);
dlist_t* tools_dlist_pop_back(dlist_t** head, dlist_t** tail);
void tools_dlist_push_front(dlist_t** head, dlist_t** tail, dlist_t* item);
dlist_t* tools_dlist_pop_front(dlist_t** head, dlist_t** tail);
void tools_dlist_insert(dlist_t** head, dlist_t** tail, dlist_t* after, dlist_t * item);
void tools_dlist_remove(dlist_t** head, dlist_t** tail, dlist_t* item);
void tools_dlist_clear(dlist_t** head, dlist_t** tail);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_DLIST_ENABLED */
#endif /* TOOLS_DLIST_H */
