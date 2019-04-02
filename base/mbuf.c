#include "mbuf.h"
#include <string.h>
#include "alloc.h"
#define CHUNK_SIZE 32
static int mbuf_offset=0;
static int chunk_size=0;
static void __attribute__((constructor)) my_buf_init_before_main(void){
	my_buf_init();
}
MyBuf *my_buf_new(){
	MyBuf *mbuf=NULL;
	void *buf=my_malloc(chunk_size);
	if(buf){
		mbuf=(MyBuf*)(buf+mbuf_offset);
	}
	return mbuf;
}
void my_buf_free(MyBuf *mbuf){
	void *buf=NULL;
	if(mbuf){
		buf=mbuf-mbuf_offset;
		my_free(buf);
	}
}
void my_buf_init(){
	int struct_size=sizeof(MyBuf);
	if(CHUNK_SIZE<struct_size){
		chunk_size=2*struct_size;
	}else{
		chunk_size=CHUNK_SIZE;
	}
	mbuf_offset=chunk_size-struct_size;
}
void my_buf_destroy(){

}
MyBuf *my_buf_get(){
	MyBuf *mbuf=NULL;
	mbuf=my_buf_new();
	void *buf=mbuf-mbuf_offset;
	if(mbuf){
		mbuf->start=(uint8_t*)buf;
		mbuf->end=(uint8_t*)mbuf;
		mbuf->pos=(uint8_t*)buf;
		mbuf->last=(uint8_t*)buf;
	}
	return mbuf;
}
void my_buf_recycle(MyBuf *mbuf){
	my_buf_free(mbuf);
}
uint32_t my_buf_read_size(MyBuf *mbuf){
	return (mbuf->last-mbuf->pos);
}
uint32_t my_buf_write_size(MyBuf *mbuf){
	return (mbuf->end-mbuf->last);
}
uint32_t my_buf_peek(MyBuf *mbuf,void *dst,uint32_t len){
	uint32_t read_size=my_buf_read_size(mbuf);
	read_size=len>read_size?read_size:len;
	memcpy(dst,mbuf->pos,read_size);
	return read_size;
}
