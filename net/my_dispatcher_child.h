#ifndef MY_DISPATCHER_CHILD_H_
#define MY_DISPATCHER_CHILD_H_
#include "my_dispatcher.h"
typedef struct _MyDispatcherChild MyDispatcherChild;
typedef struct _MyDispatcherChildClass MyDispatcherChildClass;
#define MY_DISPATCHER_CHILD(obj) ((MyDispatcherChild*)obj)
#define MY_DISPATCHER_CHILD_CLASS(kclass)((MyDispatcherChildClass*)kclass)
#define my_dispatcher_child_call(obj,method,...)  do{\
MyDispatcherChildClass *vtable=(MyDispatcherChildClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(__VA_ARGS__);\
}while(0)

#define MY_DISPATCHER_CHILD_FIELD \
MY_DISPATCHER_FIELD;\
int a
struct _MyDispatcherChild{
	MyObject root;
	MY_DISPATCHER_CHILD_FIELD;
};

#define MY_DISPATCHER_CHILD_FUN_FIELD \
MY_DISPATCHER_FUN_FIELD;\
void (*fun1)(void);\
void (*fun2)(void)
struct _MyDispatcherChildClass{
	MyObjectClass root_class;
	MY_DISPATCHER_CHILD_FUN_FIELD;
};
MyDispatcherChild* my_dispacher_child_new();
void my_dispatcher_child_free(MyDispatcherChild* obj);
MyDispatcherChildClass* my_dispatcher_child_vtable();
void my_dispatcher_child_init(MyDispatcherChild *self);

#endif /* MY_DISPATCHER_CHILD_H_ */
