/**
 * @file    tools_datetime.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    05.11.2015
 *
 * @brief
 */

#include "tools_datetime.h"

/* Defines */
/**
 * Юлианский день с котторого будем начинать отсчёт даты
 * Соответствует 1 января 2000 года
 */
#define JDN_START    2451545

#define RST_YEAR    2000
#define RST_MONTH    1
#define RST_DAY        1

/** Количество дней в месяце */
const char month_lenght[12]  = {
    31, 28, 31, 30,
    31, 30, 31, 31,
    30, 31, 30, 31
};

/**
 * @brief Переводит текущую дату и время в значение 32-битного регистра
 *
 * Сначала переводим текущую дату (по григорианскуму календарю) в юлианский
 * день JDN.
 *
 * Сначала вычисляем промежуточные коэффициенты
 * @f{ a = \frac{14-M}{12} @f}
 *
 * @f{ y = Y + 4800 - a @f}
 *
 * @f{ m = M + 12 \cdot a - 3 @f}
 *
 * И теперь вычисляем номер юлианского дня
 *
 * @f{ JDN = D + \frac{153 \cdot m + 2}{5} + 365 \cdot y + \frac{y}{4} -
 * \frac{y}{100} + \frac{y}{400} - 32045 @f}
 *
 * Далее имеем номер юлианского дня JDN, который и переводим в значение
 * регистра. Для начала отнимем от него номер юлианского дня который
 * соответствует дате 1 января 2000 года - 2451545. Это число задано
 * макросом JDN_START. После чего нужно это число умножить на количство
 * секунд в сутках, а это 86400. После чего будем иметь дату в секундах
 * в нашем регистре.
 *
 * К этой дате нужно ещё добавить текущее время. Для этого переведём
 * это время в секунды: час * 3600 + минута * 60 + секунда.
 *
 * @param dt - указатель на структуру даты времени
 *
 * @return Дату и время в формате 32-битного регистра
 */
uint32_t tools_set_datetime(const datetime_t* dt)
{
    if (!dt) {
        return 0;
    }

    int a = (14 - dt->month) / 12;
    int y = dt->year + 4800 - a;
    int m = dt->month + (12 * a) - 3;
    int jdn = dt->day + (((153 * m) + 2) / 5) + (365 * y) +
        (y / 4) - (y / 100) + (y / 400) - 32045;

    int d = jdn - JDN_START;

    uint32_t r = (d * 86400) + (dt->hour * 3600) +
        (dt->minute * 60) + dt->second;

    return r;
}

/**
 * @brief Переводит значение регистра в текщую дату и время
 *
 * Сначала находим значение юлианского дня из значения регистра. А это
 * значение регистра делённое на 86400 + JDN_START. Затем переводим
 * JDN в григорианскую дату.
 *
 * Для начала нужно вычислить промежуточные коэффициенты:
 *
 * @f{ a = JDN + 32044 @f}
 *
 * @f{ b = \frac{4 \cdot a + 3}{146097} @f}
 *
 * @f{ c = a - \frac{146097 \cdot b}{4} @f}
 *
 * @f{ d = \frac{4 \cdot c + 3}{1461} @f}
 *
 * @f{ e = c - \frac{1461 \cdot d}{4} @f}
 *
 * @f{ m = \frac{5 \cdot e + 2}{153} @f}
 *
 * а далее поочерёдно высчитываем текущие день, месяц и год.
 *
 * @f{ D = e - \frac{153 \cdot m + 2}{5} + 1 @f}
 *
 * @f{ M = m + 3 - 12 \frac{m}{10} @f}
 *
 * @f{ Y = 100 \cdom b + d - 4800 + \frac{m}{10} @f}
 *
 * @param datetime значение регистра
 *
 * @param dt указатель на структуру даты и времени, в которую всё и
 * сложится
 *
 */
void tools_get_datetime(uint32_t datetime, datetime_t* dt)
{
    if (!dt) {
        return;
    }
    int jdn = (datetime / 86400) + JDN_START;
    int a = jdn + 32044;
    int b = ((4 * a) + 3) / 146097;
    int c = a - ((146097 * b)/4);
    int d = (((4 * c) + 3) / 1461);
    int e = c - ((1461 * d) / 4);
    int m = ((5 * e) + 2) / 153;
    int r = datetime % 86400;

    dt->day = e - (((153 * m) + 2) / 5) + 1;
    dt->month = m + 3 - (12 * (m / 10));
    dt->year = (100 * b) + d - 4800 + (m / 10);

    dt->hour = r / 3600;
    r %= 3600;
    dt->minute = r / 60;
    r %= 60;
    dt->second = r;
}

/**
 * @brief  Вычисление номера дня недели
 *
 * Вычисение дня недели происходит следующим образом:
 * Сначала вычисляются коэффициенты
 *
 * @f{ a = \frac{14 - M}{12} @f}
 *
 * @f{ y = Y - a @f}
 *
 * @f{ m = M + 12 \cdot a - 2 @f}
 *
 * Далее вычисляем день ненеди, это будет остаток от деления на 7
 * (\mod 7) вот этой длиннюжей формулы
 *
 * @f{ W = \left(7000 + \left(D + y + \frac{y}{4} - \frac{y}{100} +
 * \frac{y}{400} + \frac{31 \cdot m}{12} \right) \right) \mod 7 @f}
 *
 * @param dt - указатель на структуру даты времени
 *
 */
void tools_get_weekday(datetime_t* dt)
{
    if (!dt) {
        return;
    }

    int a = (14 - dt->month) / 12;
    int y = dt->year - a;
    int m = dt->month + (12 * a) - 2;

    dt->weekday = ((7000 + dt->day + y + (y / 4) -
        (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
}

/**
 * @brief Выдаёт количество дней в текущем месяце.
 *
 * Если текущий месяц февраль и год високосный вернёт 29, иначе вернёт
 * соответствующее значение из массива month_lenght.
 *
 * @param dt - указатель на структуру даты/времени
 *
 * @return Количество дней в месяце dt->month
 *
 */
int tools_monthdays(datetime_t* dt)
{
    if (!dt) {
        return -1;
    }
    if (dt->month == 2 && (dt->year % 4) == 0) {
        if (dt->day > 29) {
            dt->day = 29;
        }
        return 29;
    }

    if (dt->day > month_lenght[dt->month - 1]) {
        dt->day = month_lenght[dt->month - 1];
    }

    return month_lenght[dt->month - 1];
}

int tools_get_monthdays(int month, int year) {
    if (month == 2 && (year % 4) == 0) {
        return 29;
    }

    return month_lenght[month - 1];
}
