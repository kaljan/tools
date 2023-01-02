/**
 * @file    tools_hexdump.h
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    Dec 27, 2020
 *
 * @brief
 */
#ifndef TOOLS_HEXDUMP_H
#define TOOLS_HEXDUMP_H

#include "tools_opt.h"

#define THD_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void tools_hexdump(const uint8_t* data, size_t size, int flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TOOLS_HEXDUMP_H */
/* EOF */
