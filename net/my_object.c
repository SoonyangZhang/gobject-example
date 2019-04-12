#include "my_object.h"
#include "alloc.h"
void my_object_null_dispose(MyObject *obj);
void my_object_null_copy(MyObject* src,MyObject* o);
MyObjectClass vtable={
.dispose=my_object_null_dispose,
.copy=my_object_null_copy,
};
void my_object_free(MyObject *obj){
	obj->vtable->dispose(obj);
	my_free(obj);
}
void *my_object_create(int size){
	MyObject *ins=NULL;
	ins=my_malloc(size);
	if(ins){
		ins->lock=0;
		ins->count=1;
	}
	return ins;
}
void *my_object_ref(MyObject *obj){
	MyObject *ins=NULL;
	atomic_lock(&obj->lock);
	if(obj->count){
		obj->count++;
		ins=obj;
	}
	atomic_unlock(&obj->lock);
	return ins;
}
void my_object_unref(MyObject *obj){
	atomic_lock(&obj->lock);
	if(obj->count){
		obj->count--;
	}
	atomic_unlock(&obj->lock);
	if(obj->count==0){
		my_object_free(obj);
	}
}
MyObjectClass * my_object_vtable(){
	return &vtable;
}
void my_object_null_dispose(MyObject *obj){
printf("%s\n",__FUNCTION__);
}
void my_object_null_copy(MyObject* src,MyObject* o){

}
void my_object_copy(MyObject* src,MyObject* o){
	src->vtable->copy(src,o);
}
void my_object_init(MyObject *obj){
	obj->vtable=my_object_vtable();
}
