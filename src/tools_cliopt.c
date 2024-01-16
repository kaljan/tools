/**
 * @file    tools_cliopt.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    12.05.2020
 *
 * @brief
 *
 * TODO Help print
 * TODO Version print
 *
 */
#include "tools_cliopt.h"
#include "tools_assert.h"
#include "tools_print.h"
#include "tools_string.h"
#include "tools_misc.h"
#include "tools_debug.h"

#ifdef TOOLS_CLIOPT_ENABLED


static int opt_strcmp(const char* opt1, const char* opt2) {
    if (strlen(opt1) == strlen(opt2)) {
        return strcmp(opt1, opt2);
    }
    return -1;
}

static int opt_node_set_optarg(opt_node_t* context, char* arg) {
    ASSERT_ARG_RET(context->callback, -1)
    int ret = 0;
    if (NULL == arg) {
        ret = context->callback(context->object, NULL);
    } else if ('-' != *arg) {
        ret = context->callback(context->object, arg);
    } else {
        return 0;
    }

    if (ret < 0) {
        print_e("opt callback returned: %d", ret);
    } else {
        ret = 1;
    }

    return ret;
}

static int opt_node_parse_arg(opt_node_t* context, char** arg) {
    ASSERT_ARG_RET(context->callback, -1)

    print_v("start");
    int ret = 0;

    while (NULL != *arg) {
        print_v("arg: \'%s\'", *arg);

        int result = opt_node_set_optarg(context, *arg);
        if (result < 0) {
            print_e("parse arg failed");
            ret = -1;
            break;
        } else if (result == 0) {
            break;
        }
        ret++;
        arg++;
    }
    print_v("return: %d", ret);
    return ret;
}

static int opt_node_split_callback(void* ctx, const char* str, size_t size) {
    ASSERT_OBJECT_RET(opt_node_t, context, ctx, -1)
    int ret = -1;
    if (NULL != context->callback) {
        ret = context->callback(context->object, str);
    }
    return ret;
}

static int opt_node_split_arg(opt_node_t* context, char* arg) {
    int clbk_ret = 0;
    int ret = tools_string_split(arg, strlen(arg), ',',
        opt_node_split_callback, context, &clbk_ret);
    if (ret < 0) {
        if (clbk_ret < 0) {
            print_e("parse arg failed");
        } else {
            ret = 0;
        }
    } else if (ret > 0) {
        ret = 1;
    }
    return ret;
}

static int opt_node_common_parse(opt_node_t* context, char** argv) {
    int ret = 0;
    if (context->type == cli_opt_flag) {
        ret = opt_node_set_optarg(context, NULL);
        if (ret < 0) {
            print_e("set flag failed");
        }
    } else if (context->type == cli_opt_single_arg) {
        ret = opt_node_set_optarg(context, *argv);
        if (ret < 0) {
            print_e("set opt failed");
        } else if (ret > 0) {
            ret += 1;
        }
    } else {
        ret = opt_node_parse_arg(context, argv);
        if (ret <= 0) {
            print_e("has no arguments");
        } else {
            ret += 1;
        }
    }
    return ret;
}

static int opt_node_short_flag_find(opt_node_t* context, char opt) {
    int ret = 0;
    while (NULL != context) {
        if (context->type == cli_opt_flag &&
            context->short_name == opt) {
            ret = opt_node_set_optarg(context, NULL);
            break;
        }
        context = context->next;
    }
    return ret;
}

static int opt_node_short_find(opt_node_t* context, char opt, char** argv) {
    int ret = 0;
    while (NULL != context) {
        if (context->short_name == opt) {
            ret = opt_node_common_parse(context, argv);
            break;
        }
        context = context->next;
    }
    return ret;
}

static int opt_node_long_find(opt_node_t* context, char* opt, char** argv) {
    int ret = 0;
    while (NULL != context) {
        if (opt_strcmp(context->long_name, opt) == 0) {
            ret = opt_node_common_parse(context, argv);
            break;
        }
        context = context->next;
    }
    return ret;
}

static int opt_node_long_comma_find(opt_node_t* context, char* opt, char* arg) {
    int ret = 0;
    while (NULL != context) {
        if (opt_strcmp(context->long_name, opt) == 0) {
            ret = opt_node_split_arg(context, arg);
            break;
        }
        context = context->next;
    }
    return ret;
}

static int opt_container_parse(opt_container_t* context, char* opt, char** argv) {
    int ret = 0;
    print_v("opt: \"%s\"", opt);
    if ('-' == *opt) {
        opt++;
        if ('-' == *opt) {
            print_v("parse long opt");
            opt++;
            char* ptr = strchr(opt, '=');
            if (NULL != ptr) {
                *ptr = 0;
                ptr++;
                print_v("comma separated args");
                ret = opt_node_long_comma_find(context->head, opt, ptr);
            } else {
                print_v("space separated args");
                ret = opt_node_long_find(context->head, opt, argv);
            }
        } else {
            print_v("parse short opts");
            size_t len = strlen(opt);
            if (len == 1) {
                print_v("parse opts");
                ret = opt_node_short_find(context->head, *opt, argv);
            } else if (len > 1) {
                print_v("parse flag collection");
                while (0 != *opt) {
                    ret = opt_node_short_flag_find(context->head, *opt);
                    if (ret <= 0) {
                        print_e("bad flag");
                        ret = -1;
                        break;
                    }
                    opt++;
                }
            }
        }
    } else {
        print_v("parse default argument");
        if (context->callback) {
            ret = context->callback(context->object, opt);
        } else {
            print_e("application has no default arguments");
            ret = -1;
        }
    }

    print_v("return: %d", ret);
    return ret;
}

int tools_cliopt_exec(opt_container_t* context, int argc, char** argv) {
    ASSERT_ARG_RET(context, -1)
    ASSERT_ARG_RET(argv, -1)
    int ret = 0;
    print_v("start parsing options");
    if (context->argc_min > 0) {
        if (argc < (context->argc_min + 1)) {
            printf("USAGE: %s\n", context->usage_text);
            return -1;
        }
    }
    argv++;

    while (NULL != *argv) {
        char* opt = *argv;

        ret = opt_container_parse(context, opt, argv + 1);
        if (ret <= 0) {
            print_e("bad argument");
            break;
        }
        argv += ret;
    }

    return ret;
}

#endif /* TOOLS_CLIOPT_ENABLED */
