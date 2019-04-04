#ifndef MY_ADDCHILD_H_
#define MY_ADDCHILD_H_
#include <glib-object.h>
#include "my_add.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define MY_ADD_CHILD_TYPE (my_add_child_get_type ())
#define MY_ADDCHILD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_ADD_CHILD_TYPE, MyAddChild))
#define MY_IS_ADDCHILD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_ADD_CHILD_TYPE))
#define MY_ADDCHILD_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_ADD_CHILD_TYPE, MyAddChildClass))
#define MY_IS_ADDCHILD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_ADD_CHILD_TYPE))
#define MY_ADDCHILD_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_ADD_CHILD_TYPE,MyAddChildClass))

typedef struct _MyAddChild MyAddChild;
typedef struct _MyAddChildClass MyAddChildClass;

struct _MyAddChild{
    MyAdd parent;
};
struct _MyAddChildClass{
    MyAddClass parent_class;
};


GType my_add_child_get_type (void);
MyAddChild *my_add_child_new(void);
void my_add_child_free(MyAddChild *self);

#ifdef __cplusplus
}
#endif

#endif
