#ifndef MY_LISTENER_H_
#define MY_LISTENER_H_
#include "my_dispatcher.h"
typedef struct _MyListener MyListener;
typedef struct _MyListenerClass MyListenerClass;
#define MY_LISTERER(obj) ((MyListener*)obj)
#define MY_LISTENER_CLASS(kclass) ((MyListenerClass*)kclass)
#define my_listerer_call(obj,method,...)  do{\
MyDispatcherClass *vtable=(MyListenerClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(__VA_ARGS__);\
}while(0)
#define MY_LISTENER_FIELD \
MY_DISPATCHER_FIELD
struct _MyListener{
	MyObject root;
	MY_LISTENER_FIELD;
};
struct _MyListenerClass{
	MyObjectClass root_class;
	MY_DISPATCHER_FUN_FIELD;
};
MyListener* my_listener_new();
void my_listener_unref(MyListener* obj);
MyListenerClass* my_listener_vtable();
void my_listener_init(MyListener *self);
#endif /* MY_LISTENER_H_ */
