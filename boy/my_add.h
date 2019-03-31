#ifndef MY_ADD_H_
#define MY_ADD_H_
#include <glib-object.h>
#include <glib-object.h>
#ifdef __cplusplus
extern "C"
{
#endif
#define MY_ADD_TYPE (my_add_get_type ())
#define MY_ADD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_ADD_TYPE, MyAdd))
#define MY_IS_ADD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_ADD_TYPE))
#define MY_ADD_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_ADD_TYPE, MyAddClass))
#define MY_IS_ADD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_ADD_TYPE))
#define MY_ADD_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_ADD_TYPE,MyAddClass))

typedef struct _MyAdd MyAdd;
typedef struct _MyAddClass MyAddClass;

struct _MyAdd{
    GObject parent;
    int a;
};
struct _MyAddClass{
    GObjectClass parent_class;
    void (*virtual_add)(gpointer instance,gint int_value,gpointer userdata);
    void (*print)(MyAdd *self);
};


GType my_add_get_type (void);
MyAdd *my_add_new(void);
void my_add_free(MyAdd *self);
#ifdef __cplusplus
}
#endif

#endif

