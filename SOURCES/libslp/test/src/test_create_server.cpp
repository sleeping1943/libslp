
#include <unistd.h>
#include <stdio.h>
#include <libslp/net.h>

int main (int , char **argv)
{
	printf("progromma\'name is %s\n",argv[0]);
	int sockfd = 0;
	char err[ERROR_LEN] = {0};
	if (!slp::net::create_tcp_server(&sockfd,(char*)"127.0.0.1",4444,err)) {
		printf("%s:%s\n",__func__,err);
		return -1;
	}

	int connfd = ::accept(sockfd,NULL,NULL);
	if (connfd <= -1) {
		printf("accept error!\n");
		return -1;
	}

	while (true) {
		char buf[1024] = {0};
		int len = ::read(connfd, buf, sizeof(buf));	
		if (len <= 0) {
			printf("read error!len =%d\n",len);	
			return -2;
		}
		printf("recive string from client:%s len=%d\n",buf,len);
	}
	return 0;
}
