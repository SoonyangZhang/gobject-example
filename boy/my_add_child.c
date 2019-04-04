#include "lazy_micro.h"

#include "my_add_child.h"

G_DEFINE_TYPE (MyAddChild, my_add_child, MY_ADD_TYPE);
void my_add_child_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_add_child_parent_class)->dispose(gobject);
}
void my_add_child_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_add_child_parent_class)->finalize(gobject);
}
static void my_add_child_init(MyAddChild *self){

}
void my_add_child_add(gpointer instance,gint int_value,gpointer userdata){
	g_print("child add\n");
    MyAddChild *self=MY_ADD(instance);
    int base=5;
    int offset=(int)int_value;
    base+=offset;
    self->parent.a=self->parent.a+base;
}
static void my_add_child_class_init(MyAddChildClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_add_child_dispose;
    base_class->finalize      = my_add_child_finalize;
	MyAddClass *parent_class=MY_ADD_CLASS(base_class);
	parent_class->virtual_add=my_add_child_add;
}
MyAddChild *my_add_child_new(void){
    MyAddChild *ins;
    ins = g_object_new(MY_ADD_CHILD_TYPE, 0);
    return ins;
}
void my_add_child_free(MyAddChild *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,ADDCHILD,self));
    g_object_unref(G_OBJECT(self));
}
