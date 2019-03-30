#define BASE_PRINT_TYPE (base_print_get_type ())
#define BASE_PRINT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), BASE_PRINT_TYPE, BasePrint))
#define BASE_IS_PRINT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BASE_PRINT_TYPE))
#define BASE_PRINT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), BASE_PRINT_TYPE, BasePrintClass))
#define BASE_IS_PRINT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BASE_PRINT_TYPE))
#define BASE_PRINT_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),BASE_PRINT_TYPE,BasePrintClass))

typedef struct _BasePrint BasePrint;
typedef struct _BasePrintClass BasePrintClass;

struct _BasePrint{
    GObject parent;
};
struct _BasePrintClass{
    GObjectClass parent_class;
};


GType base_print_get_type (void);
BasePrint *base_print_new(void);
void base_print_free(BasePrint *self);
