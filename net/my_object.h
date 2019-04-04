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
typedef struct _MyObject MyObject;
typedef struct _MyObjectClass MyObjectClass;
struct _MyObject{
	MyObjectClass *vtable;//quite tricky
};
struct _MyObjectClass{
	void (*dispose)(MyObject*obj);
};
void my_object_free(MyObject *obj);
MyObjectClass *my_object_vtable();
#endif /* MY_OBJECT_H_ */
