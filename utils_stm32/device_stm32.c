#include "device.h"

static volatile bool timer_already_init;
uint32_t critical_nesting_level;

uint32_t HAL_GetTick(void) {
    return get_time_ms32();
}

void configureTimerForRunTimeStats(void) {
    static bool already_init = false;
    if (already_init) {
        return;
    }
    CoreDebug->DEMCR |= 0x01000000;
    DWT->CYCCNT = 0;
    DWT->CTRL |= 1; /* enable the counter */
    already_init = true;
}

static inline uint32_t getRunTimeCounterValue_(void) {
    if (!timer_already_init) {
        configureTimerForRunTimeStats();
    }
    return DWT->CYCCNT;
}

uint32_t getRunTimeCounterValue32(void) {
    return getRunTimeCounterValue_ ();
}

uint64_t getRunTimeCounterValue64(void) {
    static volatile uint64_t wrap_counter;
    static volatile uint32_t prev_value;
    uint32_t value;
    enter_critical ();
    value = getRunTimeCounterValue_ ();
    if (value < prev_value) {
        wrap_counter += 0x100000000LLU;
    }
    prev_value = value;
    exit_critical ();
    return wrap_counter | value;
}

uint32_t get_time_ms32(void) {
    return getRunTimeCounterValue64 () / (COUNTER_FREQ * 1000);
}

uint64_t get_time_ms64(void) {
    return getRunTimeCounterValue64 () / (COUNTER_FREQ * 1000);
}

uint64_t get_time_us(void) {
    return getRunTimeCounterValue64 () / COUNTER_FREQ;
}

void delay (uint32_t delay_in_ms) {
    uint64_t stop = get_time_ms64 () + delay_in_ms;
    while (get_time_ms64 () < stop) {
    }
}

void delay_wd (uint32_t delay_in_ms) {
    uint64_t stop = get_time_ms64 () + delay_in_ms;
    while (get_time_ms64 () < stop) {
        wdt_reset_all ();
    }
}
