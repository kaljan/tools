/**
 * @file    tools_random.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    17.10.2020
 *
 * @brief
 */

#ifndef TOOLS_RANDOM_H
#define TOOLS_RANDOM_H

#include "tools_opt.h"

#ifdef TOOLS_RANDOM_ENABLED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void tools_random_init(void);
int tools_random_int(int start, int end);
void tools_random_str(char * ptr, size_t size);
void tools_random_string(char * text, size_t size);
void tools_random_data(uint8_t * data, size_t size);

#ifdef TOOLS_ALLOC_ENABLED
char * tools_random_create_string(size_t size);
uint8_t * tools_random_create_data(size_t size);
#endif /* TOOLS_ALLOC_ENABLED */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_RANDOM_ENABLED */
#endif /* TOOLS_RANDOM_H */
