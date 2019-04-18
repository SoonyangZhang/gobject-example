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
/* that seems cause some bug
typedef struct _MyPollWrapper MyPollWrapper;
struct _MyPollWrapper{
	struct pollfd pollfd;
	MyDispatcher *dispatcher;
};*/
typedef struct _MyDispatcherWrapper MyDispatcherWrapper;
struct _MyDispatcherWrapper{
	MyDispatcher *dispatcher_ref;
	UT_hash_handle hh_id;
	UT_hash_handle hh_sock;
};
typedef struct _PollPoller PollPoller;
struct _PollPoller{
	int notifyfd;
	struct pollfd *events;
	MyDispatcherWrapper *h;
	MyDispatcherWrapper *free_h;
	MyDispatcherWrapper *sock_h;
	int dispatcher_count;
    int events_count;
    int events_capacity;
    bool event_changed;
};
int my_poll_monitor_insert(PollPoller *self,MyDispatcher *ele){
	MyDispatcherWrapper *found=NULL;
	int ret=-1;
	HASH_FIND(hh_id,self->h,&ele,sizeof(ele),found);
	if(!found){
		MyDispatcherWrapper *wrapper=(MyDispatcherWrapper*)my_malloc(sizeof(MyDispatcherWrapper));
		wrapper->dispatcher_ref=my_object_ref(ele);
		HASH_ADD(hh_id,self->h,dispatcher_ref,sizeof(ele),wrapper);
		printf("insert %p\n",ele);
		found=NULL;
		HASH_FIND(hh_sock,self->sock_h,&ele->fd,sizeof(ele->fd),found);
		if(!found){
			HASH_ADD_KEYPTR(hh_sock,self->sock_h,&(ele->fd),sizeof(ele->fd),wrapper);
		}
		ret=0;
	}
	return ret;
}
int my_poll_monitor_remove(PollPoller *self,MyDispatcher *ele){
	MyDispatcherWrapper *found=NULL;
	int ret=-1;
	HASH_FIND(hh_sock,self->sock_h,&ele->fd,sizeof(ele->fd),found);
	if(found){
		HASH_DELETE(hh_sock,self->sock_h,found);
	}
	found=NULL;
	HASH_FIND(hh_id,self->h,&ele,sizeof(ele),found);
	if(found){
		HASH_DELETE(hh_id,self->h,found);
		HASH_ADD(hh_id,self->free_h,dispatcher_ref,sizeof(ele),found);
		ret=0;
	}
	return ret;
}
void my_poller_free_h_dispose(PollPoller*self){
	MyDispatcherWrapper *itor=NULL;
	MyDispatcherWrapper *itor_tmp=NULL;
	HASH_ITER(hh_id,self->free_h,itor,itor_tmp){
		HASH_DELETE(hh_id,self->free_h,itor);
		my_object_unref(MY_OBJECT(itor->dispatcher_ref));
		itor->dispatcher_ref=NULL;
		my_free(itor);
	}
}
MyPoller* my_poller_create(void){
	PollPoller *poller=(PollPoller*)my_malloc(sizeof(PollPoller));
	poller->events_capacity=init_event_buf_size;
	int len=poller->events_capacity;
	poller->events=(struct pollfd*)my_malloc(len*sizeof(struct pollfd));
	return poller;
}
void my_poller_destroy(MyPoller* poller){
	if(!poller){
		return;
	}
	PollPoller *self=(PollPoller*)poller;
	MyDispatcherWrapper *itor=NULL;
	MyDispatcherWrapper *itor_tmp=NULL;
	HASH_ITER(hh_sock,self->sock_h,itor,itor_tmp){
		HASH_DELETE(hh_sock,self->sock_h,itor);
	}
	itor=NULL,itor_tmp=NULL;
	HASH_ITER(hh_id,self->h,itor,itor_tmp){
		HASH_DELETE(hh_id,self->h,itor);
		HASH_ADD(hh_id,self->free_h,dispatcher_ref,sizeof(itor->dispatcher_ref),itor);
	}
	my_poller_free_h_dispose(self);
	my_free(self->events);
	my_free(self);
}
void my_poller_poll(MyPoller* poller,int timeout_ms){
	PollPoller *self=(PollPoller*)poller;
	my_poller_free_h_dispose(self);
	if(self->dispatcher_count==0){
		return;
	}
	if(self->event_changed){
		if(self->events_capacity<self->dispatcher_count){
			int diff=self->dispatcher_count-self->events_capacity;
			int need=(diff+extend_event_buf_size)%extend_event_buf_size;
			int new_size=sizeof(struct pollfd)*(self->events_capacity+need);
			self->events=(struct pollfd*)my_realloc(self->events,new_size);
			self->events_capacity+=need;
		}
		memset(self->events,0,self->events_capacity);
		MyDispatcherWrapper *itor=NULL;
		MyDispatcherWrapper *itor_tmp=NULL;
		int i=0;
		HASH_ITER(hh_id,self->h,itor,itor_tmp){
		int ff=itor->dispatcher_ref->request_event;
		self->events[i].fd=itor->dispatcher_ref->fd;
		if(ff&(MY_EV_READ|MY_EV_ACCEPT)){
			self->events[i].events|=POLLIN;
		}
		if(ff&(MY_EV_WRITE|MY_EV_CONNECT)){
			self->events[i].events|=POLLOUT;
		}
		}
		i++;
		self->event_changed=false;
	}
	if(self->dispatcher_count){
		int fdcount=poll(self->events,self->dispatcher_count,timeout_ms);
		int i=0;
		if(fdcount>0){
			for(i=0;i<self->dispatcher_count;i++){
				if(self->events[i].fd<0){
					continue;
				}
				int fd=self->events[i].fd;
				MyDispatcherWrapper * found=NULL;
				if(self->events[i].revents&((POLLIN|POLLERR|POLLPRI))){
					if(self->events[i].revents&POLLIN){
						printf("poll read\n");
					}
					HASH_FIND(hh_sock,self->sock_h,&fd,sizeof(fd),found);
					if(found){
					MyDispatcher *dispatcher=found->dispatcher_ref;
					printf("%d %p\n",fd,dispatcher);
					my_dispatcher_call(dispatcher,read_event);
					}
				}
				if(self->events[i].revents&(POLLOUT)){
					HASH_FIND(hh_sock,self->sock_h,&fd,sizeof(fd),found);
					if(found){
						MyDispatcher *dispatcher=found->dispatcher_ref;
						my_dispatcher_call(dispatcher,write_event);
					}				
				}
			}
		}
	}
}
void my_poller_modify(MyPoller* poller,void *dispatcher,int op){
	PollPoller *self=(PollPoller*)poller;
	MyDispatcher *my_dis=(MyDispatcher*)dispatcher;
	int status=0;
	switch(op){
	case MY_EV_ADD_OP:{
		status=my_poll_monitor_insert(self,dispatcher);
		if(status==0){
			self->dispatcher_count++;
		}
		self->event_changed=true;
		break;
	}
	case MY_EV_DEL_OP:{
		status=my_poll_monitor_remove(self,dispatcher);
		if(status==0){
			printf("del \n");
			self->dispatcher_count--;
		}
		self->event_changed=true;
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
