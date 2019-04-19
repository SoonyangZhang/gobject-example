#include <sys/types.h>
#include <sys/socket.h>
#include "my_dispatcher.h"
#include "my_ev_poller.h"
static MyDispatcherClass  default_vtable;
static bool class_inited=false;
#define BUF_SIZE 1500
void my_dispatcher_class_init();
int my_dispacther_write(MyDispatcher *self,void *data,int len);
void my_dispacther_read_event(MyDispatcher *self){
	printf("%s %d\n",__FUNCTION__,self->fd);
	if(!self||self->closed){
		return;
	}
	if(self->notify_read){
		self->notify_read(self,self->usr);
	}
}
void my_dispacther_write_event(MyDispatcher *self){
	printf("%s\n",__FUNCTION__);
}
int my_dispacther_write(MyDispatcher *self,void *data,int len){
	printf("%s\n",__FUNCTION__);
	int ret=0;
	ret=send(self->fd,data,len,0);
	return ret;
}
int my_dispatcher_read(MyDispatcher *self,void *buf,int len){
	if(self->closed){
		return -1;
	}
	int ret=0;
	ret=recv(self->fd,buf,len,0);
	return ret;	
}
int my_dispatcher_close(MyDispatcher *self){
	if(self->closed){
		return ;
	}
	self->closed=true;
	if(self->fd>=0){
		su_socket_destroy(self->fd);
	}	
}
MyDispatcher *my_dispatcher_accept(MyDispatcher *self){
	su_addr addr;
	int addr_len=sizeof(addr);
	su_socket new_fd=su_accept(self->fd,&addr,&addr_len);
	MyDispatcher *con=my_dispatcher_new();
	if(new_fd!=-1){
		printf("new con\n");
		su_socket_noblocking(new_fd);
		MyPollerInterface *pollfun=(MyPollerInterface*)self->pollfun;
		con->fd=new_fd;
		con->poller=self->poller;
		con->pollfun=pollfun;
		con->request_event=MY_EV_READ;
		pollfun->poller_modify(self->poller,con,MY_EV_ADD_OP);
	}
	return con;
}
MyDispatcher* my_dispatcher_new(){
	MyDispatcher *ins;
	ins=(MyDispatcher*)my_object_create(sizeof(MyDispatcher));
	my_dispatcher_init(ins);
	return ins;
}
void my_dispatcher_dispose(MyDispatcher* self){
	if(!self){
		return;
	}
	my_dispatcher_call(self,close);
	printf("%s %p\n",__FUNCTION__,self);
	MyObjectClass *parent_class=my_object_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(self));
}
void my_dispatcher_unref(MyDispatcher* obj){
	my_object_unref(MY_OBJECT(obj));
}
MyDispatcherClass* my_dispatcher_vtable(){
	if(!class_inited){
		my_dispatcher_class_init();
	}
	return &default_vtable;
}
void my_dispatcher_class_init(){
	class_inited=true;
	MyDispatcherClass *kclass=&default_vtable;
	MyObjectClass *parent=my_object_vtable();
	memcpy(kclass,parent,sizeof(*parent));
	kclass->read_event=my_dispacther_read_event;
	kclass->write=my_dispacther_write;
	kclass->write_event=my_dispacther_write_event;
	kclass->read=my_dispatcher_read;
	kclass->close=my_dispatcher_close;
	kclass->accept=my_dispatcher_accept;
	MY_OBJECT_CLASS(kclass)->dispose=my_dispatcher_dispose;
}
void my_dispatcher_init(MyDispatcher *self){
	if(!self){return ;}
	my_object_init(self);
	MY_OBJECT_VTABLE(self)=my_dispatcher_vtable();
	self->fd=-1;
	self->request_event=0;
	self->closed=false;
	self->request_event=MY_EV_READ;
	self->usr=0;
	self->notify_read=0;
}
