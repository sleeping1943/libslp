#include "net.h"
#include <poll.h>
#include <unistd.h>

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
            perror("inet_pton:");
            return false;
        }
    
        sockfd = ::socket(AF_INET,SOCK_STREAM,0);
        if (!sockfd) {
            perror("socket:");
            return false;
        }

        connfd = ::connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
        if (connfd < 0) {
            perror("connect:");
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
            perror("try_write[poll]:");
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
            perror("try_read[poll]:");
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
        std::cout << slp::YELLOW << "tre_read_true..." << slp::NONE << std::endl;
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
}};
