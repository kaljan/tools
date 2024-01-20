/**
 * @file    tools_assert.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    27.12.2022
 *
 * @brief
 */

#ifndef TOOLS_ASSERT_H
#define TOOLS_ASSERT_H

#include "tools_opt.h"

#ifdef TOOLS_ASSERT_ENABLED

#define IS_NULL(ptr) (NULL == (ptr))

#define IS_NOT_NULL(ptr) (NULL != (ptr))

#define ASSERT_PTR(arg) \
    if (NULL == (arg)) { \
        msg_e("assert error"); \
        return; \
    }

#define ASSERT_PTR_RET(arg, ret) \
    if (NULL == (arg)) { \
        msg_e("assert error"); \
        return ret; \
    }

#define ASSERT_VAL(val) \
    if (0 == (val)) { \
        msg_e("assert error"); \
        return; \
    }

#define ASSERT_VAL_RET(val, ret) \
    if (0 == (val)) { \
        msg_e("assert error"); \
        return ret; \
    }

#define ASSERT_STRING(str) \
    if ((NULL == (str)) || (0 == strlen((str)))) { \
        msg_e("assert error"); \
        return;\
    }

#define ASSERT_STRING_RET(str, ret) \
    if ((NULL == (str)) || (0 == strlen((str)))) { \
        msg_e("assert error"); \
        return ret; \
    }
#else
#define ASSERT_PTR(arg)
#define ASSERT_PTR_RET(arg, ret)
#define ASSERT_STRING(str)
#define ASSERT_STRING_RET(str, ret)
#endif

#endif /* TOOLS_ASSERT_H */
