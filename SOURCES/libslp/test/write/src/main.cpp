/************************************
*
*此源文件
*filename : main.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2017年01月04日 星期三 14时22分42秒
*
************************************/
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <strings.h>
#include <libshelper/net.h>
#include <libshelper/log.h>

using namespace std;

int main(int argc,char** argv) 
{
	if (argc != 3) {
		slp::log::log::trace(time(NULL),__func__,"Usage:client <IP> <PORT>",slp::log::level::error);	
		return -1;
	} 

	printf("pid[%d]\n",getpid());
	int sockfd = 0;
	if (!slp::net::connect(argv[1],atoi(argv[2]),&sockfd)) return -2;
	char sendbuf[1024];
	while (true) {
		 printf("请输入要发送的命令:\n");
		 string cmd;
		 cin >> cmd;
		 snprintf(sendbuf,sizeof(sendbuf),"subscribe:[%s][%d]",cmd.data(),getpid());
		 write(sockfd,sendbuf,sizeof(sendbuf));	

		sleep(1);
	}
	if (sockfd) close(sockfd);

	return 0;
}
