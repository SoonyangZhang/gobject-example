#include "my_ev_poller.h"
extern MyPollerInterface my_poller_impl;
MyPollerInterface *my_get_poller_impl(){
	return &my_poller_impl;
}




