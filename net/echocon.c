#include "echocon.h"
#include "my_ev_poller.h"
#define BUF_SIZE 1500
void clousure_con_read(MyDispatcher *dispatcher,void *usr){
	printf("%s %d\n",__FUNCTION__,dispatcher->fd);
	EchoCon *self=(EchoCon*)usr;
	uint8_t buf[BUF_SIZE];
	memset(buf,0,BUF_SIZE);
	int len=0;
	my_dispatcher_call_return(len,dispatcher,read,buf,BUF_SIZE);
	if(len){
	printf("%s\n",buf);
	my_dispatcher_call(dispatcher,write,buf,len);
	}
	if(!len){
		printf("peer closed\n");
		my_dispatcher_call(self->con_ref,close);
		MyPollerInterface *pollfun=(MyPollerInterface*)self->con_ref->pollfun;
		pollfun->poller_modify(dispatcher->poller,self->con_ref,MY_EV_DEL_OP);
		my_object_unref(MY_OBJECT(self->con_ref));
		self->con_ref=0;
		echo_con_unref(self);
	}
}
EchoCon *echo_con_new(){
	EchoCon *ins=0;
	ins=(EchoCon*)my_malloc(sizeof(EchoCon));
	return ins;
}
void echo_con_set_dispatcher(EchoCon*self,MyDispatcher *dis){
	self->con_ref=dis;
	self->con_ref->usr=self;
	self->con_ref->notify_read=clousure_con_read;
}
void echo_con_unref(EchoCon *self){
	my_free(self);
}




