#include "irunnable.h"
#include "thread.h"
G_DEFINE_INTERFACE (MyIRunnable, my_irunnable, G_TYPE_INVALID);

static void
my_irunnable_default_init (MyIRunnableInterface *iface) {

}
void my_irunnable_run(MyIRunnable * callback,gpointer thread, gpointer userdata){
	g_return_if_fail (MY_IS_IRUNNABLE(callback));
	MY_IRUNNABLE_GET_INTERFACE(callback)->run(callback,thread,userdata);
}


