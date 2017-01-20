
#include <unistd.h>
#include <stdio.h>
#include <libslp/net.h>
#include <libslp/ev.h>

void _accept(event_base *eb, int fd, void *data, int mask);
void onread(event_base *eb, int fd, void *data, int mask);

event_base *eb;

int main (int , char **argv)
{
	printf("progromma\'name is %s\n",argv[0]);
	int sockfd = 0;
	char err[ERROR_LEN] = {0};
	if (!slp::net::create_tcp_server(&sockfd,(char*)"127.0.0.1",4444,err)) {
		printf("%s:%s\n",__func__,err);
		return -1;
	}

	if (!ev_init(&eb,1024*10)) {
		printf("in ev_init()\n");
		return -1;
	}
	if (!ev_start(eb)) {
		printf("in ev_start()\n");
		return -2;
	}
	if (!ev_addevent(eb,sockfd,_accept,EV_READABLE,NULL)) {
		printf("in ev_addevent()\n");
		return -3;
	}

	printf("before dispatch!\n");
	ev_dispatch(eb);
	printf("after dispatch!\n");

	ev_stop(eb);
#if 0
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
#endif
	return 0;
}




void _accept(event_base *eb, int fd, void*, int)
{
	int connfd = ::accept(fd,NULL,NULL);
	if (connfd <= -1) {
		printf("accept error!\n");
		return;
	}
	if (!ev_addevent(eb,connfd,onread,EV_READABLE,NULL)) return;
}


void onread(event_base *eb, int fd, void *, int mask)
{
	char buf[1024] = {0};
	int len = ::read(fd, buf, sizeof(buf));	
	if (len <= 0) {
		printf("read error!len =%d\n",len);	
		ev_delevent(eb,fd,mask);
		close(fd);
		return;
	}
	printf("recive string from client:%s len=%d\n",buf,len);
}
