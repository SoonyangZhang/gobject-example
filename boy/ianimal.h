#ifndef EXAMPLE_IANIMAL_H_
#define EXAMPLE_IANIMAL_H_
#include <glib-object.h>
#define MY_TYPE_IANIMAL (my_ianimal_get_type ())
#define MY_IANIMAL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj),MY_TYPE_IANIMAL, MyIAnimal))
#define MY_IS_IANIMAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_TYPE_IANIMAL))
#define MY_IANIMAL_GET_INTERFACE(obj) (\
                G_TYPE_INSTANCE_GET_INTERFACE ((obj), MY_TYPE_IANIMAL, MyIAnimalInterface))


typedef struct _MyIAnimal MyIAnimal;
typedef struct _MyIAnimalInterface MyIAnimalInterface;

struct _MyIAnimalInterface {
    GTypeInterface parent_interface;
    void (*speak) (MyIAnimal *self, const char *str);
};
GType my_ianimal_get_type (void);
void my_ianimal_speak(MyIAnimal *animal,const char *str);
#endif /* EXAMPLE_IANIMAL_H_ */
