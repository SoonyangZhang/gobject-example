#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "uthash.h"
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
struct _MyDispatcherWrapper{
	MyDispatcher *dispatcher_ref;
	UT_hash_handle hh_id;
};
typedef struct _PollPoller PollPoller;
struct _PollPoller{
	int notifyfd;
	MyPollWrapper *events;
	MyDispatcherWrapper *h;
	MyDispatcherWrapper *free_h;
	int dispatcher_count;
    int events_count;
    int events_capacity;
    bool event_changed;
};
int my_poll_monitor_insert(PollPoller*context,MyDispatcher *ele){
	MyDispatcherWrapper *found=NULL;
	int ret=-1;
	HASH_FIND(hh_id,context->h,&ele,sizeof(MyDispatcher*),found);
	if(!found){
		MyDispatcherWrapper *wrapper=(MyDispatcherWrapper*)my_malloc(sizeof(MyDispatcherWrapper));
		wrapper->dispatcher_ref=my_object_ref(ele);
		HASH_ADD_KEYPTR(hh_id,context->h,&ele,sizeof(MyDispatcher*),wrapper);
		ret=0;
	}
	return ret;
}
int my_poll_monitor_remove(PollPoller*context,MyDispatcher *ele){
	MyDispatcherWrapper *found=NULL;
	int ret=-1;
	HASH_FIND(hh_id,context->h,&ele,sizeof(MyDispatcher*),found);
	if(found){
		HASH_DELETE(hh_id,context->h,found);
		HASH_ADD_KEYPTR(hh_id,context->free_h,&ele,sizeof(MyDispatcher*),found);
		ret=0;
	}
	return ret;
}
void my_poller_free_h_dispose(PollPoller*self){
	MyDispatcherWrapper *itor=NULL;
	MyDispatcherWrapper *itor_tmp=NULL;
	HASH_ITER(hh_id,self->free_h,itor,itor_tmp){
		HASH_DELETE(hh_id,self->free_h,itor);
		my_object_unref(itor->dispatcher_ref);
		itor->dispatcher_ref=NULL;
		my_free(itor);
	}
}
MyPoller my_poller_create(void){
	PollPoller *poller=(PollPoller*)my_malloc(sizeof(PollPoller));
	memset(poller,0,sizeof(PollPoller));
	poller->events_capacity=init_event_buf_size;
	int len=poller->events_capacity;
	poller->events=(MyPollWrapper*)my_malloc(len*sizeof(MyPollWrapper));
	return poller;
}
void my_poller_destroy(MyPoller poller){
	PollPoller *self=(PollPoller*)poller;
	MyDispatcherWrapper *itor=NULL;
	MyDispatcherWrapper *itor_tmp=NULL;
	HASH_ITER(hh_id,self->h,itor,itor_tmp){
		my_poll_monitor_remove(self,itor);
	}
	my_poller_free_h_dispose(self);
	my_free(self->events);
	my_free(self);
}
void my_poller_poll(MyPoller poller,my_ev_timeval *timeout){
	PollPoller *self=(PollPoller*)poller;
	if(self->dispatcher_count==0){
		return;
	}
	my_poller_free_h_dispose(self);
	if(self->event_changed){
		if(self->events_capacity<self->dispatcher_count){
			int new_size=sizeof(MyPollWrapper)*(self->events_capacity+extend_event_buf_size);
			self->events=(MyPollWrapper*)my_realloc(self->events,new_size);
			memset(self->events,0,new_size);
			self->events_capacity=new_size;
		}
		int i=0;
		MyDispatcherWrapper *itor=NULL;
		MyDispatcherWrapper *itor_tmp=NULL;
		HASH_ITER(hh_id,self->h,itor,itor_tmp){
			self->events[i].dispatcher=itor->dispatcher_ref;
			i++;
		int ff=itor->dispatcher_ref->request_event;
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
	int status=0;
	switch(op){
	case MY_EV_ADD_OP:{
		status=my_poll_monitor_insert(self,dispatcher);
		if(status==0){
			self->event_changed=true;
			self->dispatcher_count++;
		}
		break;
	}
	case MY_EV_DEL_OP:{
		status=my_poll_monitor_remove(self,dispatcher);
		if(status==0){
			self->event_changed=true;
			self->dispatcher_count--;
		}
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
