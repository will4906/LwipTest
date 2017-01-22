#include "dp83848.h"

/*********************************************************************************************************
*																								��������
**********************************************************************************************************/
u32 LwipTime = 0;                 //LWip����ʱ��

/*********************************************************************************************************
*                                              ��̬��������
*********************************************************************************************************/
static void GPIO_Configuration(void);
static void NVIC_Configuration(void);
static void Ethernet_Configuration(void);

/*********************************************************************************************************
*����������ʼ����̫��
*������  ��
*����ֵ����
**********************************************************************************************************/
void InitEthernet(void)
{
	GPIO_Configuration();
	NVIC_Configuration();
	Ethernet_Configuration();
}

/*-------------------------------------------------*/
/*����������̫���ӿ�����                           */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //���ļ����ڳ�ʼ��GPIO�õ��Ľṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	//����PA2  �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//����PC1  �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//����PB11 PB12 PB13 �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//�ı�RX_DV RXD0��RXD1��ӳ�� 
	GPIO_PinRemapConfig(GPIO_Remap_ETH, ENABLE);

	//����PA0 PA1 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//����PB10 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	//����PD8 PD9 PD10 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	//����PA8 �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*-------------------------------------------------*/
/*����������̫���ж�����                           */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;            //���ļ��ڣ�NVIC�ṹ��

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);     //�⺯���������������λ�ú�ƫ�ƣ���������������FLASH������ƫ�ơ�

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //�⺯�����������ȼ����飺��ռ���ȼ��ʹ����ȼ�
													//NVIC_PriorityGroup_2����ռ���ȼ�2λ �����ȼ�2λ

	NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;           //�����ж�ͨ��=��̫���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//������ռ���ȼ�=2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //���ô����ȼ�=0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);                          //�⺯��������NVIC_InitStructure�ṹ���ڵĲ�����ʼ��NVIC�Ĵ���
}

/*-------------------------------------------------*/
/*����������̫������                               */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
static void Ethernet_Configuration(void)
{ 
	ETH_InitTypeDef ETH_InitStructure;  //���ļ�����ʼ����̫���õ��Ľṹ��

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ETH_MAC | RCC_AHBPeriph_ETH_MAC_Tx | RCC_AHBPeriph_ETH_MAC_Rx, ENABLE);	 
		
	GPIO_ETH_MediaInterfaceConfig(GPIO_ETH_MediaInterface_RMII);//�ú���������̫���ӿ�ΪRMII

	//����˼·����PLL3ʱ��ΪMCO�ṩRMII��Ҫ��50Mʱ��
	//ϵͳ��ʼ��STM32��ʱ��Ϊ72M��ʱ��PLL3������Ϊ���ⲿ25M����5��Ƶ 25/5=5M
	RCC_PLL3Config(RCC_PLL3Mul_10);//PLL3��Ƶ10�� 5*10=50M

	RCC_PLL3Cmd(ENABLE);//ʹ��PLL3ʱ��

	while (RCC_GetFlagStatus(RCC_FLAG_PLL3RDY) == RESET)//�ȴ�PLL3ʹ�ܳɹ�
	{}
	  
	RCC_MCOConfig(RCC_MCO_PLL3CLK);//ѡ��MCO��ʱ��ԴΪPLL3

	ETH_DeInit();       //��λ��̫������Ĵ�����Ĭ��ֵ����ʹ�ܣ��ڽ�ֹ���ѻָ�Ĭ��ֵ

	ETH_SoftwareReset();//�����λ��ͨ������ETH->DMABMR�Ĵ�����λ0ʵ��

	while (ETH_GetSoftwareResetStatus() == SET);//�ȴ���λ�ɹ�

	ETH_StructInit(&ETH_InitStructure);//��ʼ���ṹ��ETH_InitStructure������ԱΪĬ��ֵ

	//ETH_InitStructure�ṹ���ڳ�Ա�϶࣬�����Ĭ��ֵ���޸�һЩ�ؼ���Ա������Ӧ��ǰ����Ҫ
	ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;   			//������������Ӧ����
	ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;					//�رշ���
	ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable; 		//�ر��ش�����
	ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable; 	//�ر��Զ�ȥ��PDA/CRC���� 
	ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;						//�رս������е�֡
	ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;//����������й㲥֡
	ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;			//�رջ��ģʽ�ĵ�ַ����  
	ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;//�����鲥��ַʹ��������ַ����   
	ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;	//�Ե�����ַʹ��������ַ���� 
    
	#if  !CHECKSUM_GEN_ICMP    //�ж��Ƿ���Ӳ��У��,�ر����У��
	ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable; 			//����ipv4��TCP/UDP/ICMP��֡У���ж��   
	#endif
	
	//������ʹ��֡У���ж�ع��ܵ�ʱ��һ��Ҫʹ�ܴ洢ת��ģʽ,�洢ת��ģʽ��Ҫ��֤����֡�洢��FIFO��,
	//����MAC�ܲ���/ʶ���֡У��ֵ,����У����ȷ��ʱ��DMA�Ϳ��Դ���֡,����Ͷ�������֡
	ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable; //��������TCP/IP����֡
	ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;     //�����������ݵĴ洢ת��ģʽ    
	ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;   //�����������ݵĴ洢ת��ģʽ  

	ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;     	//��ֹת������֡  
	ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;	//��ת����С�ĺ�֡ 
	ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Enable;  		//�򿪴���ڶ�֡����
	ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;  	//����DMA����ĵ�ַ���빦��
	ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;            			//�����̶�ͻ������    
	ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;     		//DMA���͵����ͻ������Ϊ32������   
	ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;			//DMA���յ����ͻ������Ϊ32������
	ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_2_1;
	ETH_Init(&ETH_InitStructure,PHY_ADDRESS);		        //����ETH

	ETH_DMAITConfig(ETH_DMA_IT_NIS|ETH_DMA_IT_R,ENABLE);  	//ʹ����̫�������ж�	
}
