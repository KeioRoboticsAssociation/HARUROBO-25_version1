#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stm32f4xx_hal_tim.h>
#include <stm32f446xx.h>
#include "LED.hpp"

//LEDをつかうときはコメントアウトを外す（.hpp , .cpp）


//dir付き（DCモータ、MD）
class ServoMotor{
    private:
        GPIO_TypeDef* GPIO_Port;
        uint16_t GPIO_Pin;

        // //LEDクラスのインスタンスを生成
        // //nullptrはポインタ型の変数にnullを代入するためのキーワード
        // //LED* indicatorLED = nullptrはデフォルト引数
        // //デフォルト引数は引数が省略された場合に使用される値
        // //LED* indicatorLED = nullptrは引数が省略された場合にnullptrが代入される
        // LED* indicatorLED = nullptr;

        TIM_HandleTypeDef *htim;
        uint32_t channel;
        static constexpr int MIN_Pulse_Width_us = 500; //0.5ms = 500us
        static constexpr int MAX_Pulse_Width_us = 2500; //2.5ms = 2500us
        static constexpr int MIN_Angle = 0;
        static constexpr int MAX_Angle = 120;


    public:
        ServoMotor(TIM_HandleTypeDef *htim, uint32_t channel, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin);
        //ServoMotor(TIM_HandleTypeDef *htim, uint32_t channel, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin, LED* indicatorLED = nullptr);
        void SetAngle(int angle);
        void start();

};

// //dirなし（サーボ用）
// class ServoMotor{
//     private:
//         TIM_HandleTypeDef *htim;
//         uint32_t channel;
//         static constexpr int MIN_Pulse_Width_us = 500; //0.5ms = 500us
//         static constexpr int MAX_Pulse_Width_us = 2500; //2.5ms = 2500us
//         static constexpr int MIN_Angle = 0;
//         static constexpr int MAX_Angle = 120;

//     public:
//         Servomotor(TIM_HandleTypeDef *htim, uint32_t channel);
//         void SetAngle(int angle);
//         void start();
// };