#include "lazy_micro.h"
#include "my_parent.h"
G_DEFINE_TYPE (MyParent, my_parent, G_TYPE_OBJECT);
/*将私有成员PMDListPrivate注册到GObject中，后续通过宏PM_DLIST_GET_PRIVATE作为获取私有成员变量的唯一入口，如果需要生效，需要在class_init中注册此变量*/
#define MY_PARENT_GET_PRIVATE(obj) \
        G_TYPE_INSTANCE_GET_PRIVATE ((obj),MY_PARENT_TYPE,MyParentPriv)
enum{
PROP_0,//must
PROP_A,
};
void my_parent_dispose(GObject *gobject){
    G_OBJECT_CLASS (my_parent_parent_class)->dispose(gobject);
}
void my_parent_finalize(GObject *gobject){
    G_OBJECT_CLASS (my_parent_parent_class)->finalize(gobject);
}
void my_parent_set_prop(GObject      *object,
                   guint         prop_id,
                   const GValue *value,
                   GParamSpec   *pspec){
	MyParent *self=MY_PARENT(object);
    MyParentPriv *priv=MY_PARENT_GET_PRIVATE(self);
	switch(prop_id){
	case PROP_A:{
		priv->a=g_value_get_int(value);
		break;
	}
	default:{
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
	}
	}
}
void my_parent_get_prop(GObject    *object,
                   guint       prop_id,
                   GValue     *value,
                   GParamSpec *pspec){
	MyParent *self=MY_PARENT(object);
    MyParentPriv *priv=MY_PARENT_GET_PRIVATE(self);
	switch(prop_id){
	case PROP_A:{
		g_value_set_int(value,priv->a);
		break;
	}
	default:{
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
	}
	}
}
static void my_parent_init(MyParent *self){

}
static void my_parent_class_init(MyParentClass *kclass){
    g_type_class_add_private (kclass, sizeof (MyParentPriv));
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_parent_dispose;
    base_class->finalize      = my_parent_finalize;
    base_class->set_property=my_parent_set_prop;
    base_class->get_property=my_parent_get_prop;
    
    g_object_class_install_property (base_class, PROP_A,
                                     g_param_spec_int ("a",
                                                        "A",
                                                        "The A",
                                                        -1,
                                                        G_MAXINT,
                                                        -1,
                                                        G_PARAM_READWRITE));

}
MyParent *my_parent_new(void){
    MyParent *ins;
    ins = g_object_new(MY_PARENT_TYPE, 0);
    return ins;
}
void my_parent_free(MyParent *self){
    g_assert(self!= NULL);
    g_return_if_fail(lazy_is_obj(MY,PARENT,self));
    g_object_unref(G_OBJECT(self));
}
