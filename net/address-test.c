#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include  "netutils.h"
#include "my_ev_poller.h"
#include "my_dispatcher.h"
#include "cf_platform.h"
#include "my_dispatcher_child.h"
#include "my_listener.h"
int running=1;
void signal_exit_handler(int sig)
{
	running=0;
}
int main(){
	signal(SIGTERM, signal_exit_handler);
	signal(SIGINT, signal_exit_handler);
	signal(SIGTSTP, signal_exit_handler);
	char *ip="127.0.0.1";
	uint16_t port=4321;
	su_socket fd;
	su_tcp_listen_create(ip,port,&fd);
	su_socket_noblocking(fd);
	MyPollerInterface *pollfun=my_get_poller_impl();
	MyPoller *poller=pollfun->poller_create();	
	MyListener *listener=my_listener_new();
	listener->fd=fd;
	listener->poller=poller;
	listener->pollfun=pollfun;
	pollfun->poller_modify(poller,listener,MY_EV_ADD_OP);
	int timeout=100;
	while(running){
		pollfun->poller_poll(poller,NULL);
	}
	pollfun->poller_destroy(poller);
	/*MyDispatcher *dispatcher=my_dispatcher_new();
	my_dispatcher_call(dispatcher,read_event,dispatcher);*/
	my_object_unref(MY_OBJECT(listener));
	//my_object_unref(MY_OBJECT(dispatcher));
    return 0;
}

