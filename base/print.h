#ifndef EXAMPLE_PRINT_H_
#define EXAMPLE_PRINT_H_
#include "irunnable.h"
#define MY_TYPE_PRINT (my_print_get_type ())
#define MY_PRINT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_TYPE_PRINT, MyPrint))
#define MY_IS_PRINT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_TYPE_PRINT))
#define MY_PRINT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_TYPE_PRINT, MyPrintClass))
#define MY_IS_PRINT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_TYPE_PRINT))
#define MY_PRINT_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_TYPE_PRINT,MyPrintClass))

typedef struct _MyPrint MyPrint;
typedef struct _MyPrintClass MyPrintClass;

struct _MyPrint{
    GObject parent;
    int conuter;
};
struct _MyPrintClass{
    GObjectClass parent_class;
};


GType my_print_get_type ();
MyPrint *my_print_new(void);
void my_print_free(MyPrint *self);
#endif /* EXAMPLE_PRINT_H_ */
