#ifndef _DP83848_H_
#define _DP83848_H_

#include "stm32f10x.h"
#include "stm32_eth.h"

#define PHY_ADDRESS             0x01  //DP83848地址，根据核心板硬件连接决定
#define LWIP_MAX_DHCP_TRIES		4     //DHCP服务器最大重试次数

void InitEthernet(void);
void InitLwipCon(void);

u32 getLwipTime(void);
void setLwipTime(u32 lt);

u8* getMacAddr(void);
void setMacAddr(u8 ma[]);

char* getHostName(void);
void setHostName(char *hn);

unsigned char* getIpAddr(void);
void setIpAddr(unsigned char *ia);

unsigned char* getSubnetMask(void);
void setSubnetMask(unsigned char* sm);

unsigned char* getGateway(void);
void setGateway(unsigned char* gw);
#endif

