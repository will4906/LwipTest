#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "stm32f10x.h"
#include "stm32_eth.h"
#include "tcp_impl.h"

#define CHECK_FOR_CONNECTION_PERIOD		20000					//连接检查时间周期（20秒）

void InitTcpClient(u16 local_port, u8 *server_ip, u16 server_port);
err_t TcpConnected(void *arg,struct tcp_pcb *pcb,err_t err);
void CloseTcp(struct tcp_pcb *pcb);
err_t OnTcpConnected(void *arg,struct tcp_pcb *pcb,err_t err);
err_t SendTcpDataAsClient(u8 *buff, u16 length);
err_t  ReceiveTcpDataAsClient(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err);
void OnTcpClientReceiveData(void *recvData);
void CheckForConnection(void);


#endif

