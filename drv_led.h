#ifndef DRV_LED_H
#define DRV_LED_H

#include "dd_types.h"
#include <Arduino.h>

enum {
    LED_SET,
    LED_FLIP,
    LED_END
};

driver * getLedDriver(void);

#endif