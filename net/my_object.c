#include "my_object.h"
void my_object_dispose(MyObject *obj);
MyObjectClass vtable={
.dispose=my_object_dispose,
};
void my_object_free(MyObject *obj){
	obj->vtable->dispose(obj);
	free(obj);
}
MyObjectClass * my_object_vtable(){
	return &vtable;
}
void my_object_dispose(MyObject *obj){
printf("%s\n",__FUNCTION__);
}
