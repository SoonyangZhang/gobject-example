#include <glib-object.h>
#include "my_parent.h"
#define MY_CHILD_TYPE (my_child_get_type ())
#define MY_CHILD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_CHILD_TYPE, MyChild))
#define MY_IS_CHILD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_CHILD_TYPE))
#define MY_CHILD_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_CHILD_TYPE, MyChildClass))
#define MY_IS_CHILD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_CHILD_TYPE))
#define MY_CHILD_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_CHILD_TYPE,MyChildClass))

typedef struct _MyChild MyChild;
typedef struct _MyChildClass MyChildClass;
typedef struct _MyChildPriv MyChildPriv;
struct _MyChildPriv{
    gint b;
};
struct _MyChild{
    MyParent parent;
};
struct _MyChildClass{
    MyParentClass parent_class;
};


GType my_child_get_type (void);
MyChild *my_child_new(int a,int b);
void my_child_free(MyChild *self);
