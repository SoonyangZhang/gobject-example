#include <glib.h>
#include "boy.h"
#include <stdio.h>
int main(){
    g_type_init();
	GObjectClass *class=NULL;
	class=g_type_class_peek_static(BOY_TYPE);
	printf("%p\n",class);
    return 0;
}
