#ifndef ALLOC_H_
#define ALLOC_H_
void *my_malloc(int size);
void my_free(void *ptr);
void *my_realloc(void*origin,int size);
#endif /* ALLOC_H_ */
