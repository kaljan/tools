/**
 * @file    tools_hashmap.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    05.05.2023
 *
 * @brief
 */
#include "tools_hashmap.h"

#ifdef TOOLS_HASHMAP_ENABLED

#include "tools_hashmap.h"
#include "tools_dlist.h"
#include "tools_string.h"

#ifndef TOOLS_ALLOC_ENABLED
#error "Memory allocation disabled"
#endif /* TOOLS_ALLOC_ENABLED */

#ifndef TOOLS_DLIST_ENABLED
#error "Double linked list (dlist_t) disabled"
#endif /* TOOLS_DLIST_ENABLED */


/**
 * Hash map node
 */
typedef struct hash_node {
    /* Pointer to key string */
    char* key;

    /* Poniter to value or object */
    void* value;
} hash_node_t;

/**
 * Hash map bucket
 *
 * TODO move to tools_dlist
 */
typedef struct hash_bucket {
    /* Poniter head of bucket */
    dlist_t* head;

    /* Poniter to tail of bucket */
    dlist_t* tail;
} hash_bucket_t;

/**
 * Hash map
 */
struct hashmap {
    /* Poniter to array of hash map bucket */
    hash_bucket_t* list;

    /* Count of bucket elements in list */
    size_t size;

    /* Count of elements in hashmap */
    size_t count;
};


/**
 * Create new hash map node
 *
 * @param key poniter hash node key string
 * @param value poniter to value
 * @return hash_node_t* NULL if allocate failed. Poniter to allocated
 *         node if success
 */
static hash_node_t* tools_hash_node_new(const char* key, void* value) {
    hash_node_t* node = NULL;
    if ((NULL != key) && (strlen(key) > 0)) {
        size_t area_size = sizeof(hash_node_t) + strlen(key) + 1;
        void* area = malloc(area_size);
        if (NULL != area) {
            memset(area, 0, area_size);
            node = (hash_node_t*)area;
            node->key = (char*)(area + sizeof(hash_node_t));
            node->value = value;
            memmove(node->key, key, strlen(key));
        }
    }
    return node;
}

/**
 * Free memory allocated for hash node. And set poniter to
 * hash node to NULL
 *
 * @param node poniter to poniter to hash node
 */
static void tools_hash_node_delete(hash_node_t** node) {
    if ((NULL != node) && (NULL != (*node))) {
        free((void*)(*node));
        *node = NULL;
    }
}

/**
 *
 *
 * @param key
 * @param value
 * @return dlist_t*
 */
static dlist_t* tools_hash_bucket_new(const char* key, void* value) {
    dlist_t* node = NULL;
    hash_node_t* hdata = tools_hash_node_new(key, value);
    if (NULL != hdata) {
        node = tools_dlist_new(hdata);
        if (NULL == node) {
            tools_hash_node_delete(&hdata);
        }
    }
    return node;
}

/**
 * @brief
 *
 * @param node
 */
static void tools_hash_bucket_delete(dlist_t** node) {
    if ((NULL != node) || (NULL != *node)) {
        tools_hash_node_delete((hash_node_t**)(&(*node)->object));
        tools_dlist_delete(node);
    }
}

/**
 * @brief
 *
 * @param key
 * @param map_size
 * @return int
 */
static int tools_hash_func(const char* key, size_t map_size) {
    int ret = -1;
    if ((NULL != key && (strlen(key) > 0))) {
        size_t temp = 0;
        while (*key != 0) {
            temp += *key;
            key++;
        }
        temp = temp % map_size;
        ret = temp;
    }
    return ret;
}

/**
 * @brief
 *
 * @param map
 * @param key
 * @return int
 */
static int tools_get_hash_key(hashmap_t* map, const char* key) {
    int hash_value = -1;
    if (NULL != map) {
        hash_value = tools_hash_func(key, map->size);
        if (hash_value > map->size) {
            hash_value = -1;
        }
    }
    return hash_value;
}


/**
 * @brief
 *
 * @param size
 * @return hashmap_t*
 */
hashmap_t* tools_hashmap_new(size_t size) {
    size_t area_size = sizeof(hashmap_t) + (sizeof(hash_bucket_t) * size);
    void* area = malloc(area_size);
    if (NULL != area) {
        hashmap_t* map = (hashmap_t*)area;
        memset(area, 0, area_size);
        map->size = size;
        map->list = (hash_bucket_t*)(area + sizeof(hashmap_t));
    }
    return (hashmap_t*)area;
}

