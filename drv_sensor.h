#ifndef DRV_SENSOR_H
#define DRV_SENSOR_H

#include "dd_types.h"
#include "kernel.h"
#include <avr/io.h>

// Lista de funções do driver
enum {
    SENSOR_READ, 
    SENSOR_END
};

// Função de acesso ao driver
driver *getSensorDriver(void);

#endif
