#include "thread.h"
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




