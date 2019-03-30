#include "lazy_micro.h"
#include "thread.h"
#include "irunnable.h"
#include "timeutils.h"

static ThreadManager instance_;
static MyPlatformThreadRef main_thread_ref_;
//https://blog.csdn.net/yanbixing123/article/details/52970804
static void thread_manager_init(ThreadManager*self){
	g_printf ("%s %p\n",__FUNCTION__,pthread_self());
	pthread_key_create(&(self->key),NULL);
	main_thread_ref_=pthread_self();
}
static void __attribute__((constructor)) thread_manager_constructor(void){
	thread_manager_init(&instance_);
}
ThreadManager* thread_manager_instance(){
	return &instance_;
}
bool is_thead_ref_equal(MyPlatformThreadRef a,MyPlatformThreadRef b){
    //g_print("%p,%p\n",a,b);
	return pthread_equal(a,b);
}
bool is_main_thread(){
	return is_thead_ref_equal(current_thead_ref(),main_thread_ref_);
}
MyPlatformThreadRef current_thead_ref(){
	return pthread_self();
}
void thread_manager_set_current_thread(MyThread*thread){
    ThreadManager *manager=thread_manager_instance();
	pthread_setspecific(manager->key,thread);
}
MyThread * thread_manager_current_thread(){
	ThreadManager *manager=thread_manager_instance();
	MyThread *current=pthread_getspecific(manager->key);
	return current;
}


G_DEFINE_TYPE (MyThread, my_thread, G_TYPE_OBJECT);
void my_thread_wrap_current_thread(MyThread *thread);
void* my_thread_pre_run(void *self);

void my_thread_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_thread_parent_class)->dispose(gobject);
}
void my_thread_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_thread_parent_class)->finalize(gobject);
}
static void my_thread_init(MyThread *self){

}
static void my_thread_class_init(MyThreadClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_thread_dispose;
    base_class->finalize      = my_thread_finalize;
}
MyThread *my_thread_new(){
	MyThread *instance;
	instance=g_object_new(MY_THREAD_TYPE,NULL);
	return instance;
}
void my_thread_free(MyThread *self){
    g_assert(self!= NULL);
    //g_return_if_fail(IS_MY_THREAD(self));
    g_return_if_fail(lazy_is_obj(MY,THREAD,self));
    g_object_unref(G_OBJECT(self));
}

bool my_thread_start(MyThread *thread,gpointer runnable){
	thread->runnable=runnable;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int error=pthread_create(&thread->thread,&attr,my_thread_pre_run,thread);
	if(error!=0){
		return FALSE;
	}
	return TRUE;
}
void my_thread_join(MyThread *thread){
	thread->running=FALSE;
	void *pv;
	pthread_join(thread->thread,&pv);
}
void* my_thread_pre_run(void *self){
	MyThread *thread=MY_THREAD(self);
	thread->running=TRUE;
	thread_manager_set_current_thread(self);
	if(thread->runnable){
		my_irunnable_run(thread->runnable,thread,NULL);
	}else{
		//just return
		g_print("no runnable function");
	}
    return NULL;
}
MyThread* my_thread_current(void){
	MyThread *thread=thread_manager_current_thread();
	if(!thread&&is_main_thread()){
        thread=my_thread_new();
        my_thread_wrap_current_thread(thread);
	}
	return thread;
}
bool thread_is_current_thread(MyThread *thread){
	return thread_manager_current_thread()==thread;
}
void my_thread_wrap_current_thread(MyThread *thread){
	thread->thread=pthread_self();
	thread_manager_set_current_thread(thread);
}
bool my_thread_sleep_ms(int milliseconds){
	base_sleep(milliseconds);
}
