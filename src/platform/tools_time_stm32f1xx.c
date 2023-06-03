/**
 * @file    tools_time_stm32f1xx.c
 * @author  Nikolai Naurotski (kaljan.nothern@gmail.com)
 * @version 1.0.0
 * @date    08.03.2020
 *
 * @brief
 */

#include "tools_time.h"

#ifdef STM32F1

#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_rcc.h"

#define SYS_TIMER              TIM2
#define SYS_TIMER_IRQ          TIM2_IRQn
#define SYS_TIMER_RCCEN       LL_APB1_GRP1_PERIPH_TIM2
#define SYS_TIMER_IRQ_HANDLER TIM2_IRQHandler

static uint64_t _time = 0;
static bool _initialized = false;

//size_t tools_time_get_size(void) {
//    return sizeof(_time) + sizeof(_initialized);
//}

void tools_time_init(void) {
    if (_initialized) {
        return;
    }

    _initialized = true;

    LL_RCC_ClocksTypeDef rccClocks;

    LL_RCC_GetSystemClocksFreq(&rccClocks);

    LL_TIM_InitTypeDef config;
    config.Prescaler = 0;
    config.CounterMode = LL_TIM_COUNTERMODE_UP;
    config.Autoreload = 0xFFFF;
    config.ClockDivision = 0;
    config.RepetitionCounter = 0;

    config.Prescaler = (rccClocks.PCLK1_Frequency / 1000000) - 1;

    LL_APB1_GRP1_EnableClock(SYS_TIMER_RCCEN);

    LL_TIM_Init(SYS_TIMER, &config);

    SYS_TIMER->CNT = 0;

    while (!LL_TIM_IsActiveFlag_UPDATE(SYS_TIMER));

    LL_TIM_ClearFlag_UPDATE(SYS_TIMER);

    LL_TIM_EnableIT_UPDATE(SYS_TIMER);
    NVIC_EnableIRQ(SYS_TIMER_IRQ);
    LL_TIM_EnableCounter(SYS_TIMER);
}

uint64_t tools_time_now_us(void) {
    return _time + LL_TIM_GetCounter(SYS_TIMER);
}

void SYS_TIMER_IRQ_HANDLER(void) {
    if (LL_TIM_IsActiveFlag_UPDATE(SYS_TIMER)) {
        LL_TIM_ClearFlag_UPDATE(SYS_TIMER);
        _time += 0xFFFF;
    }
}

int tools_time_current(struct timeval* t) {
    return 0;
}

#else
#error ERROR: This file only for STM32F1xx
#endif /* STM32F1 */
