/**
 * @file net.h
 * @brief 此头文件存放一些网络函数 
 * @author sleeping
 * @version 1.0.1
 * @email csleeping@163.com
 * @date 2016-07-04
 */
#ifndef _LIBSLP_H
#define _LIBSLP_H
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>



/**
 * @brief 网络工具类命名空间
 */
namespace slp{namespace net{

    /**
    * @brief 为指定的ip和port建立连接
    *
    * @param ip 主机地址
    * @param port 主机端口
    * @param fd 连接描述符
    *
    * @return 成功：true,失败：false
    */
    bool connect(char* ip,short port,int* fd);

     /**
     * @brief 具有超时限制的写操作
     *
     * @param fd 有效的socket描述符
     * @param content 发送数据的缓冲区
     * @param size 缓冲区大小
     * @param time 超时时间
     * @param ret 错误码
     *
     * @return 成功:true,失败:false
     */
    bool try_write(int fd,void *content,size_t size,int time,int *ret);
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
    bool try_read(int fd,void *content,size_t size,int time,int *ret);

    /**
     * @brief   检测socket连接是否存活
     *
     * @param fd socket连接描述符
     *
     * @return true：连接正常，false:连接断开
     */
    bool isalive (int fd);
}};
#endif /* _LIBSLP_H */
