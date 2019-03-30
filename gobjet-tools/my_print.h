#define MY_PRINT_TYPE (my_print_get_type ())
#define MY_PRINT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_PRINT_TYPE, MyPrint))
#define MY_IS_PRINT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_PRINT_TYPE))
#define MY_PRINT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_PRINT_TYPE, MyPrintClass))
#define MY_IS_PRINT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_PRINT_TYPE))
#define MY_PRINT_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_PRINT_TYPE,MyPrintClass))

typedef struct _MyPrint MyPrint;
typedef struct _MyPrintClass MyPrintClass;

struct _MyPrint{
    GObject parent;
};
struct _MyPrintClass{
    GObjectClass parent_class;
};


GType my_print_get_type (void);
MyPrint *my_print_new(void);
void my_print_free(MyPrint *self);
