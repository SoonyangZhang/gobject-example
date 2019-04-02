#include "mbuf.h"
#include <stdio.h>
int main(){
	MyBuf *buf=my_buf_get();
	printf("%d\n",my_buf_write_size(buf));
	my_buf_recycle(buf);
	return 0;
}
