/**
 * @file    tools_assert.h
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    Dec 27, 2022
 *
 * @brief
 */

#ifndef TOOLS_ASSERT_H
#define TOOLS_ASSERT_H

#include "tools_opt.h"

#ifdef TOOLS_ASSERT_ENABLED
#define ASSERT_ARG(arg) \
    if (!arg) { \
        msg_e("assert error"); \
        return; \
    }

#define ASSERT_ARG_RET(arg, ret) \
    if (!arg) { \
        msg_e("assert error"); \
        return ret; \
    }

#define ASSERT_STRING(str) \
    if (!str || !strlen(str)) { \
        msg_e("assert error"); \
        return;\
    }

#define ASSERT_STRING_RET(str, ret) \
    if (!str || !strlen(str)) { \
        msg_e("assert error"); \
        return ret; \
    }
#else
#define ASSERT_ARG(arg)
#define ASSERT_ARG_RET(arg, ret)
#define ASSERT_STRING(str)
#define ASSERT_STRING_RET(str, ret)
#endif

#endif /* TOOLS_ASSERT_H */
