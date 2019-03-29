#include "udisk.h"
#include "human.h"
//http://garfileo.is-programmer.com/2011/3/16/gobject-interface.25338.html
void test_desk(){
        MyUdisk *udisk = g_object_new (MY_TYPE_UDISK, NULL);
 
        my_iusb_write (MY_IUSB (udisk), "I am u-disk!");
        gchar *data = my_iusb_read (MY_IUSB (udisk));
 
        g_printf ("%s\n\n", data);
 
        g_printf ("Is udisk a MyIUsb object?\n");
        if (MY_IS_IUSB (udisk))
                g_printf ("Yes!\n");
        else
                g_printf ("No!\n");
 
        g_printf ("\nIs udisk a MyUdisk object?\n");
        if (MY_IS_UDISK (udisk))
                g_printf ("Yes!\n");
        else
                g_printf ("No!\n");
 
        disk_print_info();
}
void test_human(){
    MyHuman *human=my_human_new_with_name("Bob");
    my_ianimal_speak(MY_IANIMAL(human),"ha ha ha");
    my_iusb_write (MY_IUSB(human), "I am human!");
    gchar *data = my_iusb_read (MY_IUSB (human));
    g_printf ("read %s\n\n", data);    
    my_human_free(human);
}
int main (void)
{
    test_human();
    return 0;
}
