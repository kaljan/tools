/**
 * @file    tools_dtc.c
 * @author  Mikalai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    5.11.2015
 *
 * @brief   Date time calendar
 */
#include "tools_dtc.h"

#ifdef TOOLS_DTC_ENABLE

#ifndef NULL
#define NULL ((void*)0)
#endif

/** Number of days in month */
static const int dtc_days_in_month[12]  = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/** English month names */
static const char* dtc_month_names_en[12] = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

/** English month names in lowercase */
static const char* dtc_month_names_long_lc_en[12] = {
    "january", "february", "march", "april", "may", "june", "july",
    "august", "september", "october", "november", "december"
};

/** English month names in upercase */
static const char* dtc_month_names_long_uc_en[12] = {
    "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY",
    "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
};

/** English month short names in lowercase */
static const char* dtc_month_names_short_lc_en[12] = {
    "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};

/** English month short names in uppercase */
static const char* dtc_month_names_short_uc_en[12] = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

/** English weekday names */
static const char* dtc_weekday_names_en[7] = {
    "Sunday", "Monday", "Tuestay", "Wednesday", "Thursday",
    "Friday", "Saturday"
};

/** English weekday long names in lower case*/
static const char* dtc_weekday_names_long_lc_en[7] = {
    "sunday", "monday", "tuestay", "wednesday", "thursday",
    "friday", "saturday"
};

/** English weekday long names in upper case*/
static const char* dtc_weekday_names_long_uc_en[7] = {
    "SUNDAY", "MONDAY", "TUESTAY", "WEDNESDAY", "THURSDAY",
    "FRIDAY", "SATURDAY",
};

/** English weekday long names in lower case*/
static const char* dtc_weekday_names_short_lc_en[7] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat",
};

/** English weekday long names in upper case*/
static const char* dtc_weekday_names_short_uc_en[7] = {
    "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT",
};


/**
 * Convert number of month to string name
 *
 * @param month      month number for 1 to 12
 * @param flags      config flags see @ref DTC_STRING_FLAGS
 *
 * @return if success returns pointer to month name string else return NULL
 */
const char* dtc_get_month_name_en(int month, int flags) {
    if ((month > 0) && (month <= 12)) {
        month -= 1;
        if ((flags & DTC_FC_NAME) == DTC_FC_NAME) {
            return dtc_month_names_en[month];
        } else if ((flags & DTC_SHORT_NAME) == DTC_SHORT_NAME) {
            if ((flags & DTC_LOWER_CASE) == DTC_LOWER_CASE) {
                return dtc_month_names_short_lc_en[month];
            } else {
                return dtc_month_names_short_uc_en[month];
            }
        } else {
            if ((flags & DTC_LOWER_CASE) == DTC_LOWER_CASE) {
                return dtc_month_names_long_lc_en[month];
            } else {
                return dtc_month_names_long_uc_en[month];
            }
        }
    }
    return NULL;
}

/**
 * Convert number of weekday to string name
 *
 * @param weekday    number of week 0 to 6
 * @param flags      config flags see @ref DTC_STRING_FLAGS
 *
 * @return if success returns pointer to weekday name string else return NULL
 */
const char* dtc_get_weekday_name_en(int weekday, int flags) {
    if ((weekday >= 0) && (weekday < 7)) {
        if ((flags & DTC_FC_NAME) == DTC_FC_NAME) {
            return dtc_weekday_names_en[weekday];
        } else if ((flags & DTC_SHORT_NAME) == DTC_SHORT_NAME) {
            if ((flags & DTC_LOWER_CASE) == DTC_LOWER_CASE) {
                return dtc_weekday_names_short_lc_en[weekday];
            } else {
                return dtc_weekday_names_short_uc_en[weekday];
            }
        } else {
            if ((flags & DTC_LOWER_CASE) == DTC_LOWER_CASE) {
                return dtc_weekday_names_long_lc_en[weekday];
            } else {
                return dtc_weekday_names_long_uc_en[weekday];
            }
        }
    }
    return NULL;
}

/**
 * Calculate number of day in month
 *
 * If mont is february and year is leap returns 29 else returns number
 * of days from @ref dtc_days_in_month
 *
 * @param month      month number 1 to 12
 * @param year       year
 *
 * @return Is success return number of days in month. If failed returns -1
 */
int dtc_calc_monthdays(int month, int year) {
    if ((month == 2) && DTC_IS_LEAP_YEAR(year)) {
        return 29;
    } else if (month > 0) {
        return dtc_days_in_month[month - 1];
    }
    return -1;
}

