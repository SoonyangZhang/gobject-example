#ifndef MBUF_H_
#define MBUF_H_
#include <stdint.h>
#include "queue.h"
typedef struct _MyBuf MyBuf;
struct _MyBuf{
    TAILQ_ENTRY(MyBuf) next;
    uint8_t *pos;//read marker
    uint8_t *last;//write marker
    uint8_t *start;//start of buf
    uint8_t *end; //end of buf
};
TAILQ_HEAD(MyHdr, MyBuf);
void my_buf_init();
void my_buf_destroy();
MyBuf *my_buf_get();
void my_buf_recycle(MyBuf *mbuf);
uint32_t my_buf_read_size(MyBuf *mbuf);
uint32_t my_buf_write_size(MyBuf *mbuf);
uint32_t my_buf_peek(MyBuf *mbuf,void *dst,uint32_t len);

#endif /* MBUF_H_ */
