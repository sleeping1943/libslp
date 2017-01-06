#include "net.h"
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include "textcolor.h"

namespace slp{namespace net{

    /**
    * @brief 为指定的ip和port建立连接
    *
    * @param ip    主机地址
    * @param port  主机端口
    * @param fd    连接描述符
    *
    * @return  成功：true,失败：false
    */
    bool connect(char* ip,short port,int* fd){
        int sockfd = 0,connfd = 0;
        struct sockaddr_in addr;
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;
        if(::inet_pton(AF_INET,ip,&addr.sin_addr) <= 0) {
            /* perror("inet_pton:"); */
            return false;
        }
    
        sockfd = ::socket(AF_INET,SOCK_STREAM,0);
        if (!sockfd) {
            /* perror("socket:"); */
            return false;
        }

        connfd = ::connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
        if (connfd < 0) {
            /* perror("connect:"); */
            return false;
        }

        *fd = sockfd;
        return true;
    }
    
     
    /**
     * @brief 具有超时限制的写操作
     *
     * @param fd    有效的socket描述符
     * @param content   用于待发送数据的缓冲区
     * @param size  缓冲区大小
     * @param time  超时时间
     *
     * @return  成功:true,失败:false
     */
    bool try_write(int fd,void *content,size_t size,int time,int *ret) {
        pollfd events;
        events.fd = fd;
        events.events = POLLOUT | POLLERR | POLLHUP | POLLNVAL;

        int errnum = ::poll(&events,1,time);  /* 3秒超时 */
        if (errnum <= 0) {
            /* perror("try_write[poll]:"); */
            return false;
        }else if (errnum == 0) { 
            *ret = errnum;
            return false;
        }else if (events.revents & (POLLERR | POLLHUP | POLLNVAL)) { 
            *ret = -1;
            return false; 
        }
        if (events.revents & POLLOUT) {
            *ret = ::write(fd,content,size);
        }
        return true;
    }
    
    /**
     * @brief 具有超时限制的读操作
     *
     * @param fd    有效的socket描述符
     * @param content   用于接受数据的缓冲区
     * @param size  接受缓冲区大小
     * @param time  超时时间
     * @param ret   错误码
     *
     * @return  成功:true,失败:false
     */
    bool try_read(int fd,void *content,size_t size,int time,int *ret) {
        pollfd events;
        events.fd = fd;
        events.events = POLLIN | POLLERR | POLLHUP | POLLNVAL;
        int errnum = ::poll(&events,1,time);
        if (errnum < 0) {
            /* perror("try_read[poll]:"); */
            return false;
        }else if (errnum == 0) { 
            *ret = errnum;
            return false;
        }else if (events.revents & (POLLERR | POLLHUP | POLLNVAL)) { 
            *ret = -1;
            return false; 
        }

        if (events.revents & POLLIN){   /* 是否有数据可读,3秒超时 */
            *ret = ::read(events.fd,content,size*sizeof(char));
        }
        /* std::cout << slp::YELLOW << "tre_read_true..." << slp::NONE << std::endl; */
        return true;
    }

    bool isalive (int fd) {

        if (fd == 0)return false;
        pollfd events;
        events.fd = fd;
        events.events = POLLOUT;
        events.revents = 0;
        int errnum = ::poll(&events,1,200);
        if (errnum > 0) {
            if (events.revents & POLLRDHUP) {
                std::cout << slp::YELLOW << "POLLRDHUP--isalive:true..." << slp::NONE << std::endl;
                return false;
            }
            if (events.revents & (POLLERR | POLLHUP | POLLNVAL)) {
                ::close(fd);
                return false;
            }
            if (events.revents & POLLOUT) {
                std::cout << slp::RED << "isalive:true..." << slp::NONE << std::endl;
                return true;
            }
        }
        std::cout << slp::YELLOW << "isalive:false..." << slp::NONE << std::endl;
        return false;
    }


	bool get_socket_name(int fd, char *ip, short *port)
	{
	    struct sockaddr_in sa;
		socklen_t salen = sizeof(sa);

		if (getsockname(fd,(struct sockaddr*)&sa,&salen) == -1) {
			*port = 0;
			ip[0] = '?';
			ip[1] = '\0';
			return false;
		}
		if (ip) strcpy(ip,inet_ntoa(sa.sin_addr));
		if (port) *port = ntohs(sa.sin_port);
		return true;
	}

	bool get_peer_name(int fd, char *ip, short *port)
	{
		struct sockaddr_in sa;
		socklen_t salen = sizeof(sa);

		if (getpeername(fd,(struct sockaddr*)&sa,&salen) == -1) {
			*port = 0;
			ip[0] = '?';
			ip[1] = '\0';
			return false;
		}
		if (ip) strcpy(ip,inet_ntoa(sa.sin_addr));
		if (port) *port = ntohs(sa.sin_port);
		return true;
	}


	bool setsocknonblock(int fd, char *err)
	{
	    int flags;

		/* Note that fcntl(2) for F_GETFL and F_SETFL can't be
		 * interrupted by a signal. */
		if ((flags = fcntl(fd, F_GETFL)) == -1) {
			snprintf(err,ERROR_LEN-1,"fcntl(F_GETFL): %s", strerror(errno));
			return false;
		}
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
			snprintf(err,ERROR_LEN-1,"fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno));
			return false;
		}
		return true;
	}


	bool create_socket(int *pfd, char *err)
	{
	    int on = 1;
		if ((*pfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			snprintf(err,ERROR_LEN-1,"creating socket: %s", strerror(errno));
			return false;
		}

		if (setsockopt(*pfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
			snprintf(err,ERROR_LEN-1,"setsockopt SO_REUSEADDR: %s", strerror(errno));
			return false;
		}
		return true;
	}

	bool _listen(int fd, struct sockaddr *sa, socklen_t len, char *err)
	{
	    if (bind(fd,sa,len) == -1) {
			snprintf(err,ERROR_LEN-1,"bind: %s", strerror(errno));
			close(fd);
			return false;
		}

		/* Use a backlog of 512 entries. We pass 511 to the listen() call because
		* the kernel does: backlogsize = roundup_pow_of_two(backlogsize + 1);
		* which will thus give us a backlog of 512 entries */
		if (listen(fd, 511) == -1) {
			snprintf(err,ERROR_LEN-1,"listen: %s", strerror(errno));
			close(fd);
			return false;
		}
		return true;

	}

	bool create_tcp_server(int *pfd, char *ip, short port, char *err)
	{
		struct sockaddr_in sa;

		if (!create_socket(pfd,err)) return false;

		memset(&sa,0,sizeof(sa));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(port);
		sa.sin_addr.s_addr = htonl(INADDR_ANY);
		if (ip && inet_aton(ip, &sa.sin_addr) == 0) {
			snprintf(err,ERROR_LEN-1,"invalid bind address");
			close(*pfd);
			return false;
		}
		if (!_listen(*pfd,(struct sockaddr*)&sa,sizeof(sa),err)) return false;

		return true;
	}
}};
