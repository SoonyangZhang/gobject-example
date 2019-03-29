#include "ianimal.h"
G_DEFINE_INTERFACE (MyIAnimal, my_ianimal, G_TYPE_INVALID);

static void
my_ianimal_default_init (MyIAnimalInterface *iface)
{
}
void my_ianimal_speak(MyIAnimal *self,const char *str){
    g_return_if_fail (MY_IS_IANIMAL(self));
    MY_IANIMAL_GET_INTERFACE (self)->speak(self, str);
}
