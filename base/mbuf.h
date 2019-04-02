#ifndef MBUF_H_
#define MBUF_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "queue.h"
typedef struct _MyBuf MyBuf;
typedef struct _MyHdr MyHdr;
struct _MyBuf{
    TAILQ_ENTRY(_MyBuf) next;
    uint8_t *pos;//read marker
    uint8_t *last;//write marker
    uint8_t *start;//start of buf
    uint8_t *end; //end of buf
};
TAILQ_HEAD(_MyHdr, _MyBuf);
void my_buf_init();
void my_buf_destroy();
MyBuf *my_buf_get();
void my_buf_recycle(MyBuf *mbuf);
uint32_t my_buf_read_size(MyBuf *mbuf);
uint32_t my_buf_write_size(MyBuf *mbuf);
uint32_t my_buf_peek(MyBuf *mbuf,void *dst,uint32_t len);
uint32_t my_buf_data_size();
void my_buf_insert(MyHdr *h,MyBuf *mbuf);
void my_buf_remove(MyHdr *h,MyBuf *mbuf);
uint32_t my_buf_total_readable_size(MyHdr *h);
void my_buf_write_data(MyHdr *h,void *src,uint32_t len);
int my_buf_read_data(MyHdr *h,void *dst,uint32_t len);
#ifdef __cplusplus
}
#endif

#endif /* MBUF_H_ */
