#include <stdio.h>
#include <stdint.h>
#include  "netutils.h"
#include "my_ev_poller.h"
#include "my_dispatcher.h"
#include "my_dispatcher_child.h"
int main(){
	MyPollerInterface *pollerimpl=my_get_poller_impl();
	MyPoller *poller=pollerimpl->poller_create();	
	MyDispatcher *dispatcher1=my_dispatcher_new();
	pollerimpl->poller_modify(poller,dispatcher1,MY_EV_ADD_OP);
	MyDispatcher *dispatcher2=my_dispatcher_new();
	pollerimpl->poller_modify(poller,dispatcher2,MY_EV_ADD_OP);
	MyDispatcher *dispatcher3=my_dispatcher_new();
	pollerimpl->poller_modify(poller,dispatcher3,MY_EV_ADD_OP);
	pollerimpl->poller_poll(poller,NULL);
	pollerimpl->poller_modify(poller,dispatcher2,MY_EV_DEL_OP);
	pollerimpl->poller_poll(poller,NULL);
	my_dispatcher_unref(dispatcher1);
	my_dispatcher_unref(dispatcher2);
	my_dispatcher_unref(dispatcher3);
	pollerimpl->poller_modify(poller,dispatcher1,MY_EV_DEL_OP);
	pollerimpl->poller_modify(poller,dispatcher3,MY_EV_DEL_OP);
	pollerimpl->poller_poll(poller,NULL);
	pollerimpl->poller_destroy(poller);
	/*MyDispatcherChild *child=my_dispatcher_child_new();
	my_dispatcher_call(child,read_event,child);
	my_dispatcher_child_call(child,fun1);
	
	MY_DISPATCHER(child)->buf=malloc(8*sizeof(uint8_t));
	MY_DISPATCHER(child)->buf_len=8;
	printf("%p\n",child->parent.parent.vtable);
	printf("%p\n",my_dispatcher_child_vtable());
	my_dispather_child_free(child);*/
    return 0;
}

