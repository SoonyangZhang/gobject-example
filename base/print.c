#include "lazy_micro.h"
#include "print.h"
#include "thread.h"
#include <unistd.h>
static void my_irunnable_interface_init(MyIRunnableInterface *iface);
G_DEFINE_TYPE_WITH_CODE (MyPrint, my_print, G_TYPE_OBJECT,
G_IMPLEMENT_INTERFACE (MY_TYPE_IRUNNABLE, my_irunnable_interface_init));

void my_print_run(MyIRunnable *iface,gpointer thread,gpointer userdata){
	MyThread *mythread=MY_THREAD(thread);
	MyPrint *self=MY_PRINT(iface);
	while(mythread->running){
		self->conuter++;
        g_print("add %d\n",self->conuter);
		sleep(1);
	}
	return ;
}
void my_print_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_print_parent_class)->dispose(gobject);
}
void my_print_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_print_parent_class)->finalize(gobject);
}
static void my_print_init(MyPrint *self){
	self->conuter=0;
}
static void my_print_class_init(MyPrintClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_print_dispose;
    base_class->finalize      = my_print_finalize;
}
static void my_irunnable_interface_init(MyIRunnableInterface *iface){
	iface->run=my_print_run;
}
MyPrint *my_print_new(void){
    MyPrint *ins;
    ins = g_object_new(MY_PRINT_TYPE, 0);
    return ins;
}
void my_print_free(MyPrint *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,PRINT,self));
    g_object_unref(G_OBJECT(self));
}
