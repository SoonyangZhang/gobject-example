#include "my_listener.h"
#include "my_ev_poller.h"
MyListenerClass  default_vtable;
static bool class_inited=false;
void my_listerer_class_init();
void my_listener_read_event(MyListener *self){
	su_addr addr;
	int addr_len=sizeof(addr);
	su_socket new_fd=su_accept(self->fd,&addr,&addr_len);
	if(new_fd!=-1){
		printf("new con\n");
		su_socket_noblocking(new_fd);
		MyPollerInterface *pollfun=(MyPollerInterface*)self->pollfun;
		MyDispatcher *con=my_dispatcher_new();
		con->fd=new_fd;
		con->poller=self->poller;
		con->pollfun=pollfun;
		con->request_event=MY_EV_READ;
		pollfun->poller_modify(self->poller,con,MY_EV_ADD_OP);
		my_object_unref(MY_OBJECT(con));
	}
}
void my_listener_write_event(MyListener *self){

}
void my_listener_write(MyListener *self,void *data,int len){
	printf("%s should not be called\n",__FUNCTION__);
}
MyListener* my_listener_new(){
	MyListener *ins;
	ins=(MyListener*)my_object_create(sizeof(MyListener));
	my_listener_init(ins);
	return ins;
}
void my_listener_dispose(MyListener *self){
	printf("%s\n",__FUNCTION__);
	MyDispatcherClass *parent_class=my_dispatcher_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(self));
}
MyListenerClass *my_listener_vtable(){
	if(!class_inited){
		my_listerer_class_init();
	}
	return &default_vtable;
}
void my_listener_init(MyListener *self){
	if(!self){
		return ;
	}
	my_dispatcher_init(MY_DISPATCHER(self));
	MY_OBJECT_VTABLE(self)=my_listener_vtable();
	self->request_event=MY_EV_ACCEPT;
}
void my_listerer_class_init(){
	class_inited=true;
	MyListenerClass *kclass=&default_vtable;
	MyDispatcherClass *parent=my_dispatcher_vtable();
	memcpy(kclass,parent,sizeof(*parent));
	kclass->read_event=my_listener_read_event;
	kclass->write_event=my_listener_write_event;
	kclass->write=my_listener_write;
	MY_OBJECT_CLASS(kclass)->dispose=my_listener_dispose;
}



