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
my=sys.argv[1]
human=sys.argv[2]
My=normallize(my)
Human=normallize(human)
MY=my.upper()
HUMAN=human.upper()

fileOut=human+".h"
fout=open(fileOut,'w')
string="#define %s_TYPE_%s (%s_%s_get_type ())"
stringout=string%(MY,HUMAN,my,human)
fout.write(stringout+"\n");

string="#define %s_%s(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), %s_TYPE_%s, %s%s))"
stringout=string%(MY,HUMAN,MY,HUMAN,My,Human)
fout.write(stringout+"\n");


string="#define %s_IS_%s(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), %s_TYPE_%s))"
stringout=string%(MY,HUMAN,MY,HUMAN)
fout.write(stringout+"\n");


string="#define %s_%s_CLASS(klass) \\"
stringout=string%(MY,HUMAN)
fout.write(stringout+"\n");

string_8_space="        "
string="(G_TYPE_CHECK_CLASS_CAST ((klass), %s_TYPE_%s, %s%sClass))"
stringout=string%(MY,HUMAN,My,Human)
fout.write(string_8_space+stringout+"\n");

string="#define %s_IS_%s_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), %s_TYPE_%s))"
stringout=string%(MY,HUMAN,MY,HUMAN)
fout.write(stringout+"\n");


string="#define %s_%s_GET_CLASS(obj) \\"
stringout=string%(MY,HUMAN)
fout.write(stringout+"\n");

string="(G_TYPE_INSTANCE_GET_CLASS ((obj),%s_TYPE_%s,%s%sClass))"
stringout=string%(MY,HUMAN,My,Human)
fout.write(string_8_space+stringout+"\n");

fout.write("\n");


string="typedef struct _%s%s %s%s;"
stringout=string%(My,Human,My,Human)
fout.write(stringout+"\n");
string="typedef struct _%s%sClass %s%sClass;"
stringout=string%(My,Human,My,Human)
fout.write(stringout+"\n");
fout.write("\n");

string_4_space="    "
string="struct _%s%s{"
stringout=string%(My,Human)
fout.write(stringout+"\n");
fout.write(string_4_space+"GObject parent;"+"\n")
fout.write("};\n");


string="struct _%s%sClass{"
stringout=string%(My,Human)
fout.write(stringout+"\n");
fout.write(string_4_space+"GObjectClass parent_class;"+"\n")
fout.write("};\n");

fout.write("\n");
fout.write("\n");

string="GType %s_%s_get_type (void);"
stringout=string%(my,human)
fout.write(stringout+"\n");

string="%s%s *%s_%s_new(void);"
stringout=string%(My,Human,my,human)
fout.write(stringout+"\n");

string="void %s_%s_free(%s%s *self);"
stringout=string%(my,human,My,Human)
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
fileOut=human+".c"
fout=open(fileOut,'w')

string="#include '"'%s.h'"'"
stringout=string%(human)
fout.write(stringout+"\n");
string="void %s_%s_dispose(GObject *gobject){"
stringout=string%(my,human)
fout.write(stringout+"\n");

string="G_OBJECT_CLASS (%s_%s_parent_class)->dispose(gobject);"
stringout=string%(my,human)
fout.write(string_4_space+stringout+"\n");
fout.write("}\n")

string="void %s_%s_finalize(GObject *gobject){"
stringout=string%(my,human)
fout.write(stringout+"\n");

string="G_OBJECT_CLASS (%s_%s_parent_class)->finalize(gobject);"
stringout=string%(my,human)
fout.write(string_4_space+stringout+"\n");
fout.write("}\n")

string="static void %s_%s_init(%s%s *self){"
stringout=string%(my,human,My,Human)
fout.write(stringout+"\n");
fout.write("\n");
fout.write("}\n");

string="static void %s_%s_class_init(%s%sClass *kclass){"
stringout=string%(my,human,My,Human)
fout.write(stringout+"\n");
string="GObjectClass *base_class = G_OBJECT_CLASS (kclass);"
fout.write(string_4_space+string+"\n");
string="base_class->dispose      = %s_%s_dispose;"
stringout=string%(my,human)
fout.write(string_4_space+stringout+"\n");
string="base_class->finalize      = %s_%s_finalize;"
stringout=string%(my,human)
fout.write(string_4_space+stringout+"\n");
fout.write("}\n");

string="%s%s *%s_%s_new(void){"
stringout=string%(My,Human,my,human);
fout.write(stringout+"\n");
string="    %s%s *ins;\n    ins = g_object_new(%s_TYPE_%s, 0);\n    return ins;"
stringout=string%(My,Human,MY,HUMAN);
fout.write(stringout+"\n");
fout.write("}\n");

string="void %s_%s_free(%s%s *self){"
stringout=string%(my,human,My,Human);
fout.write(stringout+"\n");
string="    g_assert(self!= NULL);\n    g_return_if_fail(%s_IS_%s(self));\n    g_object_unref(G_OBJECT(self));"
stringout=string%(MY,HUMAN);
fout.write(stringout+"\n");
fout.write("}\n");
fout.close()
