#include "drv_motion_buzzer.h"

static driver motion_buzzer_driver;
static ptrFuncDrv my_funcs[MOTION_BUZZER_END];

char readMotion(void * parameters) {
    uint8_t pin = *((uint8_t*)parameters);
    return digitalRead(pin);
}

char toneBuzzer(void * parameters) {
    uint8_t pin = ((uint8_t*)parameters)[0];
    uint16_t frequency = ((uint16_t*)parameters)[1];
    uint16_t duration = ((uint16_t*)parameters)[2];
    tone(pin, frequency, duration);
    return SUCCESS;
}

char initMotionBuzzerDriver(void * parameters) {
    motion_buzzer_driver.id = (char) parameters;
    motion_buzzer_driver.func_ptr = my_funcs; // Corrigido: func_ptr em vez de funcoes
    my_funcs[MOTION_READ] = readMotion;
    my_funcs[BUZZER_TONE] = toneBuzzer;
    return SUCCESS;
}

driver * getMotionBuzzerDriver(void) {
    return &motion_buzzer_driver;
}