#include "lazy_micro.h"

void my_print_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_print_parent_class)->dispose(gobject);
}
void my_print_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_print_parent_class)->finalize(gobject);
}
static void my_print_init(MyPrint *self){

}
static void my_print_class_init(MyPrintClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_print_dispose;
    base_class->finalize      = my_print_finalize;
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
