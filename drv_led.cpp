#include "drv_led.h"

static driver meu_cartao;
static ptrFuncDrv my_funcs[LED_END];

char setLed(void * parameters) {
    uint8_t pin = ((uint8_t*)parameters)[0];
    uint8_t state = ((uint8_t*)parameters)[1];
    digitalWrite(pin, state);
    return SUCCESS;
}

char flipLed(void * parameters) {
    uint8_t pin = *((uint8_t*)parameters);
    digitalWrite(pin, !digitalRead(pin));
    return SUCCESS;
}

char initGenerico(void * parameters) {
    meu_cartao.id = (char) parameters;
    my_funcs[LED_SET] = setLed;
    my_funcs[LED_FLIP] = flipLed;
    return SUCCESS;
}

driver * getLedDriver(void) {
    meu_cartao.func_ptr = my_funcs;
    return &meu_cartao;
}