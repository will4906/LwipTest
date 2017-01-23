#include "tcpclient.h"
#include "dp83848.h" 
#include "led.h"

u8 connectFlag = 0;                                    //连接状态  0：未连接   1：连接
struct tcp_pcb *tcp_client_pcb;                         //TCP客户端控制块

/*-------------------------------------------------*/
/*函数名：TCP客户端的初始化                        */
/*参  数：local_port:客户端端口号                  */
/*参  数：server_ip:务器IP                         */
/*参  数：server_port:服务器端口号                 */
/*返回值：无                                       */
/*-------------------------------------------------*/
void InitTcpClient(u16 local_port, u8 *server_ip, u16 server_port)
{
	struct ip_addr serverip;                                       //ip地址
	
	IP4_ADDR(&serverip,server_ip[0],server_ip[1],server_ip[2],server_ip[3]);
	
	tcp_client_pcb = tcp_new();                                    //建立TCP控制块
 	tcp_bind(tcp_client_pcb,IP_ADDR_ANY,local_port);               //绑定本地IP地址和端口号 
  tcp_connect(tcp_client_pcb,&serverip,server_port,TcpConnected);//注册连接上服务器的回调函数
}


/*-------------------------------------------------*/
/*函数名：关闭连接函数                             */
/*参  数：pcb：TCP控制块                           */
/*返回值：无                                       */
/*-------------------------------------------------*/
void CloseTcp(struct tcp_pcb *pcb)
{
	tcp_abort(pcb);        //关闭连接
	tcp_arg(pcb,NULL);     //移除回调函数 
	tcp_recv(pcb,NULL);    //移除回调函数 
	tcp_sent(pcb,NULL);    //移除回调函数 
	tcp_err(pcb,NULL);     //移除回调函数 
	tcp_poll(pcb,NULL,0);  //移除回调函数  
}

/*-------------------------------------------------*/
/*函数名：接上服务器的回调函数                     */
/*参  数：arg:需要传递的参数，不需要传就不用       */
/*参  数：pcb:TCP控制块                            */
/*参  数：err:错误值                               */
/*返回值：错误值                                   */
/*-------------------------------------------------*/
err_t TcpConnected(void *arg,struct tcp_pcb *pcb,err_t err)
{
	tcp_recv(pcb,ReceiveTcpDataAsClient);  //设置tcp接收回调函数
	return ERR_OK;                  //返回OK
}

/*-------------------------------------------------*/
/*函数名：TCP客户端发送数据函数                    */
/*参  数：buff:数据缓冲区                          */
/*参  数：length:数据长度区                        */
/*返回值：错误值                                   */
/*-------------------------------------------------*/
err_t SendTcpDataAsClient(u8 *buff, u16 length)					
{
	struct tcp_pcb *cpcb;   //TCP控制块
 	err_t err;              //错误值
	u16 tcpLocalPort = getTcpLocalPort();
	
	connectFlag = 0;       //连接状态  0：未连接
	for(cpcb = tcp_active_pcbs; cpcb != NULL; cpcb = cpcb->next)                    //轮询TCP活动列表
	{
		if(cpcb->local_port == tcpLocalPort && cpcb->remote_port == getServerPort())  //如果TCP_LOCAL_PORT端口指定的连接没有断开
		{
			connectFlag = 1;  						//连接标志
			break;							   	
		}
	}
	if(connectFlag == 0)  							                   // TCP_LOCAL_PORT指定的端口未连接或已断开
	{
		CloseTcp(tcp_client_pcb);                                     //关闭连接
		InitTcpClient(tcpLocalPort,getServerIpAddr(),getServerPort());         //重新连接
	}
	if(connectFlag == 1)                               //连接正常
	{
		err = tcp_write(tcp_client_pcb,buff,length,1);	//发送数据
	}
	return err;   			
}

/*-------------------------------------------------*/
/*函数名：TCP接收回调函数                          */
/*参  数：arg:传递来的参数                         */
/*参  数：pcb:TCP控制块                            */
/*参  数：p:数据缓存指针                           */
/*参  数：err:错误值                               */
/*返回值：错误值                                   */
/*-------------------------------------------------*/
err_t  ReceiveTcpDataAsClient(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
	if(p != NULL)                                   //数据缓存不为空指针
	{
		tcp_recved(pcb, p->tot_len);				//获取数据长度 tot_len
		tcp_write(pcb,p->payload,p->tot_len,0);     //将数据原样发回
		pbuf_free(p); 			                    //释放指针				    
	}
	else	 										//数据缓存为空，服务器断开连接了，则客户端也应断开
	{
		tcp_close(pcb);                             //断开连接 						
	}
	return ERR_OK;	
}



