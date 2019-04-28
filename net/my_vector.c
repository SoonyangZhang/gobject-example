#include "my_vector.h"
#include "alloc.h"
#include <string.h>
#define INIT_VECTOR_SIZE 2
static my_vector_reserve(MyVector *self,int inc);
MyVector *my_vector_new(int ele_size,EleInit init,
		EleDispose dispose,EleCopy copy){
	MyVector *ins=0;
	ins=(MyVector*)my_malloc(sizeof(MyVector));
	ins->ele_size=ele_size;
	ins->ele_init=init;
	ins->ele_dispose=dispose;
	ins->ele_copy=copy;
	ins->used=0;
	ins->eles=my_malloc(ins->ele_size*INIT_VECTOR_SIZE);
	ins->cap=INIT_VECTOR_SIZE;
	return ins;
}
void my_vector_dtor(MyVector *self){
	int i=0;
	void *offset=0;
	for(i=0;i<self->used;i++){
		offset=self->eles+i*self->ele_size;
		if(self->ele_dispose){
			self->ele_dispose(offset);
		}
	}
	if(self->eles){
		my_free(self->eles);
		self->eles=0;
		self->used=0;
		self->cap=0;
	}
	my_free(self);
}
void my_vector_push_back(MyVector *self,const void *ele){
	my_vector_reserve(self,1);
	void *offset=(void*)(self->eles+self->used*self->ele_size);
	if(self->ele_copy){
		if(self->ele_init){//init must be called first
			self->ele_init(offset);
		}
		self->ele_copy(offset,ele);

	}
	self->used+=1;
}
static my_vector_reserve(MyVector *self,int inc){
	int base=self->cap;
	int occupy=self->used+inc;
	if(occupy>base){
		do{
			base*=2;
		}while(occupy>base);
		void *old_addr=self->eles;
		void *new_addr=my_malloc(base*self->ele_size);
		memcpy(new_addr,old_addr,self->used*self->ele_size);
		self->eles=new_addr;
		my_free(old_addr);
		self->cap=base;
	}
}


