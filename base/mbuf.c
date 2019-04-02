#include "mbuf.h"
#include <string.h>
#include <stdbool.h>
#include "alloc.h"
#define CHUNK_SIZE 64
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
	uint8_t *buf=NULL;
	if(mbuf){
		buf=(uint8_t*)mbuf-mbuf_offset;
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
	uint8_t *buf=(uint8_t*)mbuf-mbuf_offset;
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
bool is_buf_wrote_full(MyBuf *mbuf){
	return mbuf->last==mbuf->end;
}
uint32_t my_buf_peek(MyBuf *mbuf,void *dst,uint32_t len){
	uint32_t read_size=my_buf_read_size(mbuf);
	read_size=len>read_size?read_size:len;
	memcpy(dst,mbuf->pos,read_size);
	return read_size;
}
uint32_t my_buf_data_size(){
	return mbuf_offset;
}
void my_buf_insert(MyHdr *h,MyBuf *mbuf){
	TAILQ_INSERT_TAIL(h,mbuf,next);
}
void my_buf_remove(MyHdr *h,MyBuf *mbuf){
	TAILQ_REMOVE(h,mbuf,next);
	TAILQ_NEXT(mbuf,next)=NULL;
}
void my_buf_write_data(MyHdr *h,void *src,uint32_t len){
	MyBuf *last=TAILQ_LAST(h,_MyHdr);
	int offset=0;
	int remain=len;
	if(last==NULL){
		last=my_buf_get();
		my_buf_insert(h,last);
	}
	while(remain>0){
		last=TAILQ_LAST(h,_MyHdr);
		int write_size=my_buf_write_size(last);
		if(write_size==0){
			last=my_buf_get();
			write_size=my_buf_write_size(last);
			my_buf_insert(h,last);
		}
		int write=0;
		write=write_size>remain?remain:write_size;
		memcpy(last->last,src+offset,write);
		last->last+=write;
		offset+=write;
		remain-=write;
	}
}
uint32_t my_buf_total_readable_size(MyHdr *h){
	MyBuf *buf=NULL;
	uint32_t readable=0;
	TAILQ_FOREACH(buf,h,next){
		uint32_t read=my_buf_read_size(buf);
		readable+=read;
	}
	return readable;
}
int my_buf_read_data(MyHdr *h,void *dst,uint32_t len){
	
	int readable=0;
	int total_readable=my_buf_total_readable_size(h);
	int read=total_readable>len?len:total_readable;
	int remain=read;
	int offset=0;
	if(read){
		while(remain>0){
			MyBuf *first=TAILQ_FIRST(h);
			readable=my_buf_read_size(first);
			int read_size=readable>remain?remain:readable;
			bool is_full=is_buf_wrote_full(first);
			memcpy(dst+offset,first->pos,read_size);
			first->pos+=read_size;
			if(is_full&&(remain>=readable)){
				my_buf_remove(h,first);
				my_buf_recycle(first);
			}
			offset+=read_size;
			remain-=read_size;
		}
	}
	return read;
}
