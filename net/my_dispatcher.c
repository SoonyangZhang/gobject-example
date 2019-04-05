#include "my_dispatcher.h"
MyDispatcherClass  my_dispatcher_default_vtable;
static bool class_inited=false;
void my_dispatcher_class_init();
void my_dispacther_read_event(MyDispatcher *self){
	printf("%s\n",__FUNCTION__);
}
void my_dispacther_write_event(MyDispatcher *self){
	printf("%s\n",__FUNCTION__);
}
int my_dispacther_write(MyDispatcher *self,void *data,int len){
	printf("%s\n",__FUNCTION__);
	return 0;
}
MyDispatcher* my_dispacher_new(){
	MyDispatcher *ins;
	ins=(MyDispatcher*)my_object_create(sizeof(MyDispatcher));
	MY_OBJECT_VTABLE(ins)=my_dispatcher_vtable();
	return ins;
}
void my_dispatcher_dispose(MyDispatcher* obj){
	//resource allocation, free ptr in  MyDispatcher;
	if(obj->buf){
		printf("free buffe len %d\n",obj->buf_len);
		free(obj->buf);
		obj->buf=NULL;
	}
	printf("%s\n",__FUNCTION__);
	MyObjectClass *parent_class=my_object_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(obj));
}
void my_dispather_free(MyDispatcher* obj){
	my_object_unref(MY_OBJECT(obj));
}
MyDispatcherClass* my_dispatcher_vtable(){
	if(!class_inited){
		my_dispatcher_class_init();
	}
	return &my_dispatcher_default_vtable;
}
void my_dispatcher_class_init(){
	class_inited=true;
	MyDispatcherClass *kclass=&my_dispatcher_default_vtable;
	MyObjectClass *parent=my_object_vtable();
	memcpy(kclass,parent,sizeof(*parent));
	kclass->read_event=my_dispacther_read_event;
	kclass->write=my_dispacther_write;
	kclass->write_event=my_dispacther_write_event;

	MY_OBJECT_CLASS(kclass)->dispose=my_dispatcher_dispose;
}
