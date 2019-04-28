/*
 * my_buffer.h
 * contain char
 */
#ifndef MY_CHAR_BUFFER_H_
#define MY_CHAR_BUFFER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "my_object.h"
typedef struct _MyCharBuffer MyCharBuffer;
typedef struct _MyCharBufferClass MyCharBufferClass;
struct _MyCharBuffer{
	MyObject root;
	char *c;
	int len;
};
struct _MyCharBufferClass{
	MyObjectClass root_class;
};
MyCharBuffer *my_char_buffer_new();
void my_char_buffer_init(MyCharBuffer*self);
void my_char_buffer_unref(MyCharBuffer*self);
void my_char_buffer_set(MyCharBuffer*self,char *c,int len);
#ifdef __cplusplus
}
#endif
#endif /* MY_CHAR_BUFFER_H_ */
