/* man.c */
#include "man.h"
static gpointer man_parent_class = NULL;
static void man_bye(void);
static void man_init(Man *man);
static void man_class_init(ManClass *man);
void man_dispose(GObject *gobject);
void man_finalize(GObject *gobject);
GType man_get_type(void)
{
    static GType man_type = 0;
    if(!man_type)
    {
        static const GTypeInfo man_info = {
            sizeof(ManClass),
            NULL, NULL,
            (GClassInitFunc)man_class_init,
            NULL, NULL,
            sizeof(Man),
            0,
            (GInstanceInitFunc)man_init
        };
        man_type = g_type_register_static(BOY_TYPE, "Man", &man_info, 0);
    }
    return man_type;
}
static void man_init(Man *man)
{
    man->job = "none";
    man->bye = man_bye;
}
static void man_cry (void)
{
    g_print("The Man is crying ......\n");
}
static void man_born(){
    g_print("mothod override : A man is create .\n");
}
static void man_class_init(ManClass *kclass)
{
// my test for override
    BoyClass *boyclass=BOY_CLASS(kclass);
    boyclass->boy_born=man_born;
    man_parent_class=g_type_class_peek_parent (kclass);
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = man_dispose;
    base_class->finalize     = man_finalize;
}
void from_parent(Boy *boy){
    g_print("signal triggered\n");
}
Man*  man_new(void)
{
    Man *man;
    man = g_object_new(MAN_TYPE, 0);
    g_signal_connect(
        man,
        "boy_born",
        (GCallback)from_parent,
        NULL);
    return man;
}
void man_free(Man *man){
    g_assert(man!= NULL);
    g_return_if_fail(IS_MAN(man));
    g_object_unref(G_OBJECT(man)); 
}
void man_dispose(GObject *gobject){
    G_OBJECT_CLASS (man_parent_class)->dispose (gobject);
    g_print("man dispose ......\n");
}
void man_finalize(GObject *gobject){
    G_OBJECT_CLASS (man_parent_class)->finalize(gobject);
    g_print("man  finalize ......\n");
}
gchar* man_get_gob(Man *man)
{
    return man->job;
}
void  man_set_job(Man *man, gchar *job)
{
    man->job = job;
}
Man*  man_new_with_name_age_and_job(gchar *name, gint age, gchar *job)
{
    Man *man;
    man = man_new();
    boy_set_name(BOY(man), name);
    boy_set_age(BOY(man), age);
    man_set_job(man, job);
    return man;
}
static void man_bye(void)
{
    g_print("Goodbye everyone !\n");
}
void man_info(Man *man)
{
    g_print("the man name is %s\n", BOY(man)->name);
    g_print("the man age is %d\n", BOY(man)->age);
    g_print("the man job is %s\n", man->job);
}
