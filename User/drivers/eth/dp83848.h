#ifndef _DP83848_H_
#define _DP83848_H_

#include "stm32f10x.h"
#include "stm32_eth.h"

#define PHY_ADDRESS             0x01  //DP83848��ַ�����ݺ��İ�Ӳ�����Ӿ���
#define LWIP_MAX_DHCP_TRIES		4     //DHCP������������Դ���

void InitEthernet(void);
void InitLwipCon(void);
void HandleLwipPeriodicEvent(void);

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

u16 getServerPort(void);
void setServerPort(u16 sp);

u16 getTcpLocalPort(void);
void setTcpLocalPort(u16 tlp);

u8* getServerIpAddr(void);
void setServerIpAddr(u8 *sia);
#endif

