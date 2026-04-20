	#include "LPC17xx.h"
	#include "cmsis_os2.h"
	#include "uart.h"

	#include "Rte_Door.h"
	#include "Rte_Light.h"
	#include "Rte_Sensor.h"
	#include "Rte_Wiper.h"


	void Task_Door_Interior(void *argument) {
			uint8_t last_door = 0;
			UART0_SendString("[OS] Task Door Started\r\n");

			while(1) {
					uint8_t current_door = Rte_Read_DoorStatus();

					if (current_door != last_door) {
							if (current_door == 1) {
									UART0_SendString("[APP] Cua mo -> Fade In Den Tran\r\n");
									Rte_Call_LightFadeIn();
							} else {
									UART0_SendString("[APP] Cua dong -> Fade Out Den Tran\r\n");
									Rte_Call_LightFadeOut();
							}
							last_door = current_door;
					}
					osDelay(50);
			}
	}

	void Task_Auto_Headlight(void *argument) {
			uint8_t was_dark = 0; 
			UART0_SendString("[OS] Task Auto Headlight Started\r\n");

			while(1) {
					uint8_t is_dark = Rte_Read_IsEnvironmentDark();

					if (is_dark != was_dark) {
							if (is_dark == 1) {
									UART0_SendString("[APP] Troi toi -> BAT Den Pha!\r\n");
									Rte_Call_Headlight_TurnOn();
							} else {
									UART0_SendString("[APP] Troi sang -> TAT Den Pha!\r\n");
									Rte_Call_Headlight_TurnOff();
							}
							was_dark = is_dark; 
					}
					osDelay(100); 
			}
	}

	void Task_Wiper_Control(void *argument) {
			uint8_t last_switch_state = 0;
			UART0_SendString("[OS] Task Wiper Control Started\r\n");

			while(1) {
					uint8_t current_switch = Rte_Read_WiperSwitch();

					if (current_switch != last_switch_state) {
							if (current_switch == 1) {
									UART0_SendString("[APP] Gat mua: Che do Ngat quang (INT)\r\n");
									Rte_Call_Wiper_StartIntMode();
							} else {
									UART0_SendString("[APP] Gat mua: OFF\r\n");
									Rte_Call_Wiper_Stop();
							}
							last_switch_state = current_switch;
					}
					osDelay(100); 
			}
	}

	int main(void) {
			SystemInit();
			UART0_Init(115200);
			
			ECUAL_InitHardware();
			ECUAL_Light_Init();
			ECUAL_Headlight_Init();
			ECUAL_LightSensor_Init();
			ECUAL_Wiper_Init();
			ECUAL_WiperSwitch_Init();
			
osKernelInitialize();

			const osThreadAttr_t door_attr = { .name = "Door", .stack_size = 128 };
			const osThreadAttr_t hl_attr = { .name = "Headlight", .stack_size = 128 };
			const osThreadAttr_t wp_attr = { .name = "Wiper", .stack_size = 128 };

			osThreadNew(Task_Door_Interior, NULL, &door_attr);
			osThreadNew(Task_Auto_Headlight, NULL, &hl_attr);
			osThreadNew(Task_Wiper_Control, NULL, &wp_attr);
			osKernelStart();
			while(1) {}
	}