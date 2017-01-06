
#ifndef _SLP_EV_EPOLL_H
#define _SLP_EV_EPOLL_H
#include <sys/epoll.h>
#include "ev.h"

bool ep_create(event_base *eb);
int ep_wait(event_base *eb);
bool ep_add_event(event_base *eb, int fd, int mask);
bool ep_delete_event(event_base *eb, int fd, int mask);

#endif /*_SLP_EV_EPOLL_H*/