/**
 * Calculate number of weekday (0 to 6) of current date
 *
 * Formulas for calculating number of weekday
 *
 * Calculate coefficients:
 *
 * @f$a = \frac{14 - M}{12}@f$
 *
 * @f$y = Y - a@f$
 *
 * @f$m = M + 12 \cdot a - 2@f$
 *
 * Calculate weekday number:
 *
 * @f$[
 * W = \left(7000 + \left(D + y + \frac{y}{4} - \frac{y}{100} +
 * \frac{y}{400} + \frac{31 \cdot m}{12} \right) \right) \mod 7
 * @f]
 *
 * @param day        day of month
 * @param month      manth number 1 to 12
 * @param year       year
 * @return if success returns number of weekday else -1
 */
int dtc_calc_weekday(int day, int month, int year) {
    if ((day > 0) && (day <= dtc_calc_monthdays(month, year)) &&
        (month > 0) && (month <= 12) && (year > 0)) {

        int a = (14 - month) / 12;
        int m = month + (12 * a) - 2;
        int y = year - a;

        return ((7000 + day + y + (y / 4) -
            (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
    }
    return -1;
}

/**
 * Convert current datetime to number of seconds since fpoch
 *
 * Сначала переводим текущую дату (по григорианскуму календарю) в юлианский
 * день JDN.
 *
 * Convert gregorian date to JDN
 *
 * Calculate coefficients:
 *
 * @f$a = \frac{14-M}{12}@f$
 *
 * @f$y = Y + 4800 - a@f$
 *
 * @f$m = M + 12 \cdot a - 3@f$
 *
 * Calculate JDN:
 *
 * @f[
 * JDN = D + \frac{153 \cdot m + 2}{5} + 365 \cdot y + \frac{y}{4} -
 * \frac{y}{100} + \frac{y}{400} - 32045
 * @f]
 *
 * Next substracto from JDN substract JDN_START (see @ref DTC_START_DATE_CONFIG)
 * and multiply result to number of second in day (86400) and add current
 * time in seconds @f$(hour \cdot 3600 + minute \cdot 60 + seconfs)@f$
 *
 * @param context    pointer to date time structure
 *
 * @return if success datetime in seconds since epoch else 0
 */
dtc_time_t dtc_to_rtc(const dtc_t* context) {
    if (NULL != context) {
        int a = (14 - context->month) / 12;
        int y = context->year + 4800 - a;
        int m = context->month + (12 * a) - 3;
        int jdn = context->day + (((153 * m) + 2) / 5) + (365 * y) +
            (y / 4) - (y / 100) + (y / 400) - 32045;

        int d = jdn - JDN_START;

        dtc_time_t r = (d * 86400) + (context->hour * 3600) +
            (context->minute * 60) + context->second;

        return r;
    }
    return 0;
}

/**
 * Calculate date time from seconds since epoch
 *
 * At first calculate current JDN
 *
 * @f$\frac{seconds}{86400} + JDN_START@f$
 *
 * And next convert it to gregorian date
 *
 * Calculate coefficients first:
 *
 * @f$a = JDN + 32044@f$
 *
 * @f$b = \frac{4 \cdot a + 3}{146097}@f$
 *
 * @f$c = a - \frac{146097 \cdot b}{4}@f$
 *
 * @f$d = \frac{4 \cdot c + 3}{1461}@f$
 *
 * @f$e = c - \frac{1461 \cdot d}{4}@f$
 *
 * @f$m = \frac{5 \cdot e + 2}{153}@f$
 *
 * Next calculate current day, month and year
 *
 * @f$D = e - \frac{153 \cdot m + 2}{5} + 1@f$
 *
 * @f$M = m + 3 - 12 \frac{m}{10}@f$
 *
 * @f$Y = 100 \cdom b + d - 4800 + \frac{m}{10}@f$
 *
 * @param rtc_value  seconds since epoch
 * @param context    pointer to destination date time structure
 *
 * @return 0 if succes. -1 if failed
 */
int dtc_from_rtc(dtc_t* context, dtc_time_t rtc_value) {
    if (NULL != context) {
        int jdn = (rtc_value / 86400) + JDN_START;
        int a = jdn + 32044;
        int b = ((4 * a) + 3) / 146097;
        int c = a - ((146097 * b)/4);
        int d = (((4 * c) + 3) / 1461);
        int e = c - ((1461 * d) / 4);
        int m = ((5 * e) + 2) / 153;
        int r = rtc_value % 86400;

        context->day = e - (((153 * m) + 2) / 5) + 1;
        context->month = m + 3 - (12 * (m / 10));
        context->year = (100 * b) + d - 4800 + (m / 10);

        context->hour = r / 3600;
        r %= 3600;
        context->minute = r / 60;
        r %= 60;
        context->second = r;

        context->weekday = dtc_calc_weekday(context->day,
            context->month, context->year);
        return 0;
    }
    return -1;
}

#endif /* TOOLS_DTC_ENABLE */
