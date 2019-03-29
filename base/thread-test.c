#include "thread.h"
#include "irunnable.h"
#include "print.h"
#include <signal.h>
static int running=1;
void signal_exit_handler(int sig)
{
	running=0;
}
int main(){
    signal(SIGTERM, signal_exit_handler);
	signal(SIGINT, signal_exit_handler);
	signal(SIGTSTP, signal_exit_handler);
    //ThreadManager *instance= thread_manager_instance();
    MyPrint *print=my_print_new();
    MyThread *thread=my_thread_new();
    my_thread_start(thread,print);
    while(running){
        
    }
    my_thread_join(thread);
    return 0;
}
