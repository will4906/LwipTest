#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                                   //����һ��IO�˿ڲ����ṹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD , ENABLE);  			   //ʹ��PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;//��ʼ��PD12.13.14�˿�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      //����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   					   //���������ʽ
	GPIO_Init(GPIOD, &GPIO_InitStructure);            					   //��ʼ��PD12.13.14
	
	DisableAllLed();
}

/*-------------------------------------------------*/
/*����������������LED                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void EnableAllLed(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
}
/*-------------------------------------------------*/
/*��������Ϩ������LED                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void DisableAllLed(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
}

