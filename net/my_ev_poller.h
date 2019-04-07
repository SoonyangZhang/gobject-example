#ifndef MY_EV_POLLER_H_
#define MY_EV_POLLER_H_
#include "my_ev_defines.h"
typedef void  MyPoller;
typedef struct _MyPollerInterface MyPollerInterface;
struct _MyPollerInterface{
	MyPoller* (*poller_create)(void);
	void (*poller_destroy)(MyPoller* poller);
	void (*poller_poll)(MyPoller* poller,int timeout_ms);
	void (*poller_modify)(MyPoller* poller,void *dispatcher,int op);
	void (*poller_notify)(MyPoller* poller);
};
MyPollerInterface *my_get_poller_impl();
#endif /* MY_EV_POLLER_H_ */
