#include "thread.h"
#include "irunnable.h"
#include "print.h"
#include <signal.h>
#include <unistd.h>
#include "timeutils.h"
static int running=1;
void signal_exit_handler(int sig)
{
	running=0;
}
int main(){
    signal(SIGTERM, signal_exit_handler);
	signal(SIGINT, signal_exit_handler);
	signal(SIGTSTP, signal_exit_handler);
    MyThread *main_thread=my_thread_current();
    printf("thread %p %p\n",main_thread,pthread_self());
    
    MyPrint *print=my_print_new();
    MyThread *thread=my_thread_new();
    printf("thread1 %p\n",thread);
    my_thread_start(thread,print,NULL);
    while(running){
        my_thread_sleep_ms(1000);
    }
    my_thread_join(thread);
    my_thread_free(thread);
    /*
    uint64_t last=base_clock32();
    uint64_t delta=base_clock32()-last;
    g_print("time %lu\n",delta);
    my_thread_free(main_thread);*/
    return 0;
}
