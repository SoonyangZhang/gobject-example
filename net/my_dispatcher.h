#ifndef MY_DISPATCHER_H_
#define MY_DISPATCHER_H_
#include "my_object.h"
#include "cf_platform.h"
//defference __VA_ARGS__ and ##__VA_ARGS__ 
// see http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2034.htm
typedef struct _MyDispatcher MyDispatcher;
typedef struct _MyDispatcherClass MyDispatcherClass;
#define MY_DISPATCHER(obj) ((MyDispatcher*)obj)
#define MY_DISPATCHER_CLASS(kclass)((MyDispatcherClass*)kclass)

#define my_dispatcher_call(obj,method,...)  do{\
MyDispatcherClass *vtable=(MyDispatcherClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(obj,##__VA_ARGS__);\
}while(0)
#define my_dispatcher_call_return(ret,obj,method,...)  do{\
MyDispatcherClass *vtable=(MyDispatcherClass*)MY_OBJECT_VTABLE(obj);\
ret=vtable->method(obj,##__VA_ARGS__);\
}while(0)
typedef int SOCKET;
#define MY_DISPATCHER_FIELD \
su_socket fd;\
int request_event;\
void *pollfun;\
void *poller;\
bool closed;\
void *usr;\
void (*notify_read)(MyDispatcher *self,void *usr)
struct _MyDispatcher{
	MyObject root;
	MY_DISPATCHER_FIELD;
};
#define MY_DISPATCHER_FUN_FIELD \
void (*read_event)(MyDispatcher *self);\
void (*write_event)(MyDispatcher *self);\
int (*write)(MyDispatcher *self,void *data,int len);\
int (*read)(MyDispatcher *self,void *buf,int len);\
int (*close)(MyDispatcher *self);\
MyDispatcher* (*accept)(void *self)
struct _MyDispatcherClass{
	MyObjectClass root_class;
	MY_DISPATCHER_FUN_FIELD;
};
MyDispatcher* my_dispatcher_new();
void my_dispatcher_init(MyDispatcher *self);
void my_dispatcher_unref(MyDispatcher* obj);
MyDispatcherClass* my_dispatcher_vtable();
#endif /* MY_DISPATCHER_H_ */
