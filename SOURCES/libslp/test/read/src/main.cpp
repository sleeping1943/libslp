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
#include <libslp/net.h>
#include <libslp/log.h>

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
	/*char sendbuf[1024];*/
	while (true) {
		char buf[1024];
		bzero(buf,sizeof(buf));
		int read_len = read(sockfd,buf,sizeof(buf));
		switch (read_len) {
		case 0:
			printf("socket连接断开!\n");
			break;
		case -1:
			printf("socket读错误!\n");
			break;
		default:
			break;
		}
		if (read_len <= 0) break;
		printf("\033[32mthe string from server is:\033[31m%s\033[m\n",buf);
		sleep(1);
	}
	if (sockfd) close(sockfd);

	return 0;
}
