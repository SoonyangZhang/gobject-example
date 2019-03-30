#include "timeutils.h"
#if defined (WIN_32)
#include <windows.h>
#else
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#endif
bool base_sleep(int milliseconds){
	#if defined (WIN_32)
	Sleep(milliseconds);
	#else
	struct timespec req = {0};
	time_t sec = (int)(milliseconds / 1000);
	milliseconds = milliseconds - (sec * 1000);
	req.tv_sec = sec;
	req.tv_nsec = milliseconds * 1000000L;
	nanosleep(&req,NULL);
	#endif
	return true;
}
static inline void itimeofday(long *sec, long *usec){
	#if defined (WIN32)
	static long mode = 0, addsec = 0;
	bool retval;
	static int64_t freq = 1;
	int64_t qpc;
	if (mode == 0) {
		retval = QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		freq = (freq == 0)? 1 : freq;
		retval = QueryPerformanceCounter((LARGE_INTEGER*)&qpc);
		addsec = (long)time(NULL);
		addsec = addsec - (long)((qpc / freq) & 0x7fffffff);
		mode = 1;
	}
	retval = QueryPerformanceCounter((LARGE_INTEGER*)&qpc);
	retval = retval * 2;
	if (sec) *sec = (long)(qpc / freq) + addsec;
	if (usec) *usec = (long)((qpc % freq) * 1000000 / freq);
	#else
	struct timeval time;
	gettimeofday(&time, NULL);
	if (sec) *sec = time.tv_sec;
	if (usec) *usec = time.tv_usec;
	#endif
}
uint64_t base_clock64(void){
	long s, u;
	int64_t value;
	itimeofday(&s, &u);
	value = ((int64_t)s) * 1000 + (u / 1000);
	return value;
}
uint32_t base_clock32(void){
	return (uint32_t)(base_clock64()& 0xfffffffful);
}




