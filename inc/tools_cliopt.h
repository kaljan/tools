/**
 * @file    tools_cliopt.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    12.05.2020
 *
 * @brief
 */
#ifndef TOOLS_CLIOPT_H
#define TOOLS_CLIOPT_H

#include "tools_opt.h"

#ifdef TOOLS_CLIOPT_ENABLED

typedef enum opt_type {
    cli_opt_flag = 0,
    cli_opt_single_arg = 1,
    cli_opt_muliple_args = 2
} opt_type_t;

typedef struct opt_node {
    char short_name;
    const char* long_name;
    const char* description;
    opt_type_t type;
    void* object;
    int (*callback)(void*, const char*);
    struct opt_node* next;
} opt_node_t;

typedef struct opt_container {
    const char* app_name;
    const char* usage_text;
    const char* description;
    int argc_min;
    opt_node_t* head;
    void* object;
    int (*callback)(void*, const char*);
} opt_container_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int tools_cliopt_exec(opt_container_t* context, int argc, char** argv);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_CLIOPT_ENABLED */
#endif /* TOOLS_CLIOPT_H */
/* EOF */
