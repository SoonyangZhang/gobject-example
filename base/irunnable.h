#ifndef EXAMPLE_IRUNNABLE_H_
#define EXAMPLE_IRUNNABLE_H_
#include <glib-object.h>
#define MY_TYPE_IRUNNABLE (my_irunnable_get_type ())
#define MY_IRUNNABLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj)MY_TYPE_IRUNNABLE, MyIRunnable))
#define MY_IS_IRUNNABLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_TYPE_IRUNNABLE))
#define MY_IRUNNABLE_GET_INTERFACE(obj) (\
          G_TYPE_INSTANCE_GET_INTERFACE ((obj), MY_TYPE_IRUNNABLE, MyIRunnableInterface))

typedef struct _MyIRunnable MyIRunnable;
typedef struct _MyIRunnableInterface MyIRunnableInterface;
struct _MyIRunnableInterface{
	GTypeInterface parent_interface;
	void (*run)(MyIRunnable *self,gpointer thread, gpointer userdata);
};
GType my_irunnable_get_type (void);
void my_irunnable_run(MyIRunnable * callback,gpointer thread, gpointer userdata);
#endif /* EXAMPLE_IRUNNABLE_H_ */
