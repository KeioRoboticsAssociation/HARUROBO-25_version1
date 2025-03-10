#include "ElectromagneticValve.hpp"
#include "main.h"

//コンストラクタ
ElectromagneticValve::ElectromagneticValve(GPIO_TypeDef *ElectromagneticValvePort, uint16_t ElectromagneticValvePin){
    this->ElectromagneticValvePort = ElectromagneticValvePort;
    this->ElectromagneticValvePin = ElectromagneticValvePin;
}
// ElectromagneticValve::ElectromagneticValve(GPIO_TypeDef *ElectromagneticValvePort, uint16_t ElectromagneticValvePin, LED* indicatorLED){
//     this->ElectromagneticValvePort = ElectromagneticValvePort;
//     this->ElectromagneticValvePin = ElectromagneticValvePin;
//     this->indicatorLED = indicatorLED;
// }

//電磁弁を開く
void ElectromagneticValve::open(){
    HAL_GPIO_WritePin(ElectromagneticValvePort, ElectromagneticValvePin, GPIO_PIN_RESET);

    // HAL_GPIO_WritePin(ElectromagneticValvePort, ElectromagneticValvePin, GPIO_PIN_SET);
    // //LEDを点滅させる（３回チカチカ）
    // if (indicatorLED != nullptr){
    //     for (int i = 0; i < 3; i++){
    //         // indicatorLED->toggle();
    //         // HAL_Delay(200); //200ms待つ

    //         indicatorLED->on();
    //         HAL_Delay(500);
    //         indicatorLED->off();
    //         HAL_Delay(500);
    //     }
    //     indicatorLED->off(); //最後はLEDを消灯
    // }
}

//電磁弁を閉じる
void ElectromagneticValve::close(){
    HAL_GPIO_WritePin(ElectromagneticValvePort, ElectromagneticValvePin, GPIO_PIN_SET);
    
    // HAL_GPIO_WritePin(ElectromagneticValvePort, ElectromagneticValvePin, GPIO_PIN_RESET);
    // //LEDを点滅させる（３回チカチカ）
    // if (indicatorLED != nullptr){
    //     for (int i = 0; i < 3; i++){
    //         indicatorLED->toggle();
    //         HAL_Delay(200); //200ms待つ

    //         // indicatorLED->on();
    //         // HAL_Delay(100);
    //         // indicatorLED->off();
    //         // HAL_Delay(100);
    //     }
    //     indicatorLED->off(); //最後はLEDを消灯
    // }
}