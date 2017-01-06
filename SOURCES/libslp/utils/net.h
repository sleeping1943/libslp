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


#ifndef ERROR_LEN
	#define ERROR_LEN 1024
#endif

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


	/**
	 * @brief 获取本地协议的ip和port
	 *
	 * @param fd 已建立浩的连接描述符
	 * @param ip 返回参数，解析后的ip地址
	 * @param port 返回参数，解析后的port端口
	 *
	 * @return true 成功 false 失败
	 */
	bool get_socket_name(int fd, char *ip, short *port);


	/**
	 * @brief 获取远程协议的ip和port
	 *
	 * @param fd 已建立好的连接描述符
	 * @param ip 返回参数,解析后的ip地址
	 * @param port 返回参数，解析后的port端口
	 *
	 * @return  true 成功 false 失败
	 */
	bool get_peer_name(int fd, char *ip, short *port);


	/**
	 * @brief 设置给定描述符为非阻塞
	 *
	 * @param fd 有效的描述符
	 * @param err 出错信息
	 *
	 * @return  true 成功 false 失败
	 */
	bool setsocknonblock(int fd, char *err);

	/**
	 * @brief 创建新的socket,并设置地址重用
	 *
	 * @param pfd 返回参数，创建成功返回的socket描述符
	 * @param err 出错信息
	 *
	 * @return  true 成功 false 失败
	 */
	bool create_socket(int *pfd, char *err);


	/**
	 * @brief 绑定，监听指定的地址和端口
	 *
	 * @param fd 有效的socketfd
	 * @param sa 有效的socket地址
	 * @param len sa的地址内存长度
	 * @param err 出错信息
	 *
	 * @return true 成功 false 失败
	 */
	bool _listen(int fd, struct sockaddr *sa, socklen_t len, char *err);


	/**
	 * @brief 创建服务器socket并监听
	 *
	 * @param pfd 服务器socketfd
	 * @param ip  服务器地址
	 * @param port 服务器端口
	 * @param err 出错信息
	 *
	 * @return  true 成功 false 失败
	 */
	bool create_tcp_server(int *pfd, char *ip, short port, char *err);
}};
#endif /* _LIBSLP_H */
