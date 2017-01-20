#include "stm32f10x.h"
#include "stm32_eth.h"
#include "delay.h"
#include "TotalTimer.h"
#include "led.h"
#include "Uart.h"
#include "dp83848.h"

int main()
{
	u8 data[] = "hello";
	
	delay_init();
	//定时器时间设置为10ms
	InitTimerCon();
	InitUartCon();
	LED_Init();
	InitEthernet();
	
	while(1)
	{
		EnableAllLed();
		delay_ms(1000);
		if(ReadUartData(UART_PORT_COM2,data))
		{
			SendUartData(UART_PORT_COM2,data,5);
		}
		DisableAllLed();
		delay_ms(500);
	}
}
