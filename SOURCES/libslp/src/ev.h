/**
 * @file ev.h
 * @brief 定义了一些结构体，用于封装epoll的操作
 * @author sleeping
 * @version 1.0.0
 * @date 2017-01-05
 */

#ifndef _SLP_EV_H
#define _SLP_EV_H

#include <sys/epoll.h>

#define EV_NONE			0x0
#define	EV_READABLE		0x1
#define EV_WRITEABLE	0x10

struct event_base;

/**
 * @brief 用于可读时的回调函数原型
 *
 * @param 一些基本信息
 * @param fd 可读socket描述符
 * @param data 发送给client的数据
 * @param mask 可读掩码
 *
 * @return 无
 */
typedef void (*read_callback) (struct event_base* eb,int fd,void* data,int mask);

/**
 * @brief 用于可写时的回调函数原型
 *
 * @param 一些基本信息
 * @param fd 可写socket描述符
 * @param data 接收client发来的数据
 * @param mask 可写掩码
 *
 * @return 无
 */
typedef void (*write_callback) (struct event_base* eb,int fd,void* data,int mask);

/**
 * @brief 读写回调函数原型
 *
 * @param 一些基本信息
 * @param fd 可写socket描述符
 * @param data 接收client发来的数据
 * @param mask 可写掩码
 *
 * @return 无
 */
typedef void (*callback_func) (struct event_base* eb,int fd,void* data,int mask);
/**
 * @brief 事件对象
 * mask 读写掩码
 * rcb  读回调函数
 *
 * wcb  写回调函数
 * data 一些额外的数据信息
 */
typedef struct tag_file_event {
	int mask;
	read_callback  rcb;
	write_callback wcb;
	void* data;
} file_event;

/**
 * @brief 就绪事件对象
 * mask 事件掩码
 * fd 	就绪的socket描述符
 */
typedef struct tag_fired_event {
	int mask;
	int fd;
} fired_event;


/**
 * @brief 封装了epoll函数族需要使用的结构
 * epfd 由epoll_create返回
 * ee   就绪的事件信息数组
 */
typedef struct epoll_state {
	int epfd;
	struct epoll_event* ee;
} epoll_state;

typedef struct event_base {
	file_event* events;	
	fired_event* fevents;
	int size;
	int maxfd;
	epoll_state* es;
	bool stop;
} event_base;

/*
 *初始化并分配所需的内存
 */
bool ev_init(event_base **peb,int size);

/*
 *开始epoll_create
 */
bool ev_start(event_base *eb);
bool ev_dispatch(event_base *eb);
int	 ev_process_event(event_base *eb);
void ev_stop(event_base *eb);

bool ev_addevent(event_base *eb,int fd, callback_func func, int mask, void *data);
bool ev_delevent(event_base *eb, int fd, int mask);

#endif /*_SLP_EV_H*/
