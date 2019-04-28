#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include  "netutils.h"
#include "my_ev_poller.h"
#include "my_dispatcher.h"
#include "cf_platform.h"
#include "my_dispatcher_child.h"
#include "echoserver.h"
int running=1;
void signal_exit_handler(int sig)
{
	running=0;
}
/*
int main(){
	signal(SIGTERM, signal_exit_handler);
	signal(SIGINT, signal_exit_handler);
	signal(SIGTSTP, signal_exit_handler);
	char *ip="127.0.0.1";
	uint16_t port=4321;
	EchoServer *server=echo_server_new();
	echo_server_call(server,bind,ip,port);
	while(running){
		echo_server_call(server,loop);
	}
	echo_server_call(server,stop);
	my_object_unref(MY_OBJECT(server));
    return 0;
}*/
#include "my_string.h"
#include "my_vector.h"
#include <string.h>
int main(){
	char *c="hello world";
	MyString *str=my_string_new(c,strlen(c));
	printf("len %d\n",my_string_len(str));
	MyVector *vec=my_vector_new(sizeof(MyString),my_string_init,MY_OBJECT(str)->vtable->dispose,my_string_copy);
	my_vector_push_back(vec,str);
	my_string_unref(str);
	my_vector_dtor(vec);
	return 0;
}


