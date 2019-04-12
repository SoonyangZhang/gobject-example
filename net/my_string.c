#include "my_string.h"
MyStringClass default_vtable;
static bool class_inited=false;
void my_string_dispose(MyString *self){
	if(self->buf){
		my_free(self->buf);
		self->cur_pos=0;
		self->cap=0;
		self->buf=NULL;
	}
	MyObjectClass *parent_class=my_object_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(self));
}
void my_string_copy(MyString *self,MyString *o){

}
MyStringClass *my_string_vtable(){
	if(!class_inited){
		my_string_class_init();
	}
	return &default_vtable;
}
MyString *my_string_new0(){
	MyString *ins=(MyString*)my_malloc(sizeof(MyString));
	my_string_init(ins);
	return ins;
}
MyString *my_string_new(char *content,int len){
	MyString *ins;
	ins=my_string_new0();
	ins->buf=(char*)my_malloc(sizeof(char)*(len+1));
	ins->cap=len;
	memcpy(ins->buf,content,len);
}
void my_string_unref(MyString *self){
	my_object_unref(MY_OBJECT(self));
}
void my_string_class_init(){
	class_inited=true;
	MyStringClass *kclass=&default_vtable;
	MyObjectClass *parent=my_object_vtable();
	memcpy(kclass,parent,sizeof(*parent));

	MY_OBJECT_CLASS(kclass)->dispose=my_string_dispose;
	MY_OBJECT_CLASS(kclass)->copy=my_string_copy;
}
void my_string_init(MyString *self){
	if(!self){
		return ;
	}
	my_object_init(self);
	MY_OBJECT_VTABLE(self)=my_string_vtable();
	self->buf=NULL;
	self->cap=0;
	self->cur_pos=0;
	
}

