/*
 * thread.h
 * copy from webrtc and learn write code
 */

#ifndef GOBJECT_EXAMPLE_THREAD_H_
#define GOBJECT_EXAMPLE_THREAD_H_
#include <glib-object.h>
#include <pthread.h>
#include <stdbool.h>
#define MY_THREAD_TYPE (my_thread_get_type ())
#define MY_THREAD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_THREAD_TYPE, MyThread))
#define MY_IS_THREAD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_THREAD_TYPE))
#define MY_THREAD_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_THREAD_TYPE, MyThreadClass))
#define MY_IS_THREAD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_THREAD_TYPE))
#define MY_THREAD_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_THREAD_TYPE,MyThreadClass))
typedef pthread_t MyPlatformThreadRef;
typedef struct _ThreadManager ThreadManager;
typedef struct _ThreadManagerClass ThreadManagerClass;
typedef struct _MyThread MyThread;
typedef struct _MyThreadClass MyThreadClass;
struct _ThreadManager{
	pthread_key_t key;
};
GType thread_manager_get_type(void);
ThreadManager* thread_manager_instance();
bool is_main_thread();
MyPlatformThreadRef current_thead_ref();
struct _MyThread{
	GObject parent;
    pthread_t thread;
	gpointer runnable;
    gpointer userdata;
	bool running;
};
struct _MyThreadClass{
	GObjectClass parent_class;
};
GType my_thread_get_type(void);
MyThread *my_thread_new();
void my_thread_free(MyThread *thread);
bool my_thread_start(MyThread *thread,gpointer runnable,gpointer userdata);
void my_thread_join(MyThread *thread);
MyThread*my_thread_current (void);
bool thread_is_current_thread(MyThread *thread);
bool my_thread_sleep_ms(int milliseconds);
#endif /* GOBJECT_EXAMPLE_THREAD_H_ */
