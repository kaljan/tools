/**
 * @file    tools_misc.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    27.12.2022
 *
 * @brief
 */

#ifndef TOOLS_MISC_H
#define TOOLS_MISC_H

#include "tools_opt.h"

#define TOOLS_SUCCESS 0
#define TOOLS_FAILED -1

#define GET_OBJECT(obj_type, obj_name, arg) obj_type* obj_name = (obj_type*)arg;

#define ASSERT_OBJECT(type, arg, name) \
    if (!arg) { \
        msg_e("assertion failed"); \
        return; \
    } \
    type* name = (type*)arg;

#define ASSERT_OBJECT_RET(type, arg, name, ret) \
    if (!arg) { \
        msg_e("assertion failed"); \
        return ret; \
    } \
    type* name = (type*)arg;

#define CLEAR_OBJECT(obj_type, obj_ptr) \
    memset((void*)(obj_ptr), 0, sizeof(obj_type))

#define COPY_OBJECT(obj_type, obj_dst_ptr, obj_src_ptr) \
    memmove((void*)(obj_dst_ptr), (const void*)(obj_src_ptr), sizeof(obj_type))

#ifdef TOOLS_ALLOC_ENABLED
/* Create new data */
#define NEW_OBJECT(type) (type*)malloc(sizeof(type))

/* Create new array */
#define NEW_ARRAY(datatype, data_size) \
    (datatype*)calloc(data_size, sizeof(datatype))

/* Create new object */
#define CREATE_OBJECT(objtype, objname) \
    objtype* objname = (objtype*)malloc(sizeof(objtype))

/* Create new object array */
#define CREATE_ARRAY(datatype, arrayname, data_size) \
    datatype * arrayname = (datatype*)calloc(data_size, sizeof(datatype))

/* Free allocated memory*/
#define DELETE(datapointer) \
    free((void *)(datapointer)); \
    datapointer = NULL;
#endif /* ALLOC_ENABLED */

#endif /* TOOLS_MISC_H */
