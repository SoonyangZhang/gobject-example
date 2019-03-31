#include <glib-object.h>
#define MY_PARENT_TYPE (my_parent_get_type ())
#define MY_PARENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_PARENT_TYPE, MyParent))
#define MY_IS_PARENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_PARENT_TYPE))
#define MY_PARENT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_PARENT_TYPE, MyParentClass))
#define MY_IS_PARENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_PARENT_TYPE))
#define MY_PARENT_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_PARENT_TYPE,MyParentClass))

typedef struct _MyParent MyParent;
typedef struct _MyParentClass MyParentClass;
typedef struct _MyParentPriv MyParentPriv;
struct _MyParentPriv{
    int a;   
};
struct _MyParent{
    GObject parent;
    MyParentPriv priv;
};
struct _MyParentClass{
    GObjectClass parent_class;
};
GType my_parent_get_type (void);
MyParent *my_parent_new(void);
void my_parent_free(MyParent *self);
