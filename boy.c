/* boy.c */
#include "boy.h"
enum { BOY_BORN, LAST_SIGNAL };
//https://blog.csdn.net/chen_jianjian/article/details/79855345
static gpointer boy_parent_class = NULL;
static gint boy_signals[LAST_SIGNAL] = { 0 };
static void boy_cry (void);
static void boy_born(void);
static void boy_init(Boy *boy);
static void boy_class_init(BoyClass *boyclass);
void boy_dispose(GObject *gobject);
void boy_finalize(GObject *gobject);
GType boy_get_type(void)
{
    static GType boy_type = 0;
    if(!boy_type)
    {
        static const GTypeInfo boy_info = {
            sizeof(BoyClass),
            NULL,NULL,
            (GClassInitFunc)boy_class_init,
            NULL,NULL,
            sizeof(Boy),
            0,
            (GInstanceInitFunc)boy_init
        };
        boy_type = g_type_register_static(G_TYPE_OBJECT,"Boy",&boy_info,0);
    }
    return boy_type;
}
static void boy_init(Boy *boy)
{
    boy->age = 0;
    boy->name = "none";
    boy->cry = boy_cry;
}

static void boy_class_init(BoyClass *boyclass)
{
    boyclass->boy_born = boy_born;
    boy_signals[BOY_BORN] = g_signal_new("boy_born",
                BOY_TYPE,
                G_SIGNAL_RUN_FIRST,
                G_STRUCT_OFFSET(BoyClass,boy_born),
                NULL,NULL,
                g_cclosure_marshal_VOID__VOID,
                G_TYPE_NONE, 0, NULL);
    boy_parent_class=g_type_class_peek_parent (boyclass);
    GObjectClass *base_class = G_OBJECT_CLASS (boyclass);
    base_class->dispose      = boy_dispose;
    base_class->finalize     = boy_finalize;
}
Boy *boy_new(void)
{
    Boy *boy;
    boy = g_object_new(BOY_TYPE, NULL);
    g_signal_emit(boy,boy_signals[BOY_BORN],0);
    return boy;
}
void boy_free(Boy *boy){
    g_assert(boy!= NULL);
    g_return_if_fail(IS_BOY(boy));

    g_object_unref(G_OBJECT(boy));    
}
//http://garfileo.is-programmer.com/2011/3/21/gobject-signal.25477.html
void boy_dispose(GObject *gobject){
    G_OBJECT_CLASS (boy_parent_class)->dispose (gobject);
    g_print("boy dispose ......\n");
}
void boy_finalize(GObject *gobject){
    G_OBJECT_CLASS (boy_parent_class)->finalize(gobject);
    g_print("boy  finalize ......\n");
}
int boy_get_age(Boy *boy)
{
    return boy->age;
}
void boy_set_age(Boy *boy, int age)
{
    boy->age = age;
}
char *boy_get_name(Boy *boy)
{
    return boy->name;
}
void boy_set_name(Boy *boy, char *name)
{
    boy->name = name;
}
Boy*  boy_new_with_name(gchar *name)
{
    Boy* boy;
    boy = boy_new();
    boy_set_name(boy, name);
    return boy;
}
Boy*  boy_new_with_age(gint age)
{
    Boy* boy;
    boy = boy_new();
    boy_set_age(boy, age);
    return boy;
}
Boy *boy_new_with_name_and_age(gchar *name, gint age)
{
    Boy *boy;
    boy = boy_new();
    boy_set_name(boy,name);
    boy_set_age(boy,age);
    return boy;
}
static void boy_cry (void)
{
    g_print("The Boy is crying ......\n");
}
//http://garfileo.is-programmer.com/2011/3/25/gobject-signal-extra-1.25576.html
static void boy_born(void)
{
    g_print("Message : A boy was born .\n");
}
void  boy_info(Boy *boy)
{
    g_print("The Boy name is %s\n", boy->name);
    g_print("The Boy age is %d\n", boy->age);
}
void  release_signal(Boy *boy){
    g_signal_emit(boy,boy_signals[BOY_BORN],0);
}
