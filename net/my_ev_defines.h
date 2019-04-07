#ifndef MY_EV_DEFINES_H_
#define MY_EV_DEFINES_H_
#include <time.h>
typedef struct timeval my_ev_timeval;
enum{
MY_EV_0_OP,
MY_EV_ADD_OP,
MY_EV_DEL_OP,
MY_EV_MOD_OP,
};
enum{
	MY_EV_READ=0x00000001,
	MY_EV_CONNECT=0x000000002,
	MY_EV_ACCEPT=0x00000004,
	MY_EV_WRITE=0x00000008,
};
#endif /* MY_EV_DEFINES_H_ */
