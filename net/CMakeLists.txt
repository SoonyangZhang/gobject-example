include_directories(${CMAKE_SOURCE_DIR}/base)
include_directories(${CMAKE_SOURCE_DIR}/net)
set(net_LIB 
netutils.cc
posix.c
my_ev_poller.c
my_ev_poller_poll.c
my_object.c
my_dispatcher.c
my_dispatcher_child.c
my_string.c
echoserver.c
echocon.c
)
add_library(net STATIC ${net_LIB})
