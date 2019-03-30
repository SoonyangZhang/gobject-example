#include "lazy_micro.h"
#include "thread.h"
#include "irunnable.h"
static ThreadManager *instance_=NULL;
static MyPlatformThreadRef main_thread_ref_;
//https://blog.csdn.net/yanbixing123/article/details/52970804
G_DEFINE_TYPE (ThreadManager, thread_manager, G_TYPE_OBJECT);
static void thread_manager_init(ThreadManager*self){
	g_printf ("%s\n",__FUNCTION__);
	pthread_key_create(&(self->key),NULL);
}
static void thread_manager_class_init(ThreadManagerClass *klass){

}
ThreadManager* thread_manager_new(){
	ThreadManager *instance;
	instance=g_object_new(THREAD_MANAGER_TYPE,NULL);
	return instance;
}
ThreadManager* thread_manager_instance(){
	if(instance_){
		return instance_;
	}
	instance_=thread_manager_new();
    main_thread_ref_=pthread_self();
	return instance_;
}
gboolean is_thead_ref_equal(MyPlatformThreadRef a,MyPlatformThreadRef b){
	return a==b;
}
gboolean is_main_thread(){
	return is_thead_ref_equal(current_thead_ref(),main_thread_ref_);
}
MyPlatformThreadRef current_thead_ref(){
	return pthread_self();
}




G_DEFINE_TYPE (MyThread, my_thread, G_TYPE_OBJECT);
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

gboolean my_thread_start(MyThread *thread,gpointer runnable){
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
	if(thread->runnable){
		my_irunnable_run(thread->runnable,thread,NULL);
	}else{
		//just return
		g_print("no runnable function");
	}
    return NULL;
}
