#include "stm32f10x.h"
#include "stm32_eth.h"
#include "delay.h"
#include "TotalTimer.h"
#include "led.h"
#include "Uart.h"
#include "dp83848.h"
#include "tcpclient.h"
#include <string.h>

u32 w_buff[512] = {1,2,3,4,5,6,7,8,9};   
u32 r_buff[512];   

int main()
{
	u8 data[50];
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
		if(ReadUartData(UART_PORT_COM2,data))
		{
			SendTcpDataAsClient(data, strlen((char*)data));
		}
		//DisableAllLed();
		HandleLwipPeriodicEvent();
	}
}
