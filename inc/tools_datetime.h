/*!
 * @file    tools_datetime.h
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    05.11.2015
 *
 * @brief
 */
#ifndef TOOLS_DATETIME_H
#define TOOLS_DATETIME_H

#include <stdint.h>

/* Typedefs */

typedef struct datetime {
    int second; /* Seconds [0-59] TODO Add leap second */
    int minute; /* Minutes [0-59] */
    int hour;   /* Hours [0-23] */
    int day;    /* Day [1-31] */
    int month;  /* Month [1..12] TODO move to [0-11]*/
    int year;   /* Year for 32 bit RTC[2000-2135] */
    int weekday; /* Weekday [0-6] */
} datetime_t;

extern const char month_lenght[12];

/* Prototypes */
uint32_t tools_set_datetime(const datetime_t* dt);
void tools_get_datetime(uint32_t datetime, datetime_t* dt);
void tools_get_weekday(datetime_t* dt);
int tools_monthdays(datetime_t* dt);
int tools_get_monthdays(int month, int year);

#endif /* TOOLS_DATETIME_H */
