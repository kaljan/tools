/**
 * @file    tools_dlist.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    02.04.2020
 *
 * @brief
 */
#include "tools_dlist.h"

#ifdef TOOLS_DLIST_ENABLED
#ifdef ALLOC_ENABLED
#include <stdlib.h>

dlist_t* tools_dlist_new(void* object) {
    dlist_t* node = (dlist_t*)malloc(sizeof(dlist_t));
    if (node) {
        node->object = object;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

void tools_dlist_delete(dlist_t** node) {
    if ((NULL != node) && (NULL != (*node))) {
        free((void*)(*node));
        *node = NULL;
    }
}
#endif /* ALLOC_ENABLED */

void tools_dlist_foreach(dlist_t* head, dlist_iterator_t callback, void* arg) {
    if (NULL != callback) {
        while (NULL != head) {
            if (callback(arg, head) == false) {
                break;
            }
            head = head->next;
        }
    }
}

void tools_dlist_for(dlist_t* head, dlist_t* tail,
    dlist_iterator_t callback, void* arg) {
    if ((NULL != callback) || (NULL != head)) {
        while (head != tail) {
            if (callback(arg, head) == false) {
                break;
            }
            head = head->next;
        }
    }
}

void tools_dlist_push_back(dlist_t** head, dlist_t** tail, dlist_t* item) {
    if ((NULL != head) || (NULL != tail) || (NULL != item)) {
        if (NULL == (*head)) {
            *head = item;
            *tail = item;
            item->prev = NULL;
            item->next = NULL;
        } else {
            if (NULL == *tail) {
                *tail = *head;
            }
            (*tail)->next = item;
            item->prev = *tail;
            item->next = NULL;
            *tail = item;
        }
    }
}

dlist_t* tools_dlist_pop_back(dlist_t** head, dlist_t** tail) {
    if ((NULL != head) || (NULL != tail)) {
        if (NULL != *tail) {
            dlist_t* temp = *tail;
            if (NULL != (*tail)->prev) {
                *tail = (*tail)->prev;
                (*tail)->next = NULL;
                temp->next = NULL;
                temp->prev = NULL;
            } else {
                *tail = NULL;
                *head = NULL;
            }
            return temp;
        }
    }
    return NULL;
}

void tools_dlist_push_front(dlist_t** head, dlist_t** tail, dlist_t* item) {
    if ((NULL != head) || (NULL != tail) || (NULL != item)) {
        if (NULL == (*tail)) {
            *head = item;
            *tail = item;
            item->prev = NULL;
            item->next = NULL;
        } else {
            if (NULL == *head) {
                *head = *tail;
            }
            (*head)->prev = item;
            item->next = *tail;
            item->prev = NULL;
            *head = item;
        }
    }
}

dlist_t* tools_dlist_pop_front(dlist_t** head, dlist_t** tail) {
    if ((NULL != head) || (NULL != tail)) {
        if (NULL != *head) {
            dlist_t* temp = *head;
            if (NULL != (*head)->next) {
                *head = (*head)->next;
                (*head)->prev = NULL;
                temp->next = NULL;
                temp->prev = NULL;
            } else {
                *tail = NULL;
                *head = NULL;
            }
            return temp;
        }
    }
    return NULL;
}

void tools_dlist_insert(dlist_t** head, dlist_t** tail,
    dlist_t* after, dlist_t * item) {
    if ((NULL != head) || (NULL != tail) ||
        (NULL != after) || (NULL != item)) {
        item->prev = after;
        item->next = after->next;
        after->next = item;
        if (NULL == item->next) {
            *tail = item;
        } else {
            item->next->prev = item;
        }
    }
}

void tools_dlist_remove(dlist_t** head, dlist_t** tail, dlist_t* item) {
    if ((NULL != head) || (NULL != tail) || (NULL != item)) {
        if (NULL == item->next) {
            tools_dlist_pop_back(head, tail);
        } else if (NULL == item->prev) {
            tools_dlist_pop_front(head, tail);
        } else {
            item->next = item->next->prev;
            item->prev = item->next->prev;
        }
    }
}

void tools_dlist_clear(dlist_t** head, dlist_t** tail) {
    if (NULL != head && NULL != tail) {
        dlist_t* curr = *head;
        *head = NULL;
        *tail = NULL;
        while (curr) {
            dlist_t* temp = curr;
            curr = curr->next;
            temp->prev = NULL;
            temp->next = NULL;
        }
    }
}

#endif /* TOOLS_DLIST_ENABLED */
