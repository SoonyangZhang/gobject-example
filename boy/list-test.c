#include "my_list.h"

int main(){
    MyList *list=my_list_new();
    MyListClass *kclass=MY_LIST_GET_CLASS(list);
    double a=123.45;
    kclass->push_back(list,(void*)&a,sizeof(double),1);
    a=123.46;
    kclass->push_front(list,(void*)&a,sizeof(double),1);    
    g_print("%d\n",my_list_size(list));
    a=123.47;
    kclass->push_front(list,(void*)&a,sizeof(double),1);    
    g_print("%d\n",my_list_size(list));
    double b=0;
    kclass->pop_front(list,(void*)&b,sizeof(double));
    g_print("%f,%d\n",b,my_list_size(list));
    my_list_free(list);
    return 0;
}
