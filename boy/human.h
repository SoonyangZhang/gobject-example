#ifndef EXAMPLE_HUMAN_H_
#define EXAMPLE_HUMAN_H_
#include "iusb.h"
#include "ianimal.h"
#define MY_TYPE_HUMAN (my_human_get_type ())
#define MY_HUMAN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_TYPE_HUMAN, MyHuman))
#define MY_IS_HUMAN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_TYPE_HUMAN))
#define MY_HUAMN_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_TYPE_HUMAN, MyHumanClass))
#define MY_IS_HUAMN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_TYPE_HUMAN))
#define MY_HUAMN_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_TYPE_HUMAN,MyHumanClass))

typedef struct _MyHuman MyHuman;
typedef struct _MyHumanClass MyHumanClass;

struct _MyHuman{
	GObject parent;
	char *name;
	GString *data;
};
struct _MyHumanClass{
	GObjectClass parent_class;
};
GType my_human_get_type ();
MyHuman *my_human_new_with_name(char *name);
void my_human_free(MyHuman *human);
#endif /* EXAMPLE_HUMAN_H_ */
