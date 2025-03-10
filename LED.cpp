#include "LED.hpp"
#include "main.h"

// コンストラクタ
LED::LED(GPIO_TypeDef *ledPort, uint16_t myledPin){
    this->ledPort = ledPort;
    this->myledPin = myledPin;
}

// LEDを点灯
void LED::on() {
    HAL_GPIO_WritePin(ledPort, myledPin, GPIO_PIN_SET);
}

// LEDを消灯
void LED::off() {
    HAL_GPIO_WritePin(ledPort, myledPin, GPIO_PIN_RESET);
}

// LEDをトグル
void LED::toggle() {
    HAL_GPIO_TogglePin(ledPort, myledPin);
}
