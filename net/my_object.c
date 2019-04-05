#include "my_object.h"
void my_object_dispose(MyObject *obj);
MyObjectClass vtable={
.dispose=my_object_dispose,
};
void my_object_free(MyObject *obj){
	obj->vtable->dispose(obj);
	free(obj);
}
void *my_object_create(int size){
	MyObject *ins=NULL;
	ins=(MyObject*)malloc(size);
	memset(ins,0,size);
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
void my_object_dispose(MyObject *obj){
printf("%s\n",__FUNCTION__);
}
