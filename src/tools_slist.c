/**
 * @file    tools_slist.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    02.04.2020
 *
 * @brief
 */

#include "tools_slist.h"

#ifdef TOOLS_SLIST_ENABLED
#ifdef ALLOC_ENABLED
#include <stdlib.h>

slist_t* slist_new(void* object) {
    slist_t* node = (slist_t*)malloc(sizeof(slist_t));
    if (node) {
        node->object = object;
        node->next = NULL;
    }
    return node;
}

void slist_delete(slist_t** node) {
    if ((NULL != node) && (NULL != (*node))) {
        free((void*)(*node));
        *node = NULL;
    }
}
#endif /* ALLOC_ENABLED */

void slist_foreach(slist_t* head,
    slist_iterator_t func, void* arg) {
    if (NULL != func) {
        while (NULL != head) {
            if ((*func)(arg, head) == false) {
                break;
            }
            head = head->next;
        }
    }
}

void slist_for(slist_t* head, slist_t* tail
    , slist_iterator_t func, void* arg) {
    if ((NULL != func) || (NULL != head)) {
        while (head != tail) {
            if ((*func)(arg, head) == false) {
                break;
            }
            head = head->next;
        }
    }
}

slist_t* slist_get_tail(slist_t* head) {
    while (head) {
        if (!head->next) {
            break;
        }
        head = head->next;
    }
    return head;
}

void slist_push_back(slist_t** head, slist_t** tail, slist_t* item) {
    if ((NULL != head) || (NULL != tail) || (NULL != item)) {
        if (NULL == *head) {
            *head = item;
            *tail = item;
            item->next = NULL;
        } else {
            if (NULL != *tail) {
                (*tail)->next = item;
            }
            *tail = item;
        }
    }
}

void slist_push_front(slist_t** head, slist_t** tail, slist_t* item) {
    if ((NULL != head) || (NULL != tail) || (NULL != item)) {
        if (NULL == *head) {
            *head = item;
            *tail = item;
            item->next = NULL;
        } else {
            item->next = *head;
            *head = item;
        }
    }
}

slist_t* slist_pop_back(slist_t** head, slist_t** tail) {
    if ((NULL != head) && (NULL != tail)) {
        if (NULL != (*head)) {
            slist_t* temp = *head;
            slist_t* prev = NULL;
            while (NULL != temp->next) {
                prev = temp;
                temp = temp->next;
            }
            if (NULL != prev) {
                prev->next = NULL;
            } else {
                *head = NULL;
            }
            *tail = prev;
            return temp;
        } else {
            *tail = NULL;
        }
    }
    return NULL;
}

slist_t* slist_pop_front(slist_t** head, slist_t** tail) {
    if (head && tail) {
        if (*head) {
            slist_t* temp = *head;
            *head = (*head)->next;
            temp->next = NULL;
            return temp;
        } else {
            *tail = NULL;
        }
    }
    return NULL;
}

#endif /* TOOLS_SLIST_ENABLED */
