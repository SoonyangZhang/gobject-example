#ifndef MY_OBJECT_H_
#define MY_OBJECT_H_
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define MY_OBJECT(obj) ((MyObject*)obj)
#define MY_OBJECT_CLASS(kclass)  ((MyObjectClass*)kclass)
#define MY_OBJECT_VTABLE(obj)  (MY_OBJECT(obj)->vtable)

#define atomic_cas(dst, old, new) __sync_bool_compare_and_swap((dst), (old), (new))
#define atomic_lock(ptr)\
while(!atomic_cas(ptr,0,1))
#define atomic_unlock(ptr)\
while(!atomic_cas(ptr,1,0))

typedef struct _MyObject MyObject;
typedef struct _MyObjectClass MyObjectClass;
struct _MyObject{
	MyObjectClass *vtable;//quite tricky
	int lock;
	int count;
};

struct _MyObjectClass{
	void (*dispose)(MyObject*obj);
};
void *my_object_create(int size);
void *my_object_ref(MyObject *obj);
void my_object_unref(MyObject *obj);
MyObjectClass *my_object_vtable();
#endif /* MY_OBJECT_H_ */
