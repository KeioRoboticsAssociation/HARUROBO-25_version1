#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stm32f4xx_hal_tim.h>
#include <stm32f446xx.h>

class LED{
    private:
        GPIO_TypeDef *ledPort;
        uint16_t myledPin;

    public:
        LED(GPIO_TypeDef *ledPort,uint16_t myledPin);
        void on();
        void off();
        void toggle();
};