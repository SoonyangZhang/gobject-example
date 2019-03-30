#include "lazy_micro.h"

void base_print_dispose(GObject *gobject){
    G_OBJECT_CLASS (base_print_parent_class)->dispose(gobject);
}
void base_print_finalize(GObject *gobject){
    G_OBJECT_CLASS (base_print_parent_class)->finalize(gobject);
}
static void base_print_init(BasePrint *self){

}
static void base_print_class_init(BasePrintClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = base_print_dispose;
    base_class->finalize      = base_print_finalize;
}
BasePrint *base_print_new(void){
    BasePrint *ins;
    ins = g_object_new(BASE_PRINT_TYPE, 0);
    return ins;
}
void base_print_free(BasePrint *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(BASE,PRINT,self));
    g_object_unref(G_OBJECT(self));
}
