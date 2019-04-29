#include "my_string.h"
#include <string.h>
static MyStringClass default_vtable;
static bool class_inited=false;
static char *name="MyString";
static MyStringClass *my_string_vtable();
void my_string_dispose(MyString *self){
	//why unref buf again, for example, this object may inited on buffer in vector, 
	//this dispose function can be called directly.
	if(self->buf){
		my_char_buffer_unref(self->buf);
		self->buf=NULL;
	}
	MyObjectClass *parent_class=my_object_vtable();
	MY_OBJECT_CLASS(parent_class)->dispose(MY_OBJECT(self));
}
void my_string_copy(MyString *dst,MyString *src){
	if(dst->buf){
		my_char_buffer_unref(dst->buf);
		dst->buf=0;
	}
	if(src->buf){
		dst->buf=my_object_ref(MY_OBJECT(src->buf));
	}	
}
static MyStringClass *my_string_vtable(){
	if(!class_inited){
		my_string_class_init();
	}
	return &default_vtable;
}
MyString *my_string_new0(){
	MyString *ins=(MyString*)my_object_create(sizeof(MyString));
	my_string_init(ins);
	return ins;
}
MyString *my_string_new(char *content,int len){
	MyString *ins;
	ins=my_string_new0();
	ins->buf=my_char_buffer_new();
	my_char_buffer_set(ins->buf,content,len);
	return ins;
}
void my_string_unref(MyString *self){
	if(self->buf){
		my_char_buffer_unref(self->buf);
		self->buf=NULL;		
	}
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
	my_object_init(MY_OBJECT(self));
	my_object_set_name(MY_OBJECT(self),name);
	MY_OBJECT_VTABLE(self)=my_string_vtable();
	self->buf=0;	
}
int my_string_len(MyString *self){
	int len=0;
	if(self->buf){
		len=self->buf->len;
	}
	return len;
}
bool my_string_equal(MyString *a,MyString *b){
	bool ret=false;
	if(a&&b&&a->buf&&b->buf){
		if(a->buf==b->buf){
			ret=true;
		}else if(a->buf->len==a->buf->len){
			if(memcmp(a->buf->c,b->buf->c,a->buf->len)==0){
				ret=true;
			}
		}
	}
	return ret;
}
