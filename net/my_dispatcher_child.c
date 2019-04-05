#include "my_dispatcher_child.h"
MyDispatcherChildClass  my_dispatcherchild_default_vtable;
static bool class_inited=false;
void my_dispatcher_child_class_init(void);
void my_fun1(void){
	printf("%s\n",__FUNCTION__);
}
void my_fun2(void){
	printf("%s\n",__FUNCTION__);
}
void my_child_read_event(MyDispatcherChild *self){
	printf("%s\n",__FUNCTION__);
}
MyDispatcherChild* my_dispatcher_child_new(){
	MyDispatcherChild *ins;
	ins=(MyDispatcherChild *)my_object_create(sizeof(MyDispatcherChild));
	MY_OBJECT_VTABLE(ins)=my_dispatcher_child_vtable();
	return ins;
}
void my_dispatcher_child_dispose(MyDispatcherChild* obj){
	//resource allocation, from ptr in  MyDispatcher;
	printf("%s\n",__FUNCTION__);
	MyDispatcherClass *parent_class=my_dispatcher_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(obj));
}
void my_dispather_child_free(MyDispatcherChild* obj){
	my_object_unref(MY_OBJECT(obj));
}
MyDispatcherChildClass* my_dispatcher_child_vtable(){
	if(!class_inited){
		my_dispatcher_child_class_init();
	}
	return &my_dispatcherchild_default_vtable;
}
void my_dispatcher_child_class_init(void){
	class_inited=true;
	MyDispatcherChildClass *kclass=&my_dispatcherchild_default_vtable;
	MyDispatcherClass *parent=my_dispatcher_vtable();
	memcpy(kclass,parent,sizeof(*parent));
	kclass->parent_class.read_event=my_child_read_event;
	kclass->fun1=my_fun1;
	kclass->fun2=my_fun2;

	MY_OBJECT_CLASS(kclass)->dispose=my_dispatcher_child_dispose;
}


