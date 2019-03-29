#include "human.h"
static void my_iusb_interface_init (MyIUsbInterface *iface);
static void my_ihuman_interface_init(MyIAnimalInterface *iface);
//http://web.mit.edu/barnowl/src/glib/glib-2.16.3/gobject/tests/threadtests.c
G_DEFINE_TYPE_WITH_CODE (MyHuman, my_human, G_TYPE_OBJECT,
G_IMPLEMENT_INTERFACE (MY_TYPE_IUSB, my_iusb_interface_init);
G_IMPLEMENT_INTERFACE(MY_TYPE_IANIMAL,my_ihuman_interface_init);
);


void human_dispose(GObject *gobject){
	MyHuman *human = MY_HUMAN(gobject);
	g_string_free(human->data,TRUE);
	g_print("%s free string\n",human->name);
	G_OBJECT_CLASS (my_human_parent_class)->dispose(gobject);
}
void human_finalize(GObject *gobject){
	G_OBJECT_CLASS (my_human_parent_class)->finalize(gobject);
}
static void my_human_init(MyHuman *self){
	self->data = g_string_new (NULL);
}
static void my_human_class_init(MyHumanClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = human_dispose;
    base_class->finalize     = human_finalize;
}

gchar * human_read(MyIUsb *iusb){
    MyHuman *human = MY_HUMAN(iusb);
    return human->data->str;
}
void human_write(MyIUsb *iusb, const gchar *str){
    MyHuman *human = MY_HUMAN (iusb);
    g_string_assign (human->data, str);
}
void human_speak(MyIAnimal *self, const char *str){
	g_print("human_speak: %s\n",str);
}
static void my_iusb_interface_init (MyIUsbInterface *iface){
	iface->read=human_read;
	iface->write=human_write;
}
static void my_ihuman_interface_init(MyIAnimalInterface *iface){
	iface->speak=human_speak;
}
MyHuman *my_human_new_with_name(char *name){
    MyHuman *human;
    human = g_object_new(MY_TYPE_HUMAN, 0);
    human->name=name;
    return human;
}
void my_human_free(MyHuman *human){
    g_assert(human!= NULL);
    g_return_if_fail(MY_IS_HUMAN(human));
    g_object_unref(G_OBJECT(human));
}

