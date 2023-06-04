/**
 * @file    tools_crc.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    17.10.2020
 *
 * @brief
 */

#ifndef TOOLS_CRC_H
#define TOOLS_CRC_H

#include "tools_opt.h"

#ifdef TOOLS_CRC_ENABLED

#define CRC16_CCITT_INIT    (uint16_t)0xFFFF

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

uint8_t tools_crc8(const uint8_t*data, size_t size, uint8_t crc);
uint16_t tools_crc16_ccitt_0x1021(const uint8_t * data, uint16_t size, uint16_t crc);
uint16_t tools_crc16_ccitt_0x8005(const uint8_t * data, uint16_t size, uint16_t crc);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_CRC_ENABLED */
#endif /* TOOLS_CRC_H */
