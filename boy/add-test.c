#include "my_add.h"
#include <stdio.h>
void add1(gpointer instance,gint offset,gpointer userdata){
    g_print("%s,%p,%d\n",__FUNCTION__,instance,offset);
    MyAdd *self=MY_ADD(instance);
    int base=1;
    base+=offset;
    self->a=self->a+base;
}
void add2(gpointer instance,gint offset,gpointer userdata){
    g_print("%s,%d\n",__FUNCTION__,offset);
    MyAdd *self=MY_ADD(instance);
    int base=2;
    base+=offset;
    self->a=self->a+base;
}
void monitor(gpointer instance,gint offset,gpointer userdata){
    g_print("%s,%d\n",__FUNCTION__,offset);
    g_print("userdata %p\n",userdata);
    /*gchar *str=(gchar *)userdata;
    if(str){
        g_print ("monitor: %s\n",str);
    }*/
}
int main(){
    MyAdd *obj1=my_add_new();
    MyAdd *obj2=my_add_new();
    MyAddClass *kclass;
    kclass=MY_ADD_GET_CLASS(obj1);
    kclass->virtual_add=add1;
    int a=1;
    int b=2;
    g_print("b address %p\n",&b);
    gchar *userdata = "This is userdata";
    g_signal_connect (obj1, "add", 
                      G_CALLBACK (monitor), 
                      &b);    
    g_signal_emit_by_name(obj1,"add",a,G_TYPE_NONE);
    kclass->print(obj1);
    kclass=MY_ADD_GET_CLASS(obj2);
    kclass->virtual_add=add2;
    g_signal_emit_by_name(obj2,"add",a,G_TYPE_NONE);
    kclass->print(obj2);
    my_add_free(obj1);
    my_add_free(obj2);
    return 0;
}
