#include "alloc.h"
#include <stdlib.h>
void *my_malloc(int size){
	return malloc(size);
}
void my_free(void *ptr){
	free(ptr);
}


