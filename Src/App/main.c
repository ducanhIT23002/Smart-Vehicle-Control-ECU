#include "LPC17xx.h"
#include <stdio.h>

// CHỈ SỬ DỤNG TẦNG RTE ĐỂ ĐẢM BẢO KIẾN TRÚC
#include "Rte_Door.h"
#include "Rte_Wiper.h"
#include "Rte_Light.h"
#include "Rte_Sensor.h"
#include "gpio.h"

void App_BCM_FullIntegration_Task(void) {
    // --- 1. TEST CỬA (Rte_Read_DoorStatus & Rte_Write_P_DoorLed_Status) ---
    // Sử dụng Joystick UP (P1.23)
    if (Rte_Read_DoorStatus() == 0) { // Nhấn UP = Mở cửa
        Rte_Write_P_DoorLed_Status(1); // Sáng LED P2.3
    } else {
        Rte_Write_P_DoorLed_Status(0); // Tắt LED P2.3
    }

    // --- 2. TEST GẠT MƯA (Rte_Read_WiperSwitch & Rte_Call_Wiper_Start/Stop) ---
    // Sử dụng Joystick LEFT (P1.24)
    if (Rte_Read_WiperSwitch() == 0) { // Nhấn LEFT = Bật gạt mưa
        Rte_Call_Wiper_StartIntMode();  // Sáng LED P1.29
        Rte_Write_WiperMode(WIPER_INT); // Test thêm hàm WriteMode
    } else {
        Rte_Call_Wiper_Stop();          // Tắt LED P1.29
    }

    // --- 3. TEST ÁNH SÁNG (Rte_Read_IsEnvironmentDark & Rte_Call_Headlight_TurnOn/Off) ---
    // Sử dụng Joystick DOWN (P1.25) làm "Cảm biến giả"
    if (Rte_Read_IsEnvironmentDark()) { // Nhấn DOWN = Trời tối
        Rte_Call_Headlight_TurnOn();    // Sáng LED P1.28
    } else {
        Rte_Call_Headlight_TurnOff();   // Tắt LED P1.28
    }

    // --- 4. TEST DIMMER (Rte_Call_LightFadeIn / Rte_Call_LightFadeOut) ---
    // Sử dụng Joystick RIGHT (P1.26)
    static uint8_t last_right_sw = 1;
    uint8_t current_right_sw = GPIO_ReadPin(1, 26); // Đọc trực tiếp để test logic Dimmer

    if (current_right_sw == 0 && last_right_sw == 1) { 
        Rte_Call_LightFadeIn();  // LED P2.2 sáng dần
    } else if (current_right_sw == 1 && last_right_sw == 0) {
        Rte_Call_LightFadeOut(); // LED P2.2 tắt dần
    }
    last_right_sw = current_right_sw;
}

int main(void) {
    SystemInit();
    
    // KHỞI TẠO TẤT CẢ PHẦN CỨNG (TẦNG ECUAL)
    ECUAL_InitHardware();      // LED P2.3 & Switch P1.23
    ECUAL_Headlight_Init();    // LED P1.28
    ECUAL_Light_Init();        // LED P2.2 (PWM)
    ECUAL_LightSensor_Init();  // Sẽ đọc P1.25 thay vì ADC để test
    ECUAL_Wiper_Init();        // LED P1.29
    ECUAL_WiperSwitch_Init();  // Joystick P1.24

    // Cấu hình thêm P1.25 và P1.26 làm Input cho mục đích test
    GPIO_SetDir(1, 25, 0); 
    GPIO_SetDir(1, 26, 0);

    while(1) {
        App_BCM_FullIntegration_Task();

        // Delay chu kỳ để ổn định log và quan sát mắt thường
        for(volatile int i = 0; i < 1000000; i++);
    }
}