/**
 * @brief
 *
 * @param map
 */
void tools_hashmap_delete(hashmap_t** map) {
    if ((NULL != map) && (NULL != (*map))) {
        free((void*)(*map));
        *map = NULL;
    }
}

/**
 * @brief
 *
 * @param map
 * @param key
 * @param value
 * @return int
 */
int tools_hashmap_put(hashmap_t* map, const char* key, void* value) {
    int hash_value = tools_get_hash_key(map, key);
    if (hash_value < 0) {
        return -1;
    }

    dlist_t* curr = map->list[hash_value].head;
    bool add_new = true;

    while (NULL != curr) {
        hash_node_t* node = (hash_node_t*)curr->object;
        if (strlen(node->key) == strlen(key)) {
            if (0 == strcmp(node->key, key)) {
                node->value = value;
                add_new = false;
                break;
            }
        }
        curr = curr->next;
    }

    if (true == add_new) {
        dlist_t* item = tools_hash_bucket_new(key, value);
        tools_dlist_push_back(&map->list[hash_value].head,
            &map->list[hash_value].tail, item);
        map->count++;
    }

    return 0;
}

/**
 * @brief
 *
 * @param map
 * @param key
 * @return void*
 */
void* tools_hashmap_get(hashmap_t* map, const char* key) {
    int hash_value = tools_get_hash_key(map, key);
    if (hash_value < 0) {
        return NULL;
    }

    void* value = NULL;
    dlist_t* curr = map->list[hash_value].head;
    while (NULL != curr) {
        hash_node_t* node = (hash_node_t*)curr->object;
        if (strlen(node->key) == strlen(key)) {
            if (0 == strcmp(node->key, key)) {
                value = node->value;
                break;
            }
        }
        curr = curr->next;
    }
    return value;
}

/**
 * @brief
 *
 * @param map
 * @param key
 */
void tools_hashmap_remove(hashmap_t* map, const char* key) {
    int hash_value = tools_get_hash_key(map, key);
    if (hash_value < 0) {
        return;
    }
    dlist_t* curr = map->list[hash_value].head;
    while (NULL != curr) {
        hash_node_t* node = (hash_node_t*)curr->object;
        if (strlen(node->key) == strlen(key)) {
            if (0 == strcmp(node->key, key)) {
                map->count--;
                break;
            }
        }
        curr = curr->next;
    }
    tools_dlist_remove(&map->list[hash_value].head,
        &map->list[hash_value].tail, curr);
    tools_hash_bucket_delete(&curr);
}

/**
 * @brief
 *
 * @param map
 */
void tools_hashmap_clear(hashmap_t* map) {
    if (map) {
        for (size_t i = 0; i < map->size; i++) {
            while (NULL != map->list[i].head) {
                dlist_t* item = tools_dlist_pop_back(
                    &map->list[i].head, &map->list[i].tail);
                tools_hash_bucket_delete(&item);
            }
        }
        map->count = 0;
    }
}

/**
 * @brief
 *
 * @param map
 */
void tools_hashmap_print(hashmap_t* map) {
    if (map) {
        for (size_t i = 0; i < map->size; i++) {
            char str[1024];
            str[0] = 0;
            bool empty = true;
            dlist_t* curr = map->list[i].head;
            while (NULL != curr) {
                empty = false;
                hash_node_t* node = (hash_node_t*)curr->object;
                snprintf(&str[strlen(str)], 1024 - strlen(str), "\"%s\"", node->key);
                if (NULL != curr->next) {
                    snprintf(&str[strlen(str)], 1024 - strlen(str), "->");
                }
                curr = curr->next;
            }
            if (true == empty) {
                snprintf(str, 1024, "<EMPTY>");
            }
            printf("%lu: %s\n", i, str);
        }
    }
}

/**
 * @brief
 *
 * @param map
 * @return size_t
 */
size_t tools_hashmap_count(hashmap_t *map) {
    return (NULL != map) ? map->count : 0;
}

/**
 * @brief
 *
 * @param map
 * @return size_t
 */
size_t tools_hashmap_size(hashmap_t *map) {
    return (NULL != map) ? map->size : 0;
}

#endif /* TOOLS_HASHMAP_ENABLED */
