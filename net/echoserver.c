#include "echoserver.h"
#include "echocon.h"
#include "cf_platform.h"
#include "my_ev_poller.h"
// at first, I name it default_vtable,same in mylistener, bug found;
EchoServerClass  echo_server_default_vtable;
static bool class_inited=false;
void echo_server_class_init();
void clousure_read(MyDispatcher *dispatcher,void *usr){
	printf("%s\n",__FUNCTION__);
	EchoServer *self=(EchoServer*)usr;
	MyListener *l=(MyListener*)dispatcher;
	if(self){
		MyDispatcher *new_dis=NULL;
		my_dispatcher_call_return(new_dis,l,accept);
		EchoCon *con=echo_con_new();
		echo_con_set_dispatcher(con,new_dis);
	}
}
EchoServer* echo_server_new(){
	EchoServer *ins=NULL;
	ins=(EchoServer*)my_object_create(sizeof(EchoServer));
	echo_server_init(ins);
	return ins;
}
void echo_server_init(EchoServer *self){
	if(!self){
		return;
	}
	my_object_init(self);
	MY_OBJECT_VTABLE(self)=echo_server_vtable();
}
void echo_server_unref(EchoServer *self){
	my_object_unref(MY_OBJECT(self));
}
void echo_server_bind(EchoServer *self,char*ip,uint16_t port){
	if(!self){return;}
	self->srv_ref=my_listener_new();
	printf("%p,listener %p\n",self,self->srv_ref);
	MyPollerInterface *pollfun=my_get_poller_impl();
	self->srv_ref->pollfun=pollfun;
	MyPoller *poller=pollfun->poller_create();
	self->srv_ref->poller=poller;
	su_socket fd;
	su_tcp_listen_create(ip,port,&fd);
	su_socket_noblocking(fd);
	self->srv_ref->fd=fd;
	self->srv_ref->usr=self;
	self->srv_ref->notify_read=clousure_read;
	pollfun->poller_modify(poller,self->srv_ref,MY_EV_ADD_OP);
}
void echo_server_stop(EchoServer *self){

}
void echo_server_loop(EchoServer *self){
	if(!self||!self->srv_ref){
		return ;
	}
	MyPollerInterface *pollfun=self->srv_ref->pollfun;
	pollfun->poller_poll(self->srv_ref->poller,0);
}
void echo_server_dispose(EchoServer *self){
	printf("%s %p\n",__FUNCTION__,self);
	if(!self){
		return;
	}
	if(self->srv_ref){
		MyPollerInterface *pollfun=self->srv_ref->pollfun;
		if(self->srv_ref->poller){
			pollfun->poller_destroy(self->srv_ref->poller);
		}
		self->srv_ref->usr=0;
		self->srv_ref->notify_read=0;
		printf("%s %p\n",__FUNCTION__,self->srv_ref);
		my_object_unref(MY_OBJECT(self->srv_ref));
		self->srv_ref=0;
	}
	MyObjectClass *parent_class=my_object_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(self));
}
EchoServerClass* echo_server_vtable(){
	if(!class_inited){
		echo_server_class_init();
	}
	return &echo_server_default_vtable;
}
void echo_server_class_init(){
	class_inited=true;
	EchoServerClass *kclass=&echo_server_default_vtable;
	MyObjectClass *parent=my_object_vtable();
	memcpy(kclass,parent,sizeof(*parent));
	kclass->bind=echo_server_bind;
	kclass->loop=echo_server_loop;
	kclass->stop=echo_server_stop;
	MY_OBJECT_CLASS(kclass)->dispose=echo_server_dispose;
}



