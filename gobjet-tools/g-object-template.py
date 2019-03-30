'''
#define MY_TYPE_HUMAN (my_human_get_type ())
#define MY_HUMAN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MY_TYPE_HUMAN, MyHuman))
#define MY_IS_HUMAN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_TYPE_HUMAN))
#define MY_HUAMN_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST ((klass), MY_TYPE_HUMAN, MyHumanClass))
#define MY_IS_HUAMN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MY_TYPE_HUMAN))
#define MY_HUAMN_GET_CLASS(obj) \
        (G_TYPE_INSTANCE_GET_CLASS ((obj),MY_TYPE_HUMAN,MyHumanClass))

typedef struct _MyHuman MyHuman;
typedef struct _MyHumanClass MyHumanClass;

struct _MyHuman{
    GObject parent;
    //add you own data
};
struct _MyHumanClass{
    GObjectClass parent_class;
};
GType my_human_get_type (void);
MyHuman *my_human_new(void);
void my_print_free(MyPrint *self);
'''
import sys
def normallize(name):
    return name.capitalize()

NAMESPACE=""
OBJECTNAME=""
object_type="%s_%s_TYPE"   #"MY_PRINT_TYPE"
struct_cast="%s_%s" #"MY_PRINT(obj)"
is_object="%s_IS_%s" #"MY_IS_PRINT(obj)"
class_cast="%s_%s_CLASS"#"MY_PRINT_CLASS(klass)"
is_class="%s_IS_%s_CLASS" #"MY_IS_PRINT_CLASS(klass)"

get_class="%s_%s_GET_CLASS" #"MY_PRINT_GET_CLASS(obj)"
struct_name="%s%s" #"MyPrint"
class_name="%s%sClass" #"MyPrintClass"
fucntion_name_p="%s_%s" #"my_print"
argc=len(sys.argv);
if argc==3:
    namespace=sys.argv[1]
    arg1=sys.argv[2]
    Namespace=normallize(namespace)
    NAMESPACE=namespace.upper()
    Arg1=normallize(arg1)
    ARG1=arg1.upper()
    OBJECTNAME=ARG1
    object_type=object_type%(NAMESPACE,ARG1)
    struct_cast=struct_cast%(NAMESPACE,ARG1)
    is_object=is_object%(NAMESPACE,ARG1)
    class_cast=class_cast%(NAMESPACE,ARG1)
    is_class=is_class%(NAMESPACE,ARG1)
    get_class=get_class%(NAMESPACE,ARG1)
    struct_name=struct_name%(Namespace,Arg1)
    class_name=struct_name+"Class"
    fucntion_name_p=fucntion_name_p%(namespace,arg1)
elif argc==4:
    namespace=sys.argv[1]
    arg1=sys.argv[2]#print
    arg2=sys.argv[3]#buffer
    Namespace=normallize(namespace)
    NAMESPACE=namespace.upper()
    print_buffer=arg1+"_"+arg2
    Print_Buffer=normallize(arg1)+"_"+normallize(arg2)
    PRINT_BUFFER=arg1.upper()+"_"+arg2.upper()
    PRINTBUFFER=arg1.upper()+arg2.upper()
    PrintBuffer=normallize(arg1)+normallize(arg2)
    OBJECTNAME=PRINTBUFFER
    arg1=print_buffer
    Arg1=Print_Buffer
    ARG1=PRINT_BUFFER

    object_type=object_type%(NAMESPACE,ARG1)
    struct_cast=struct_cast%(NAMESPACE,PRINTBUFFER)
    is_object=is_object%(NAMESPACE,PRINTBUFFER)
    class_cast=class_cast%(NAMESPACE,PRINTBUFFER)
    is_class=is_class%(NAMESPACE,PRINTBUFFER)
    get_class=get_class%(NAMESPACE,PRINTBUFFER)
    struct_name=struct_name%(Namespace,PrintBuffer)
    class_name=struct_name+"Class"
    fucntion_name_p=fucntion_name_p%(namespace,arg1)    



fileOut=fucntion_name_p+".h"
fout=open(fileOut,'w')
string="#define %s (%s_get_type ())"
stringout=string%(object_type,fucntion_name_p)
fout.write(stringout+"\n");

string="#define %s(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), %s, %s))"
stringout=string%(struct_cast,object_type,struct_name)
fout.write(stringout+"\n");


string="#define %s(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), %s))"
stringout=string%(is_object,object_type)
fout.write(stringout+"\n");


string="#define %s(klass) \\"
stringout=string%(class_cast)
fout.write(stringout+"\n");
string_8_space="        "
string="(G_TYPE_CHECK_CLASS_CAST ((klass), %s, %s))"
stringout=string%(object_type,class_name)
fout.write(string_8_space+stringout+"\n");

string="#define %s(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), %s))"
stringout=string%(is_class,object_type)
fout.write(stringout+"\n");


