#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stm32f4xx_hal_tim.h>
#include <stm32f446xx.h>
#include "LED.hpp"

//LEDをつかうときはコメントアウトを外す（.hpp , .cpp）

class ElectromagneticValve{
    private:
        GPIO_TypeDef* ElectromagneticValvePort;
        uint16_t ElectromagneticValvePin;

        // //LEDクラスのインスタンスを生成
        // //nullptrはポインタ型の変数にnullを代入するためのキーワード
        // //LED* indicatorLED = nullptrはデフォルト引数
        // //デフォルト引数は引数が省略された場合に使用される値
        // //LED* indicatorLED = nullptrは引数が省略された場合にnullptrが代入される
        // LED* indicatorLED;

    public:
        // //nullptrはポインタ型の変数にnullを代入するためのキーワード
        // ElectromagneticValve(GPIO_TypeDef *ElectromagneticValvePort, uint16_t ElectromagneticValvePin, LED* indicatorLED = nullptr);
        
        ElectromagneticValve(GPIO_TypeDef *ElectromagneticValvePort, uint16_t ElectromagneticValvePin);
        
        void open();
        void close();
};