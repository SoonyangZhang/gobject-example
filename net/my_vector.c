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
	my_vector_init(ins);
	return ins;
}
void my_vector_init(MyVector *self){
	self->used=0;
	if(self->ele_size>0){
		self->eles=my_malloc(self->ele_size*INIT_VECTOR_SIZE);
		self->cap=INIT_VECTOR_SIZE;			
	}
}
void my_vector_dtor(MyVector *self){
	my_vector_dispose(self);
	if(self->eles){
		my_free(self->eles);
		self->eles=0;
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
	if(self->cap==0){
		my_vector_init(self);
	}
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
void *my_vector_begin(MyVector *self){
	void *itor=0;
	itor=self->eles;
	return itor;
}
void *my_vector_end(MyVector *self){
	void *itor=0;
	itor=(void*)(self->eles+self->used*self->ele_size);
	return itor;
}
void *my_vector_erase(MyVector *self,void *itor){
	void *next_addr=itor+self->ele_size;
	void *ret=0;
	int i=0;
	int index=(itor-self->eles)%self->ele_size;
	if(self->ele_dispose){
		self->ele_dispose(itor);
	}
	if(next_addr!=my_vector_end(self)){
		for(i=index;i<(self->used-1);i++){
			void *dst=self->eles+i*self->ele_size;
			void *src=self->eles+(i+1)*self->ele_size;
			memcpy(dst,src,self->ele_size);
		}
	}
	self->used--;
	ret=itor;
	return ret;
}
void my_vector_copy(MyVector *dst,MyVector *src){
	dst->ele_init=src->ele_init;
	dst->ele_copy=src->ele_copy;
	dst->ele_dispose=src->ele_dispose;
	dst->ele_size=src->ele_size;
	//my_vector_dispose(dst);
	//my_vector_reserve(dst,src->used);
	int i=0;
	for (i=0;i<src->used;i++){
		void *src_offset=src->eles+i*src->ele_size;
		my_vector_push_back(dst,src_offset);
	}
}
void my_vector_dispose(MyVector *self){
	int i=0;
	void *offset=0;
	for(i=0;i<self->used;i++){
		offset=self->eles+i*self->ele_size;
		if(self->ele_dispose){
			self->ele_dispose(offset);
		}
	}
	self->used=0;
}
