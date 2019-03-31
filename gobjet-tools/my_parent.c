#include "lazy_micro.h"
G_DEFINE_TYPE (Myparent, my_parent, G_TYPE_OBJECT);
void my_parent_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_parent_parent_class)->dispose(gobject);
}
void my_parent_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_parent_parent_class)->finalize(gobject);
}
static void my_parent_init(MyParent *self){

}
static void my_parent_class_init(MyParentClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_parent_dispose;
    base_class->finalize      = my_parent_finalize;
    
}
MyParent *my_parent_new(void){
    MyParent *ins;
    ins = g_object_new(MY_PARENT_TYPE, 0);
    return ins;
}
void my_parent_free(MyParent *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,PARENT,self));
    g_object_unref(G_OBJECT(self));
}
