#ifndef MY_STRING_H_
#define MY_STRING_H_
#include "my_object.h"
typedef struct _MyString MyString;
typedef struct _MyStringClass MyStringClass;
#define MY_STRING(obj) ((MyString*)obj)
#define MY_STRING_CLASS(kclass)((MyStringClass*)kclass)
#define my_string_call(obj,method,...)  do{\
MyStringClass *vtable=(MyStringClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(__VA_ARGS__);\
}while(0)
#define MY_STRING_FIELD \
char *buf;\
int cur_pos;\
int cap
struct _MyString{
	MyObject root;
	MY_STRING_FIELD;
};
struct _MyStringClass{
	MyObjectClass root_class;
};
MyString *my_string_new0();
MyString *my_string_new(char *content,int len);
void my_string_init(MyString *self);
void my_string_unref(MyString *self);
MyStringClass *my_string_vtable();
#endif /* MY_STRING_H_ */
