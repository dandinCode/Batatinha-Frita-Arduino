#ifndef DRV_MOTION_BUZZER_H
#define DRV_MOTION_BUZZER_H

#include "dd_types.h"
#include <Arduino.h>

enum {
    MOTION_READ,  // Função para ler o sensor de movimento
    BUZZER_TONE,  // Função para ativar o buzzer
    MOTION_BUZZER_END // Fim da enumeração
};

// Função de acesso ao driver
driver * getMotionBuzzerDriver(void);

#endif