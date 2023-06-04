/**
 * @file    tools_slist.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    02.04.2020
 *
 * @brief
 */
#ifndef TOOLS_SLIST_H
#define TOOLS_SLIST_H

#include "tools_opt.h"

#ifdef TOOLS_SLIST_ENABLED

typedef struct slist {
    void* object;
    struct slist* next;
} slist_t;

typedef bool (*slist_iterator_t)(void*, slist_t*);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef ALLOC_ENABLED
slist_t* slist_new(void* object);
void slist_delete(slist_t** node);
#endif /* ALLOC_ENABLED */

void slist_foreach(slist_t* head, slist_iterator_t func, void* arg);
void slist_for(slist_t* head, slist_t* tail, slist_iterator_t func, void* arg);
slist_t* slist_get_tail(slist_t* head);
void slist_push_back(slist_t** head, slist_t** tail, slist_t* item);
void slist_push_front(slist_t** head, slist_t** tail, slist_t* item);
slist_t* slist_pop_back(slist_t** head, slist_t** tail);
slist_t* slist_pop_front(slist_t** head, slist_t** tail);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_SLIST_ENABLED */
#endif /* TOOLS_SLIST_H */
