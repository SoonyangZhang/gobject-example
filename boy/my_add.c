#include "lazy_micro.h"
#include "my_add.h"
G_DEFINE_TYPE (MyAdd, my_add, G_TYPE_OBJECT);
enum { ADD_ADD,
LAST_SIGNAL };
static gint my_add_signals[LAST_SIGNAL] = { 0 };
void my_add_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_add_parent_class)->dispose(gobject);
}
void my_add_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_add_parent_class)->finalize(gobject);
}
static void my_add_init(MyAdd *self){
    self->a=0;
}
void print(MyAdd *self){
    g_print("a %d\n",self->a);
}
void add(gpointer instance,gint int_value,gpointer userdata){
    MyAdd *self=MY_ADD(instance);
    int base=0;
    int offset=(int)int_value;
    base+=offset;
    self->a=self->a+base;
}
static void my_add_class_init(MyAddClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_add_dispose;
    base_class->finalize      = my_add_finalize;
    kclass->virtual_add=add;
    kclass->print=print;
    my_add_signals[ADD_ADD] = g_signal_new("add",
                MY_ADD_TYPE,
                G_SIGNAL_RUN_FIRST,
                G_STRUCT_OFFSET(MyAddClass,virtual_add),
                NULL,NULL,
                g_cclosure_marshal_VOID__INT,
                G_TYPE_NONE, 1, G_TYPE_INT);
}
MyAdd *my_add_new(void){
    MyAdd *ins;
    ins = g_object_new(MY_ADD_TYPE, 0);
    return ins;
}
void my_add_free(MyAdd *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,ADD,self));
    g_object_unref(G_OBJECT(self));
}
