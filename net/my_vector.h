#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_
#ifdef __cplusplus
extern "C" {
#endif
typedef struct _MyVector MyVector;
typedef void (*EleInit)(void *obj);
typedef void (*EleDispose)(void *obj);
typedef void (*EleCopy)(void *dst,void *src);
struct _MyVector{
	int ele_size;
	EleInit ele_init;
	EleDispose ele_dispose;
	EleCopy ele_copy;
	void *eles;
	int used;
	int cap;
};
MyVector *my_vector_new(int ele_size,EleInit init,
		EleDispose dispose,EleCopy copy);
void my_vector_init(MyVector *self);
void my_vector_dtor(MyVector *self);
void my_vector_push_back(MyVector *self,const void *ele);
void *my_vector_begin(MyVector *self);
void *my_vector_end(MyVector *self);
// here itor must by casted to void*,or else, itor+1 is not the addr of next ele;
#define my_vector_itor_plusplus(self,itor) (itor=((void*)itor+self->ele_size))
void my_vector_copy(MyVector *dst,MyVector *src);
void my_vector_dispose(MyVector *self);
#ifdef __cplusplus
}
#endif
#endif /* MY_VECTOR_H_ */
