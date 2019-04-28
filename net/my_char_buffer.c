#include "my_char_buffer.h"
#include "alloc.h"
#include <string.h>
#include <stdio.h>
static MyCharBufferClass default_vtable;
static bool class_inited=false;
static char *name="MyCharBuffer";
static MyCharBufferClass* my_char_buffer_vtable();
MyCharBuffer *my_char_buffer_new(){
	MyCharBuffer *ins=0;
	ins=(MyCharBuffer*)my_object_create(sizeof(MyCharBuffer));
	my_char_buffer_init(ins);
	return ins;
}
void my_char_buffer_init(MyCharBuffer*self){
	if(!self){
		return;
	}
	my_object_init(MY_OBJECT(self));
	my_object_set_name(MY_OBJECT(self),name);
	MY_OBJECT_VTABLE(self)=my_char_buffer_vtable();
	self->c=0;
	self->len=0;
}
void my_char_buffer_unref(MyCharBuffer*self){
	my_object_unref(MY_OBJECT(self));
}
void my_char_buffer_dispose(MyCharBuffer*self){
	if(self->len>0&&self->c){
		my_free(self->c);
		self->len=0;
	}
	MyObjectClass *parent_class=my_object_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(self));
}
void my_char_buffer_copy(MyCharBuffer *dst,MyCharBuffer *src){
	my_char_buffer_set(dst,src->c,src->len);
}
void my_char_buffer_class_init(){
	class_inited=true;
	MyCharBufferClass *kclass=&default_vtable;
	MyObjectClass *parent=my_object_vtable();
	memcpy(kclass,parent,sizeof(*parent));
	MY_OBJECT_CLASS(kclass)->dispose=my_char_buffer_dispose;
	MY_OBJECT_CLASS(kclass)->copy=my_char_buffer_copy;
}
static MyCharBufferClass* my_char_buffer_vtable(){
	if(!class_inited){
		my_char_buffer_class_init();
	}
	return &default_vtable;
}
void my_char_buffer_set(MyCharBuffer*self,char *c,int len){
	if(self->len>0){
		my_free(self->c);
		self->c=0;
		self->len=0;
	}
	if(len>0){
		self->len=len;
		self->c=(char*)my_malloc(sizeof(char)*self->len);
		memcpy(self->c,c,self->len);
	}
}


