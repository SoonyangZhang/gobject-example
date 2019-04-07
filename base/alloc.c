#include <stdlib.h>
#include <string.h>
#include "alloc.h"
void *my_malloc(int size){
	void *ins=NULL;
	ins=malloc(size);
	if(ins){
		memset(ins,0,size);
	}
	return ins;
}
void my_free(void *ptr){
	free(ptr);
}
void *my_realloc(void*origin,int size){
	return realloc(origin,size);
}


