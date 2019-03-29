//https://www.ibm.com/developerworks/cn/linux/l-gobject/index.html
#include <glib.h>
#include "boy.h"
#include "man.h"
int main(int argc, char *argv[])
{
    Boy *tom, *peter;
    Man *green, *brown; 
    g_type_init();// not quite necessary 
    tom = boy_new_with_name("Tom");
    tom->cry();
    boy_info(tom);
    peter = boy_new_with_name_and_age("Peter", 10);
    peter->cry();
    boy_info(peter);
    green = man_new();
    boy_set_name(BOY(green), "Green");

    boy_set_age(BOY(green), 28);
    man_set_job(green, "Doctor");
    green->bye();
    man_info(green);
    brown = man_new_with_name_age_and_job("Brown", 30, "Teacher");
    brown->bye();
    man_info(brown);
    //release_signal(BOY(brown));
    g_signal_emit_by_name(brown, "boy_born");
    boy_free(tom);
    man_free(brown);
}
