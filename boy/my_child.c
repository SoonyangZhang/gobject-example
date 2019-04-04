#include "lazy_micro.h"
#include "my_child.h"
G_DEFINE_TYPE (MyChild, my_child, MY_PARENT_TYPE);
#define MY_CHILD_GET_PRIVATE(obj) \
        G_TYPE_INSTANCE_GET_PRIVATE ((obj),MY_CHILD_TYPE,MyChildPriv)
enum{
PROP_0,//must
PROP_B,
};
void my_child_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_child_parent_class)->dispose(gobject);
}
void my_child_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_child_parent_class)->finalize(gobject);
}
static void my_child_init(MyChild *self){

}
void my_child_set_prop(GObject      *object,
                   guint         prop_id,
                   const GValue *value,
                   GParamSpec   *pspec){
	MyChild *self=MY_CHILD(object);
	MyChildPriv *priv=MY_CHILD_GET_PRIVATE(self);
	g_print("priv addr b %p\n",priv);
	switch(prop_id){
	case PROP_B:{
		priv->b=g_value_get_int(value);
		break;
	}

	default:{
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
	}
	}
}
void my_child_get_prop(GObject    *object,
                   guint       prop_id,
                   GValue     *value,
                   GParamSpec *pspec){
	MyChild *self=MY_CHILD(object);
	MyChildPriv *priv=MY_CHILD_GET_PRIVATE(self);
	switch(prop_id){
	case PROP_B:{
		g_value_set_int(value,priv->b);
		break;
	}
	default:{
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
	}
	}
}
static void my_child_class_init(MyChildClass *kclass){
	g_type_class_add_private (kclass, sizeof (MyChildPriv));
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_child_dispose;
    base_class->finalize      = my_child_finalize;
    base_class->set_property=my_child_set_prop;
    base_class->get_property=my_child_get_prop;

    g_object_class_install_property (base_class, PROP_B,
                                     g_param_spec_int ("b",
                                                        "B",
                                                        "The B",
                                                        -1,
                                                        G_MAXINT,
                                                        -1,
                                                        G_PARAM_READWRITE));
}
MyChild *my_child_new(int a,int b){
    MyChild *ins;
    ins = g_object_new(MY_CHILD_TYPE,"a",a,"b",b, 0);
    return ins;
}
void my_child_free(MyChild *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,CHILD,self));
    g_object_unref(G_OBJECT(self));
}
