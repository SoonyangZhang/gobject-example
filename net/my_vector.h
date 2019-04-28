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
void my_vector_dtor(MyVector *self);
void my_vector_push_back(MyVector *self,const void *ele);
#ifdef __cplusplus
}
#endif
#endif /* MY_VECTOR_H_ */
