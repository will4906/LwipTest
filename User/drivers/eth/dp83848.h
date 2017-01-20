#ifndef _DP83848_H_
#define _DP83848_H_

#include "stm32f10x.h"
#include "stm32_eth.h"

#define PHY_ADDRESS             0x01  //DP83848地址，根据核心板硬件连接决定
#define LWIP_MAX_DHCP_TRIES		4     //DHCP服务器最大重试次数

/*---------静态的IP地址---------*/
#define STATIC_IP1     192
#define STATIC_IP2     168
#define STATIC_IP3     0
#define STATIC_IP4     30
/*----------子网掩码------------*/
#define STATIC_MASK1   255
#define STATIC_MASK2   255
#define STATIC_MASK3   255
#define STATIC_MASK4   0
/*------------网关-------------*/
#define STATIC_GW1     192
#define STATIC_GW2     168
#define STATIC_GW3     0
#define STATIC_GW4     1

void InitEthernet(void);

#endif

