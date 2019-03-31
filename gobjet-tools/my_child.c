#include "lazy_micro.h"
G_DEFINE_TYPE (MyChild, my_child, MY_PARENT_TYPE);
void my_child_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_child_parent_class)->dispose(gobject);
}
void my_child_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_child_parent_class)->finalize(gobject);
}
static void my_child_init(MyChild *self){

}
static void my_child_class_init(MyChildClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_child_dispose;
    base_class->finalize      = my_child_finalize;
}
MyChild *my_child_new(void){
    MyChild *ins;
    ins = g_object_new(MY_CHILD_TYPE, 0);
    return ins;
}
void my_child_free(MyChild *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,CHILD,self));
    g_object_unref(G_OBJECT(self));
}