string="#define %s(obj) \\"
stringout=string%(get_class)
fout.write(stringout+"\n");

string="(G_TYPE_INSTANCE_GET_CLASS ((obj),%s,%s))"
stringout=string%(object_type,class_name)
fout.write(string_8_space+stringout+"\n");
fout.write("\n");


string="typedef struct _%s %s;"
stringout=string%(struct_name,struct_name)
fout.write(stringout+"\n");
string="typedef struct _%s %s;"
stringout=string%(class_name,class_name)
fout.write(stringout+"\n");
fout.write("\n");

string_4_space="    "
string="struct _%s{"
stringout=string%(struct_name)
fout.write(stringout+"\n");
fout.write(string_4_space+"GObject parent;"+"\n")
fout.write("};\n");


string="struct _%s{"
stringout=string%(class_name)
fout.write(stringout+"\n");
fout.write(string_4_space+"GObjectClass parent_class;"+"\n")
fout.write("};\n");

fout.write("\n");
fout.write("\n");

string="GType %s_get_type (void);"
stringout=string%(fucntion_name_p)
fout.write(stringout+"\n");

string="%s *%s_new(void);"
stringout=string%(struct_name,fucntion_name_p)
fout.write(stringout+"\n");

string="void %s_free(%s *self);"
stringout=string%(fucntion_name_p,struct_name)
fout.write(stringout+"\n");
fout.close();

'''
#include "human.h"
void my_human_dispose(GObject *gobject){
	G_OBJECT_CLASS (my_human_parent_class)->dispose(gobject);
}
void my_human_finalize(GObject *gobject){
	G_OBJECT_CLASS (my_human_parent_class)->finalize(gobject);
}

static void my_human_init(MyHuman *self){

}
static void my_print_class_init(MyPrintClass *kclass){
    GObjectClass *base_class = G_OBJECT_CLASS (kclass);
    base_class->dispose      = my_human_dispose;
    base_class->finalize     = my_human_finalize;
}
MyPrint *my_human_new(void){
	MyHuman *ins;
    ins = g_object_new(MY_TYPE_HUMAN, 0);
    return ins;
}
void my_human_free(MyPrint *self){
    g_assert(self!= NULL);
    g_return_if_fail(MY_IS_HUMAN(self));
    g_object_unref(G_OBJECT(self));
}
'''
fileOut=fucntion_name_p+".c"
fout=open(fileOut,'w')
string="#include \"lazy_micro.h\""
fout.write(string+"\n");
fout.write("\n");

lazy_is_object="lazy_is_obj(%s,%s,self)"%(NAMESPACE,OBJECTNAME)
lazy_is_class="lazy_is_class(%s,%s,kclass)"%(NAMESPACE,OBJECTNAME)



string="void %s_dispose(GObject *gobject){"
stringout=string%(fucntion_name_p)
fout.write(stringout+"\n");

string="G_OBJECT_CLASS (%s_parent_class)->dispose(gobject);"
stringout=string%(fucntion_name_p)
fout.write(string_4_space+stringout+"\n");
fout.write("}\n")

string="void %s_finalize(GObject *gobject){"
stringout=string%(fucntion_name_p)
fout.write(stringout+"\n");

string="G_OBJECT_CLASS (%s_parent_class)->finalize(gobject);"
stringout=string%(fucntion_name_p)
fout.write(string_4_space+stringout+"\n");
fout.write("}\n")

string="static void %s_init(%s *self){"
stringout=string%(fucntion_name_p,struct_name)
fout.write(stringout+"\n");
fout.write("\n");
fout.write("}\n");

string="static void %s_class_init(%s *kclass){"
stringout=string%(fucntion_name_p,class_name)
fout.write(stringout+"\n");
string="GObjectClass *base_class = G_OBJECT_CLASS (kclass);"
fout.write(string_4_space+string+"\n");
string="base_class->dispose      = %s_dispose;"
stringout=string%(fucntion_name_p)
fout.write(string_4_space+stringout+"\n");
string="base_class->finalize      = %s_finalize;"
stringout=string%(fucntion_name_p)
fout.write(string_4_space+stringout+"\n");
fout.write("}\n");

string="%s *%s_new(void){"
stringout=string%(struct_name,fucntion_name_p);
fout.write(stringout+"\n");
string="    %s *ins;\n    ins = g_object_new(%s, 0);\n    return ins;"
stringout=string%(struct_name,object_type);
fout.write(stringout+"\n");
fout.write("}\n");

string="void %s_free(%s *self){"
stringout=string%(fucntion_name_p,struct_name);
fout.write(stringout+"\n");
string="    g_assert(self!= NULL);\n    g_return_if_fail(%s);\n    g_object_unref(G_OBJECT(self));"
stringout=string%(lazy_is_object);
fout.write(stringout+"\n");
fout.write("}\n");
fout.close()
