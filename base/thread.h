/*
 * thread.h
 * copy from webrtc and learn write code
 */

#ifndef GOBJECT_EXAMPLE_THREAD_H_
#define GOBJECT_EXAMPLE_THREAD_H_
#include <glib-object.h>
#include <pthread.h>
#define THREAD_MANAGER_TYPE (thread_manager_get_type ())
#define MY_THREAD_TYPE (my_thread_get_type ())
typedef pthread_t MyPlatformThreadRef;
typedef struct _ThreadManager ThreadManager;
typedef struct _ThreadManagerClass ThreadManagerClass;

#define MY_THREAD_CLASS(class) \
	(G_TYPE_CHECK_CLASS_CAST ((class), MY_THREAD_TYPE, MyThreadClass));
#define MY_THREAD(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),MY_THREAD_TYPE,MyThread))
#define IS_MY_THREAD(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_THREAD_TYPE))
typedef struct _MyThread MyThread;
typedef struct _MyThreadClass MyThreadClass;
struct _ThreadManager{
	GObject parent;
	pthread_key_t key;
};
struct _ThreadManagerClass{
	GObjectClass parent_class;
};
GType thread_manager_get_type(void);
ThreadManager* thread_manager_instance();
gboolean is_main_thread();
MyPlatformThreadRef current_thead_ref();
struct _MyThread{
	GObject parent;
    pthread_t thread;
	gpointer runnable;
	gboolean running;
};
struct _MyThreadClass{
	GObjectClass parent_class;
};
GType my_thread_get_type(void);
MyThread *my_thread_new();
void my_thread_free(MyThread *thread);
gboolean my_thread_start(MyThread *thread,gpointer runnable);
void my_thread_join(MyThread *thread);
#endif /* GOBJECT_EXAMPLE_THREAD_H_ */
