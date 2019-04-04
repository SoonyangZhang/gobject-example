#ifndef MY_DISPATCHER_H_
#define MY_DISPATCHER_H_
#include "my_object.h"
typedef struct _MyDispatcher MyDispatcher;
typedef struct _MyDispatcherClass MyDispatcherClass;
#define MY_DISPATCHER(obj) ((MyDispatcher*)obj)
#define MY_DISPATCHER_CLASS(kclass)((MyDispatcherClass*)kclass)
//#define my_dispather_call(method)  ((my_dispatcher_vtable())->method)
#define my_dispatcher_call(obj,method,...)  do{\
MyDispatcherClass *vtable=(MyDispatcherClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(__VA_ARGS__);\
}while(0)
typedef int SOCKET;
struct _MyDispatcher{
	MyObject parent;
	SOCKET fd;
	void* poll_plugin;
	int request_event;
	uint8_t *buf;
	int buf_len;
};
struct _MyDispatcherClass{
	MyObjectClass parent_class;
	void (*read_event)(MyDispatcher *self);
	void (*write_event)(MyDispatcher *self);
	int (*write)(MyDispatcher *self,void *data,int len);
};
MyDispatcher* my_dispacher_new();
void my_dispather_free(MyDispatcher* obj);
MyDispatcherClass* my_dispatcher_vtable();
#endif /* MY_DISPATCHER_H_ */
