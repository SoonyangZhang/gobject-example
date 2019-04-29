#ifndef MY_STRING_H_
#define MY_STRING_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "my_char_buffer.h"
typedef struct _MyString MyString;
typedef struct _MyStringClass MyStringClass;
#define MY_STRING(obj) ((MyString*)obj)
#define MY_STRING_CLASS(kclass)((MyStringClass*)kclass)
#define my_string_call(obj,method,...)  do{\
MyStringClass *vtable=(MyStringClass*)MY_OBJECT_VTABLE(obj);\
vtable->method(__VA_ARGS__);\
}while(0)
struct _MyString{
	MyObject root;
	MyCharBuffer *buf;
};
struct _MyStringClass{
	MyObjectClass root_class;
};
MyString *my_string_new0();
MyString *my_string_new(char *content,int len);
void my_string_init(MyString *self);
void my_string_unref(MyString *self);
int my_string_len(MyString *self);
void my_string_copy(MyString *dst,MyString *src);
bool mu_string_equal(MyString *a,MyString *c);
void my_string_dispose(MyString *self);
#ifdef __cplusplus
}
#endif
#endif /* MY_STRING_H_ */
