#include "drv_sensor.h"
#include <Arduino.h>

static driver sensor_driver;
static ptrFuncDrv my_funcs[SENSOR_END];

char readSensor(void * parameters) {
    uint8_t pin = *((uint8_t*)parameters);
    return digitalRead(pin);
}

char initSensorDriver(void * parameters) {
    uint8_t pin = *((uint8_t*)parameters);
    pinMode(pin, INPUT);
    return SUCCESS;
}

driver * getSensorDriver(void) {
    sensor_driver.initFunc=initSensorDriver;
    my_funcs[SENSOR_READ] = readSensor;
    sensor_driver.funcoes=my_funcs;
    
    return &sensor_driver;
}