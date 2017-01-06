#include "ev.h"
#include "ev_epoll.h"
#include <stdlib.h>
#include <strings.h>

bool ev_init(event_base *eb,int size)
{
	do {
		eb = (event_base*)malloc(sizeof(event_base));
		if (!eb) break;

		bzero(eb,sizeof(event_base));
		eb->size = size;
		eb->maxfd = -1;
		eb->events = (file_event*)malloc(sizeof(file_event)*size);
		if (!eb->events) break;
		
		eb->fevents = (fired_event*)malloc(sizeof(fired_event)*size);
		if (!eb->fevents) break;

		eb->es = (epoll_state*)malloc(sizeof(epoll_state));
		if (!eb->es) break;

		return true;
	} while (0);

	if (eb) {
		free(eb->es);
		free(eb->fevents);
		free(eb->events);
		free(eb);	
	}
	return false;
}

bool ev_start(event_base *eb)
{
	bool is_success = ep_create(eb);
	return is_success;
}

bool ev_dispatch(event_base *eb)
{
	eb->stop = false;

	while (!eb->stop) {
		/*
		 *TODO 在此可以做些额外操作	
		 */

		ev_process_event(eb);
	}
	return true;
}


int ev_process_event(event_base *eb)
{
	int numevents = 0;	

	if (eb->maxfd <= -1) return 0;

	numevents = ep_wait(eb);
	for (int i=0; i<numevents; ++i) {
		fired_event *firedev = &eb->fevents[i];			
		file_event  *fe = &eb->events[firedev->fd];

		int mask = firedev->mask;
		int fd = firedev->fd;
		bool isreaded = false;
		if (firedev->mask & EV_READABLE) {
			fe->rcb(eb,fd,fe->data,mask);
			isreaded = true;
		}

		/*同一fd,同一次就绪，读和写回调相同则不执行*/
		if (firedev->mask & EV_WRITEABLE) {
			if (!isreaded || fe->rcb != fe->wcb) {
				fe->rcb(eb,fd,fe->data,mask);
			}
		}
	}

	return numevents;
}

void ev_stop(event_base *eb)
{
	if (!eb) return;
	eb->stop = true;
}

bool ev_addevent(event_base *eb,int fd, callback_func func, int mask, void *data)
{
	do {
		/*fd超出事件数组边界*/
		if (fd >= eb->size) break;
		if (!ep_add_event(eb,fd,mask)) break;

		file_event *fe = &eb->events[fd];
		if (mask & EV_READABLE) fe->rcb = func;
		if (mask & EV_WRITEABLE) fe->wcb = func;
		fe->mask = mask;
		fe->data = data;

		if (fd > eb->maxfd) {
			eb->maxfd = fd;
		}
		return true;
	} while (0);
	return false;
}

bool ev_delevent(event_base *eb, int fd, int mask)
{
	do {
		/*fd超出事件数组边界*/
		if (fd >= eb->size) break;			
		file_event *fe = &eb->events[fd];	
		/*没有注册监视事件*/
		if (fe->mask == EV_NONE) break;

		fe->mask = fe->mask & (~mask);	
		/*最大的fd删除了所有的监视事件,更新maxfd,全部删除则为-1*/
		if (eb->maxfd == fd && fe->mask == EV_NONE) {
			int j = 0;
			for (j = eb->maxfd-1; j >= 0; --j) {
				if (eb->events[j].mask != EV_NONE) break;	
			}
			eb->maxfd = j;
		}

		if (!ep_delete_event(eb,fd,mask)) break;

		return true;
	} while (0);
	return false;
}
