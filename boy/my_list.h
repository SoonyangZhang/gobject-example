#ifndef MY_LIST_H_
#define MY_LIST_H_
#include <glib-object.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define MY_LIST_TYPE (my_list_get_type ())
#define MY_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_LIST_TYPE, MyList))
#define MY_IS_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_LIST_TYPE))
#define MY_LIST_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_LIST_TYPE, MyListClass))
#define MY_IS_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_LIST_TYPE))
#define MY_LIST_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_LIST_TYPE,MyListClass))

typedef struct _MyList MyList;
typedef struct _MyListClass MyListClass;
typedef struct _MyNode MyNode;
struct _MyNode{
    MyNode *prev;
    MyNode *next;
    uint8_t type;
    uint8_t data_size;
    uint8_t *data;
};

struct _MyList{
    GObject parent;
    int size;
    MyNode* head;
    MyNode* tail;
};
struct _MyListClass{
    GObjectClass parent_class;
    void (*push_back)(MyList *self,void *data,size_t len,uint8_t type);
    void (*push_front)(MyList *self,void *data,size_t len,uint8_t type);
    int (*pop_back)(MyList *self,void *dst,size_t len);
    int (*pop_front)(MyList *self,void *dst,size_t len);
    uint8_t (*peek_front_size)(MyList *self);
    uint8_t (*peek_back_size)(MyList *self);
    uint8_t (*peek_front_type)(MyList *self);
    uint8_t (*peek_back_type)(MyList *self);
};


GType my_list_get_type (void);
MyList *my_list_new(void);
void my_list_free(MyList *self);
int my_list_size(MyList *self);
#ifdef __cplusplus
}
#endif

#endif
