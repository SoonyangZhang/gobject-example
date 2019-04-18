#ifndef ECHOSERVER_H_
#define ECHOSERVER_H_
#include "my_object.h"
#include "my_listener.h"
#define echo_server_call(obj,method,...)  do{\
EchoServerClass *vtable=(EchoServerClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(obj,##__VA_ARGS__);\
}while(0)
typedef struct _EchoServer EchoServer;
typedef struct _EchoServerClass EchoServerClass;
struct _EchoServer{
	MyObject root;
	MyListener *srv_ref;
};
struct _EchoServerClass{
	MyObjectClass root_class;
	void (*bind)(EchoServer *self,char*ip,uint16_t port);
	void (*stop)(EchoServer *self);
	void (*loop)(EchoServer *self);
};
EchoServer* echo_server_new();
void echo_server_init(EchoServer *self);
void echo_server_unref(EchoServer *self);
EchoServerClass* echo_server_vtable();
#endif /* ECHOSERVER_H_ */
