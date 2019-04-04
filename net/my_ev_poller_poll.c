#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"
#include "alloc.h"
#include "my_ev_poller.h"
#include "my_dispatcher.h"
static int init_event_buf_size=2;
static int extend_event_buf_size=4;
typedef struct _MyPollWrapper MyPollWrapper;
struct _MyPollWrapper{
	struct pollfd pollfd;
	MyDispatcher *dispatcher;
};
typedef struct _MyDispatcherWrapper MyDispatcherWrapper;
typedef struct _MyDispatchersHdr MyDispatchersHdr;
struct _MyDispatcherWrapper{
	TAILQ_ENTRY(_MyDispatcherWrapper) next;
	MyDispatcher *dispatcher;
};
TAILQ_HEAD(_MyDispatchersHdr, _MyDispatcherWrapper);
typedef struct _PollPoller PollPoller;
struct _PollPoller{
	int notifyfd;
	MyPollWrapper *events;
	MyDispatchersHdr h;
	int dispatcher_count;
    int events_count;
    int events_capacity;
    bool event_changed;
};
void my_dispatcher_insert(MyDispatchersHdr*h,MyDispatcherWrapper *ele){
	TAILQ_INSERT_TAIL(h,ele,next);
}
void my_dispatcher_remove(MyDispatchersHdr*h,MyDispatcherWrapper *ele){
	TAILQ_REMOVE(h,ele,next);
	TAILQ_NEXT(ele,next)=NULL;
}
MyPoller my_poller_create(void){
	PollPoller *poller=(PollPoller*)my_malloc(sizeof(PollPoller));
	memset(poller,0,sizeof(PollPoller));
	TAILQ_INIT(&poller->h);
	poller->events_capacity=init_event_buf_size;
	int len=poller->events_capacity;
	poller->events=(MyPollWrapper*)my_malloc(len*sizeof(MyPollWrapper));
	return poller;
}
void my_poller_destroy(MyPoller poller){
	PollPoller *self=(PollPoller*)poller;
	MyDispatcherWrapper *first=NULL;
	MyDispatchersHdr *h=&self->h;
	while((first=TAILQ_FIRST(h))!=NULL){
		my_dispatcher_remove(h,first);
		my_free(first);
	}
	my_free(self->events);
	my_free(self);
}
void my_poller_poll(MyPoller poller,my_ev_timeval *timeout){
	PollPoller *self=(PollPoller*)poller;
	if(self->dispatcher_count==0){
		return;
	}
	if(self->event_changed){
		MyDispatchersHdr *h=&self->h;
		MyDispatcherWrapper *dispatcher=NULL;
		if(self->events_capacity<self->dispatcher_count){
			int new_size=sizeof(MyPollWrapper)*(self->events_capacity+extend_event_buf_size);
			self->events=(MyPollWrapper*)my_realloc(self->events,new_size);
			memset(self->events,0,new_size);
			self->events_capacity=new_size;
		}
		int i=0;
		TAILQ_FOREACH(dispatcher,h,next){
			self->events[i].dispatcher=dispatcher->dispatcher;
			i++;
		int ff=dispatcher->dispatcher->request_event;
		if(ff&(MY_EV_READ|MY_EV_ACCEPT)){
			self->events[i].pollfd.events|=POLLIN;
		}
		if(ff&(MY_EV_WRITE|MY_EV_CONNECT)){
			self->events[i].pollfd.events|=POLLOUT;
		}
		printf("%d\n",i);
		}
		self->event_changed=false;
	}
}
void my_poller_modify(MyPoller poller,void *dispatcher,int op){
	PollPoller *self=(PollPoller*)poller;
	MyDispatcher *my_dis=(MyDispatcher*)dispatcher;
	MyDispatchersHdr *h=&self->h;
	switch(op){
	case MY_EV_ADD_OP:{
		MyDispatcherWrapper *wrapper=my_malloc(sizeof(MyDispatcherWrapper));
		wrapper->dispatcher=my_dis;
		my_dis->poll_plugin=wrapper;
		my_dispatcher_insert(h,wrapper);
		self->event_changed=true;
		self->dispatcher_count++;
		break;
	}
	case MY_EV_DEL_OP:{
		MyDispatcherWrapper *wrapper=(MyDispatcherWrapper*)my_dis->poll_plugin;
		wrapper->dispatcher=NULL;
		my_dispatcher_remove(h,wrapper);
		self->event_changed=true;
		self->dispatcher_count--;
		break;
	}
	case MY_EV_MOD_OP:{
		self->event_changed=true;
		break;
	}
	default:{
		break;
	}
	}
}
MyPollerInterface my_poller_impl={
.poller_create=my_poller_create,
.poller_destroy=my_poller_destroy,
.poller_poll=my_poller_poll,
.poller_modify=my_poller_modify,
};
