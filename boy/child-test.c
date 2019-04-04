#include "my_child.h"
#include <glib.h>
//http://garfileo.is-programmer.com/
//https://blog.csdn.net/knowledgebao/article/details/82427406
int main(){
    MyChild *child=my_child_new(1,2);
    GValue value = {0};
    g_value_init(&value,G_TYPE_INT);
    g_value_set_int(&value, 400);
    g_object_set_property(G_OBJECT(child), "a", &value);
    g_value_unset (&value);
    
    GValue val = {0};
    g_value_init(&val,G_TYPE_INT);    
    g_object_get_property(G_OBJECT(child),"a",&val);
    int b=g_value_get_int(&val);
    g_value_unset (&val);
	GObject *root=G_OBJECT(child);
	g_print("obj %p, child %p\n",root,child);
    my_child_free(child);
    g_print("b %d\n",b);
	int arr[2];
	printf("%p, %p\n",&arr[0],&arr[1]);
}
