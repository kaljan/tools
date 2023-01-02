/**
 * @file 	tools_random.c
 * @author	Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version	1.0.0
 * @date	Oct 17, 2020
 *
 * @brief
 */

#include "tools_random.h"

#ifdef TOOLS_RANDOM_ENABLED

#include "tools_time.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// #include <unistd.h>
// #include <sys/time.h>

/**
 * Initialize random
 */
void tools_random_init(void) {
	struct timeval t;
	if (tools_time_current(&t) != 0) {
		return;
	}
	srand((uint32_t)(t.tv_sec ^ t.tv_usec));
}


/**
 * @brief
 *
 * @param start
 * @param end
 * @return int
 */
int tools_random_int(int start, int end) {
	if (start < end) {
		return (rand() % (abs(end - start) + 1)) + start;
	} else if (start > end) {
		return (rand() % (abs(end - start) + 1)) + end;
	}
	return start;
}

/**
 * @brief
 *
 * @param c
 * @return int
 */
static int p_ischar(int c) {
	if (c >= '0' && c <= '9') {
		return c;
	} else if (c >= 'A' && c <= 'Z') {
		return c;
	} else if (c >= 'a' && c <= 'z') {
		return c;
	} else if (c == '_') {
		return c;
	}
	return 0;
}

/**
 * @brief
 *
 * @param ptr
 * @param size
 */
void tools_random_str(char * ptr, size_t size) {
	if (ptr && size > 2) {
		uint32_t r;
		int c;
		r = (uint32_t)rand();
		while (size > 0) {
			if (r < 20) {
				r = (uint32_t)rand();
			}

			c = p_ischar((int)(r & 0x7F));
			r >>= 7;

			if (c != 0) {
				*ptr = (char)c;
				size--;
				ptr++;
			}
		}
		*ptr = 0;
	}
}

/**
 * @brief
 *
 * @param text
 * @param size
 */
void tools_random_string(char * text, size_t size) {
    if (!text || !size) {
        return;
    }

    uint32_t rv = 0;
    uint8_t c = 0;
    while (size > 0) {
        if (!rv) {
            rv = (uint32_t)rand();
        }

        c = (uint8_t)(rv & 0x7F);

        if (c < 0x5D) {
            *text = (char)(c + 0x21);
            size--;
            text++;
        }

        rv >>= 7;
    }
    *text = 0;
}

/**
 * @brief
 *
 * @param data
 * @param size
 */
void tools_random_data(uint8_t * data, size_t size) {
	if (data && size > 0) {
		while (size > 0) {
			int s = (size < 4) ? size : 4;
			int r = rand();
			memmove(data, &r, s);
			data += s;
			size -= s;
		}
	}
}

#ifdef TOOLS_ALLOC_ENABLED

/**
 * @brief
 *
 * @param size
 * @return char*
 */
char * tools_random_create_string(size_t size) {
    char * str = malloc(size + 1);
	tools_random_string(str, size);
	return str;
}

/**
 * @brief
 *
 * @param size
 * @return uint8_t*
 */
uint8_t * tools_random_create_data(size_t size) {
	uint8_t * data = malloc(size);
	tools_random_data(data, size);
	return data;
}

#endif /* TOOLS_ALLOC_ENABLED */
#endif /* TOOLS_RANDOM_ENABLED */