/* man.c */
#include "man.h"
static void man_bye(void);
static void man_init(Man *man);
static void man_class_init(ManClass *man);
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
    printf("man class init\n");
}
Man*  man_new(void)
{
    Man *man;
    man = g_object_new(MAN_TYPE, 0);
    return man;
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
