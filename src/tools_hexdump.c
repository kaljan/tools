/**
 * @file    tools_hexdump.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    27.12.2020
 *
 * @brief
 */
#include "tools_hexdump.h"
#include "tools_print.h"
#include <ctype.h>

// static const char* hexdump_header_byte_char = "           0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F  01234567 89ABCDEF";

/*!
 * Print hexdump on terminal
 *
 * @param data  pointer to input data buffer
 * @param size  input data size
 * @param flags
 */
void tools_hexdump(const uint8_t * data, size_t size, int flags) {
    size_t nblk = 0, nb = 0, ns = 0;
    const uint8_t * bptr;

    if (!data || !size) {
        return;
    }

    TOOLS_PRINT_LOCK();

    printf("           0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F  01234567 89ABCDEF");

    while (1) {
        printf("\n%08X: ", (uint32_t)(nblk * 16));

        bptr = data + (nblk * 16);
        ns = size - (nblk * 16);

        if (ns > 16) {
            ns = 16;
        }

        nb = 0;
        while (nb < 16) {
            if (nb < ns) {
                printf("%02X ", *(bptr + nb));
            } else {
                printf("   ");
            }

            if (nb == 7) {
                printf(" ");
            }

            nb++;
        }

        printf(" ");

        nb = 0;
        while (nb < ns) {
            printf("%c", (isgraph(*(bptr + nb)) == 0) ? '.' : *(bptr + nb));
            if (nb == 7) {
                printf(" ");
            }
            nb++;
        }

        nblk++;
        if (nblk * 16 >= size) {
            break;
        }
    }

    printf("\n\nSIZE: %lu\n\n", size);
    TOOLS_PRINT_UNLOCK();
}
