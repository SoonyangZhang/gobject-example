#include "lazy_micro.h"
#include "my_list.h"
#include <memory.h>
#include <stdlib.h>
G_DEFINE_TYPE (MyList, my_list, G_TYPE_OBJECT);
uint8_t my_peek_back_size(MyList *self);
uint8_t my_peek_front_size(MyList *self);
void my_node_free(MyNode *node);
void my_list_dispose(GObject *gobject){
    g_print("%s\n",__FUNCTION__);   
    G_OBJECT_CLASS (my_list_parent_class)->dispose(gobject);
}
void my_list_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_list_parent_class)->finalize(gobject);
}
void my_node_free(MyNode *node){
    if(node){
        if(node->data){free(node->data);}
        free(node);
    }
}
MyNode* my_node_new(uint8_t data_size){
    MyNode* node=NULL;
    uint8_t *data=(uint8_t*)calloc(1,data_size);
    if(data){
        node=(MyNode*)calloc(1,sizeof(MyNode));
        if(node){
            node->data_size=data_size;
            node->data=data;
        }else{
            free(data);
            data=NULL;
        }
    }
    return node;  
}
void my_push_back(MyList *self,void *data,size_t len,uint8_t type){
    MyNode *node=my_node_new(len);
    node->type=type;
    node->data_size=len;
    memcpy(node->data,data,len);
    MyNode *head=self->head;
    MyNode *tail=self->tail;
    if((!tail)&&(!head)){
        self->tail=node;
        self->head=node;
    }else{
        tail->next=node;
        node->prev=tail;
        self->tail=node;
    }
    self->size++;
}
void my_push_front(MyList *self,void *data,size_t len,uint8_t type){
    MyNode *node=my_node_new(len);
    node->type=type;
    node->data_size=len;
    memcpy(node->data,data,len);
    MyNode *head=self->head;
    MyNode *tail=self->tail;
    if(!tail&&!head){
        self->tail=node;
        self->head=node;
    }else{
        node->next=head;
        head->prev=node;
        self->head=node;
    }
    self->size++;    
}
int my_pop_front(MyList *self,void *dst,size_t len){
    int ret=0;
    ret=my_peek_front_size(self);
    if(ret){
        MyNode *head=self->head;
        MyNode *next=head->next;
        self->head=next;
        if(next){
            next->prev=NULL;
        }
        size_t data_size=head->data_size;
        size_t copy=len>data_size?data_size:len;
        memcpy(dst,head->data,copy);
        my_node_free(head);
        self->size--;
    }
    return ret;
}
int my_pop_back(MyList *self,void *dst,size_t len){
    int ret=0;
    ret=my_peek_front_size(self);
    if(ret){
        MyNode *tail=self->tail;
        MyNode *prev=tail->prev;
        self->tail=prev;
        if(prev){
            prev->next=NULL;
        }
        size_t data_size=tail->data_size;
        size_t copy=len>data_size?data_size:len;
        memcpy(dst,tail->data,copy);
        my_node_free(tail);
        self->size--;    
    }  
    return ret;
}
uint8_t my_peek_front_size(MyList *self){
    uint8_t ret=0;
    if(self->head){
        ret=self->head->data_size;
    }
    return ret;
}
uint8_t my_peek_back_size(MyList *self){
    uint8_t ret=0;
    if(self->tail){
        ret=self->tail->data_size;
    }
    return ret;    
}
uint8_t my_peek_front_type(MyList *self){
    uint8_t type=0;
    if(self->head){
        type=self->head->type;
    }
    return type;    
}
uint8_t my_peek_back_type(MyList *self){
    uint8_t type=0;
    if(self->tail){
        type=self->tail->type;
    }
    return type;    
}
static void my_list_init(MyList *self){
    self->size=0;
    self->head=NULL;
    self->tail=NULL;
}
static void my_list_class_init(MyListClass *kclass){
    kclass->push_back=my_push_back;
    kclass->push_front=my_push_front;
    kclass->pop_back=my_pop_back;
    kclass->pop_front=my_pop_front;
    kclass->peek_front_size=my_peek_front_size;
    kclass->peek_back_size=my_peek_back_size;
    kclass->peek_front_type=my_peek_front_type;
    kclass->peek_back_type=my_peek_back_type;
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_list_dispose;
    base_class->finalize      = my_list_finalize;
    
}
MyList *my_list_new(void){
    MyList *ins;
    ins = g_object_new(MY_LIST_TYPE, 0);
    return ins;
}
void my_list_free(MyList *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,LIST,self));
    g_object_unref(G_OBJECT(self));
    while(self->head){
        MyNode *head=self->head;
        MyNode *next=head->next;
        if(next){
            next->prev=NULL;
        }
        self->head=next;
        my_node_free(head);
        self->size--;
    }
    self->tail=NULL;
}
int my_list_size(MyList *self){
   int ret=0;
   if(self){
       ret=self->size;
   }
   return ret;
}
