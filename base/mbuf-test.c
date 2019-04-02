#include "mbuf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define buf_len 23
int main(){
	char *data="hello world,hello fuck";
	my_buf_init();
	MyBuf *buf;
	MyHdr h;
	TAILQ_INIT(&h);
	my_buf_write_data(&h,data,strlen(data));
	buf=NULL;
	uint32_t readble=my_buf_total_readable_size(&h);
	printf("%d\n",readble);
	char read_buf[buf_len];
	memset(read_buf,0,buf_len);
	my_buf_read_data(&h,read_buf,buf_len-1);
	printf("%s\n",read_buf);
	readble=my_buf_total_readable_size(&h);
	printf("remain %d\n",readble);
	memset(read_buf,0,buf_len);
	if(readble){
	my_buf_read_data(&h,read_buf,buf_len-1);
	printf("%s\n",read_buf);
	}
	readble=my_buf_total_readable_size(&h);
	printf("remain %d\n",readble);
	int ret=0;
	ret=my_buf_read_data(&h,read_buf,buf_len-1);
	printf("ret %d\n",ret);	
	if(buf){
	my_buf_remove(&h,buf);
	my_buf_recycle(buf);		
	}
	return 0;
}
