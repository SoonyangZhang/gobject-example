/*
 * thread.h
 * copy from webrtc and learn write code
 */

#ifndef GOBJECT_EXAMPLE_THREAD_H_
#define GOBJECT_EXAMPLE_THREAD_H_
#include <glib-object.h>
#include <pthread.h>
#define THREAD_MANAGER_TYPE (thread_manager_get_type ())
typedef pthread_t MyPlatformThreadRef;
typedef struct _ThreadManager ThreadManager;
struct _ThreadManager{
	GObject parent;
	pthread_key_t key;
};
typedef struct _ThreadManagerClass ThreadManagerClass;
struct _ThreadManagerClass{
	GObjectClass parent_class;
};
ThreadManager* thread_manager_instance();
gboolean is_main_thread();
MyPlatformThreadRef current_thead_ref();



#endif /* GOBJECT_EXAMPLE_THREAD_H_ */
