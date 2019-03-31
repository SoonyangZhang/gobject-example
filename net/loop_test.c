#include <glib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "timeutils.h"
static GMutex *mutex = NULL;
static gboolean t1_end = FALSE;
static gboolean t2_end = FALSE;
static int running=1;
void signal_exit_handler(int sig)
{
	running=0;
}
typedef struct _Arg Arg;
struct _Arg
{
	GMainLoop* loop;
	gint max;
};
void	run_1(Arg *arg)
{
    printf("1\n");
}
void	run_2(Arg *arg)
{
    printf("2\n");
}
void run_3(Arg *arg)
{
    printf("3\n");
}
void test(){
    signal(SIGTERM, signal_exit_handler);
	signal(SIGINT, signal_exit_handler);
	signal(SIGTSTP, signal_exit_handler);
	GMainLoop *mloop;
	Arg *arg;
	
	if(!g_thread_supported())
		g_thread_init(NULL);
	mloop = g_main_loop_new(NULL, FALSE);
	
	arg = g_new(Arg, 1);
	arg->loop = mloop;
	arg->max = 11;
		
	mutex = g_mutex_new();
    //GThread *gthread = NULL;
    //gthread=g_thread_new("run1",run_1, arg);
	//g_thread_create(run_1, arg, TRUE, NULL);
	//g_thread_create(run_2, arg, TRUE, NULL);
	//g_thread_create(run_3, arg, TRUE, NULL);
	
	//g_main_loop_run(mloop);
	//g_print("线程3退出事件循环\n");
	g_mutex_free(mutex);
	//g_print("释放互斥对象\n"); 
	g_free(arg);
    while(running){
        my_thread_sleep_ms(1000);
    }
	//g_print("释放参数所用的内存\n");
}
int	main(int argc, char *argv[])
{
	GMainLoop *mloop;
	
	if(!g_thread_supported())
		g_thread_init(NULL);
	mloop = g_main_loop_new(NULL, FALSE);
    GMainContext *context=g_main_context_new();
    g_main_context_push_thread_default(context);
    void *p=NULL;
    p=g_main_context_get_thread_default();
    printf("%p,%p\n",context,p);
}
