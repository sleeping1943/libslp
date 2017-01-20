#include "ev_epoll.h"
#include <stdlib.h>
#include <strings.h>

bool ep_create(event_base *eb)
{
	do {
		if (!eb) break;

		eb->es->ee = (epoll_event*)malloc(sizeof(epoll_event)*eb->size);
		if (!eb->es->ee) break;

		eb->es->epfd = epoll_create(1024);	/*1024 用于暗示内核*/
		if (eb->es->epfd == -1) break;

		return true;
	} while (0);

	if (eb)  free(eb->es->ee);

	return false;
}

int ep_wait(event_base *eb)
{
	do {
		int ret = 0;
		epoll_state *es = eb->es;
		ret = epoll_wait(es->epfd,es->ee,eb->size,-1);	
		if (ret > 0) {
			int j = 0;
			int numevents = ret;
			/*拷贝就绪事件到epoll_event的firedevent就绪数组中*/
			for (; j < numevents; ++j) {
				struct epoll_event* ee = es->ee+j;			

				int mask = EV_NONE;
				if (ee->events & EPOLLIN) mask |= EV_READABLE;
				if (ee->events & EPOLLOUT) mask |= EV_WRITEABLE;
				if (ee->events & EPOLLERR) mask |= EV_WRITEABLE;
				if (ee->events & EPOLLHUP) mask |= EV_WRITEABLE;

				eb->fevents[j].fd = ee->data.fd;
				eb->fevents[j].mask = mask;
			}
		}

		return ret;
	} while (0);

	return 0;
}
 
bool ep_add_event(event_base *eb, int fd, int mask)
{
	do {
		if (!eb || !eb->es) break;

		/*若已注册过事件，则修改，否则添加*/
		int op= (eb->events[fd].mask == EV_NONE ? EPOLL_CTL_ADD : EPOLL_CTL_MOD);
		epoll_state *es = eb->es;

		struct epoll_event ee;
		bzero(&ee,sizeof(ee));
		ee.events = EV_NONE;

		mask |= eb->events[fd].mask;	/*合并老的监视事件*/
		if (mask & EV_READABLE) ee.events |= EPOLLIN;
		if (mask & EV_WRITEABLE) ee.events |= EPOLLOUT;

		ee.data.u32 = 0;
		ee.data.u64 = 0;
		ee.data.fd = fd;
		if (epoll_ctl(es->epfd,op,fd,&ee) == -1) break;

		return true;
	} while (0);

	return false;
}

bool ep_delete_event(event_base *eb, int fd, int mask)
{
	do {
		if (!eb || !eb->es)	break;

		int op = EPOLL_CTL_DEL;
		/*若删除的监视掩码和现在的一样，则删除，否则为修改*/
		if (eb->events[fd].mask & (~mask)) {
			op = EPOLL_CTL_MOD;
		}

		struct epoll_event ee;
		ee.events = 0;

		if (mask & EV_READABLE) ee.events |= EPOLLIN;
		if (mask & EV_WRITEABLE) ee.events |= EPOLLOUT;

		ee.data.u32 = 0;
		ee.data.u64 = 0;
		ee.data.fd = fd;
		
		if (epoll_ctl(eb->es->epfd,op,fd,&ee)) break;
		return true;
	} while (0);

	return false;
}
