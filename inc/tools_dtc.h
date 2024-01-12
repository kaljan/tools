/**
 * @file    tools_dtc.h
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    5.11.2015
 *
 * @brief   Date time calendar
 */
#ifndef TOOLS_DTC_H
#define TOOLS_DTC_H

#include "tools_opt.h"

#ifdef TOOLS_DTC_ENABLE
/**
 * @defgroup DTC_VERSION
 *
 * @{
 */
#define DTC_VERSION_MAJOR       1
#define DTC_VERSION_MINOR       0
#define DTC_VERSION_REVISION    0
/**
 * @}
 */


/**
 * @defgroup DTC_START_DATE_CONFIG
 *
 * @{
 */

/**
 * the date(Year, month and day) from which we will start counting the date
 */
#define RST_YEAR    2000
#define RST_MONTH   1
#define RST_DAY     1

/**
 * the Julian Day Number(JDN) from which we will start counting the date
 * Соответствует 1 января 2000 года
 */
#define JDN_START    2451545

/**
 * @}
 */


/**
 * @defgroup DTC_STRING_FLAGS
 *
 * Flags for converting month and weekdaye to string names
 * @{
 */

/** Get full name in lower case and with first capital latter */
#define DTC_FC_NAME         0x0001

/** Get name in lower case flag */
#define DTC_LOWER_CASE      0x0002

/** Get short name flag */
#define DTC_SHORT_NAME      0x0004
/**
 * @}
 */


/**
 * Check value for leap year.
 *
 * Every year that evenly divisible by 4 or by 100 and 400 is leap
 */
#define DTC_IS_LEAP_YEAR(year) \
    ((((year) % 4) == 0) || ((((year) % 100) == 0) && (((year) % 400) == 0)))


/** Date and time in senconds type */
typedef unsigned long dtc_time_t;

/**
 * Date and time
 */
typedef struct tools_dtc {
    int second;   /* 00..59 */
    int minute;   /* 00..59 */
    int hour;     /* 00..23 */
    int day;      /* start from 1 */
    int month;    /* 1..12 */
    int year;     /* 2000..2135 */
    int weekday;  /* 0..6 */
} dtc_t;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char* dtc_get_month_name_en(int month, int flags);
const char* dtc_get_weekday_name_en(int weekday, int flags);

int dtc_calc_monthdays(int month, int year);
int dtc_calc_weekday(int day, int month, int year);

dtc_time_t dtc_to_rtc(const dtc_t * dt);
int dtc_from_rtc(dtc_t* context, dtc_time_t rtc_value);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOOLS_DTC_ENABLE */
#endif /* TOOLS_DTC_H */
