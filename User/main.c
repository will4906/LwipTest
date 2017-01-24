#include "stm32f10x.h"
#include "stm32_eth.h"
#include "delay.h"
#include "TotalTimer.h"
#include "led.h"
#include "Uart.h"
#include "dp83848.h"
#include "tcpclient.h"

int main()
{
	u8 data[] = "hello";
	
	delay_init();
	//定时器时间设置为10ms
	InitTimerCon();
	InitUartCon();
	InitLedCon();
	InitEthernet();
	InitLwipCon();
	InitTcpClient(getTcpLocalPort(), getServerIpAddr(), getServerPort());
	while(1)
	{
		//EnableAllLed();
		/*if(ReadUartData(UART_PORT_COM2,data))
		{
			SendUartData(UART_PORT_COM2,data,5);
		}*/
		//DisableAllLed();
		HandleLwipPeriodicEvent();
	}
}
