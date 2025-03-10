#include "main.hpp"
#include "UartLink.hpp"
#include "Encoder.hpp"
#include "BNO055_UART.hpp"
#include "message.hpp"
#include "RoboMasterController.hpp"
#include "DCMotor.hpp"
#include "ElectromagneticValve.hpp"
#include "ServoMotor.hpp"
#include "LED.hpp"

int angle = 0;

// ---- uart ----
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

// ---- can ----
//extern CAN_HandleTypeDef hcan1;

// ---- timer ----
extern TIM_HandleTypeDef htim1; // for encoder
extern TIM_HandleTypeDef htim2; // for pwm
extern TIM_HandleTypeDef htim3; // for encoder
extern TIM_HandleTypeDef htim4; // for encoder
extern TIM_HandleTypeDef htim5; // 割り込み(20Hz)
extern TIM_HandleTypeDef htim6; // 割り込み(100Hz)
extern TIM_HandleTypeDef htim7; // 割り込み(1000Hz)
extern TIM_HandleTypeDef htim8; // for encoder


// ---- 対ROS通信 ----
UartLink uart_link(&huart2, 0);
Publisher<UartLink, float, float, float, float, float> periodic_pub(uart_link, messages::transmission::PERIODIC);
// //データの送信, publisherの設定
//UartLinkPublisher<bool> pub(uart_link, 1);
//データの受信, subscriberの設定
UartLinkSubscriber<bool> sub_kokuban(uart_link, 1);
UartLinkSubscriber<bool> sub_ball(uart_link, 2);
UartLinkSubscriber<bool> sub_LED(uart_link, 3);

// ---- IMU ----
BNO055_UART imu(&huart3, EUL_AXIS::EUL_X);

// ---- LED ----
LED led1(GPIOA, GPIO_PIN_10); //PA_10

//----ServoMotor----
//NHK2025基盤
ServoMotor servoMotor1(&htim2, TIM_CHANNEL_1, GPIOB, GPIO_PIN_15); //PA_0(TIM2_CH1/pwm_3),PB_15(dir_3)
// //SpringRObocon2025基盤(dirなし)
// ServoMotor servoMotor1(&htim2, TIM_CHANNEL_1); //PA_6(TIM2_CH1/pwm),PB_15
// //----ServoMotor(LED付き)----
// ServoMotor servoMotor1(&htim2, TIM_CHANNEL_1, GPIOB, GPIO_PIN_15, &led1); //PA_0(TIM2_CH1),PB_15(dir_3),PA_5

//----ElecttomagneticValve----
//NHK2025基盤
ElectromagneticValve electromagneticValve1(GPIOC, GPIO_PIN_8); //J15(PB_12)
// //SpringRObocon2025基盤
// ElectromagneticValve electromagneticValve1(GPIOA, GPIO_PIN_11); //J7(PA_11)
// //----ElecttomagneticValve(LED付き)----
// ElectromagneticValve electromagneticValve1(GPIOB, GPIO_PIN_12, &led1); //J15(PB_12),PA_5

// ---- encoder ----
Encoder encoder1(&htim1, 4096); 
Encoder encoder2(&htim4, 4096);
Encoder encoder3(&htim8, 4096); 
Encoder encoder4(&htim3, 4096); 

// ---- flag ----
bool htim5_flag = false; // 20Hzでtrueになる

// UART受信割り込み
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        uart_link.interrupt(); // ros2との通信で受信したデータを処理
    } else if (huart->Instance == USART3) {
        //imu.interrupt();
    }
}

// GPIO割り込み
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    
}

// タイマー割り込み
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM5) {
        // 20Hz
        htim5_flag = true;
    } else if (htim->Instance == TIM6) {
        // 100Hz
        imu.request_flag = true;
    } else if (htim->Instance == TIM7) {
        // 1000Hz
        encoder1.getRawCount();
        encoder2.getRawCount();
        encoder3.getRawCount();
        encoder4.getRawCount();
    }
}

// サブスクライバのコールバック関数
void servoCallback_kokuban(bool servo_state) {
    // ここにコールバック関数の処理を書く
    if (servo_state == true) 
    {
        //(黒板)
        // 電磁弁を開く
        electromagneticValve1.open();
        // 下げる
        // 30度から120度まで3度ずつ増やす
        for (int angle = 30; angle <= 120; angle += 3){
            servoMotor1.SetAngle(angle);
            HAL_Delay(15);
        }
        HAL_Delay(300);
        //ものをつかむ
        electromagneticValve1.close();
        HAL_Delay(500);
        //　上げる
        // 120度から0度まで3度ずつ減らす
        for(int angle = 120; angle >= 0; angle -= 3){
            servoMotor1.SetAngle(angle);
            HAL_Delay(15);
        }
        HAL_Delay(1000);
        // ものを落とす
        electromagneticValve1.open();
        HAL_Delay(300);
        //　もとの位置に戻る
        // 0度から30度まで3度ずつ増やす
        for(int angle = 0; angle <= 30; angle += 3){
            servoMotor1.SetAngle(angle);
            HAL_Delay(10);
        }
        // HAL_Delay(10000);
    }
}

void servoCallback_ball(bool servo_state) {
    // ここにコールバック関数の処理を書く
    if (servo_state == true)
    {
        //(ボール)
        // 電磁弁を開く
        electromagneticValve1.open();
        // 下げる
        // 30度から90度まで3度ずつ増やす
        for (int angle = 30; angle <= 90; angle += 3){
            servoMotor1.SetAngle(angle);
            HAL_Delay(15);
        }
        HAL_Delay(300);
        // ものをつかむ
        electromagneticValve1.close();
        HAL_Delay(500);
        //　上げる
        // 90度から0度まで3度ずつ減らす
        for(int angle = 90; angle >= 0; angle -= 3){
            servoMotor1.SetAngle(angle);
            HAL_Delay(15);
        }
        HAL_Delay(400);
        // ものを落とす
        electromagneticValve1.open();
        HAL_Delay(500);
        //　もとの位置に戻る
        // 0度から90度まで3度ずつ増やす
        for(int angle = 0; angle <= 30; angle += 3){
            servoMotor1.SetAngle(angle);
            HAL_Delay(10);
        }
    }
}    

void ledCallback(bool LED_state) {
    // ここにコールバック関数の処理を書く
    if (LED_state == true)
    {
        led1.on();
    }
    else
    {
        led1.off();
    }
}

//初期化処理を以下に書く
void setup() {
    uart_link.start(); // ros2との通信を開始
    imu.start(); // IMUを開始
    // timer
    HAL_TIM_Base_Start_IT(&htim5); // 20Hz
    HAL_TIM_Base_Start_IT(&htim6); // 100Hz
    HAL_TIM_Base_Start_IT(&htim7); // 1000Hz

    // // encoder
    // encoder1.start();
    // encoder2.start();
    // encoder3.start();
    // encoder4.start();

    //サーボモータ
    servoMotor1.start();

    // サブスクライバのコールバック関数を設定
    sub_kokuban.set_callback(servoCallback_kokuban);
    sub_ball.set_callback(servoCallback_ball);
    sub_LED.set_callback(ledCallback);

    led1.off();
}

void loop() {
}

    
