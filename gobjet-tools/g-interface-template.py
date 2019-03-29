'''
usage: python g-interface-micro-generator.py my runnable

#include <glib-object.h>
#define MY_TYPE_IANIMAL (my_ianimal_get_type ())
#define MY_IANIMAL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj),MY_TYPE_IANIMAL, MyIAnimal))
#define MY_IS_IANIMAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MY_TYPE_IANIMAL))
#define MY_IANIMAL_GET_INTERFACE(obj) (\
                G_TYPE_INSTANCE_GET_INTERFACE ((obj), MY_TYPE_IANIMAL, MyIAnimalInterface))

typedef struct _MyIAnimal MyIAnimal; //dummy object
typedef struct _MyIAnimalInterface MyIAnimalInterface;


struct _MyIAnimalInterface {
    GTypeInterface parent_interface;
};
GType my_ianimal_get_type (void);
'''
import sys
#  animal -> Animal
def normallize(name):
    return name.capitalize()
prefix=sys.argv[1]
oname=sys.argv[2]
fileOut="i"+oname+".h"
fout=open(fileOut,'w')
Prefix=normallize(prefix)
PREFIX=prefix.upper()
Oname=normallize(oname)
ONAME=oname.upper()
string="#include <glib-object.h>"
fout.write(string+"\n");


string="#define %s_TYPE_I%s (%s_i%s_get_type ())"
stringout=string%(PREFIX,ONAME,prefix,oname)
fout.write(stringout+"\n");
string="#define %s_I%s(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj)%s_TYPE_I%s, %sI%s))"
stringout=string%(PREFIX,ONAME,PREFIX,ONAME,Prefix,Oname)
fout.write(stringout+"\n");
string="#define %s_IS_I%s(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), %s_TYPE_I%s))"
stringout=string%(PREFIX,ONAME,PREFIX,ONAME)
fout.write(stringout+"\n");

string="#define %s_I%s_GET_INTERFACE(obj) (\\"
stringout=string%(PREFIX,ONAME)
fout.write(stringout+"\n");


string="G_TYPE_INSTANCE_GET_INTERFACE ((obj), %s_TYPE_I%s, %sI%sInterface))"
stringout=string%(PREFIX,ONAME,Prefix,Oname)
fout.write("          "+stringout+"\n");
fout.write("\n");
fout.write("\n");
fout.write("\n");

string="typedef struct _%sI%s %sI%s; //dummy object"
stringout=string%(Prefix,Oname,Prefix,Oname)
fout.write(stringout+"\n");

string="typedef struct _%sI%sInterface %sI%sInterface;"
stringout=string%(Prefix,Oname,Prefix,Oname)
fout.write(stringout+"\n");

string="struct _%sI%sInterface {"
stringout=string%(Prefix,Oname)
fout.write(stringout+"\n");


string="GTypeInterface parent_interface;"
fout.write("    "+string+"\n");

string="};"
fout.write(string+"\n");


string="GType %s_i%s_get_type (void);"
stringout=string%(prefix,oname)
fout.write(stringout+"\n")
fout.close()

'''
xxx.c

#include "ianimal.h"
G_DEFINE_INTERFACE (MyIAnimal, my_ianimal, G_TYPE_INVALID);

static void
my_ianimal_default_init (MyIAnimalInterface *iface)
{
}
'''
fileOut="i"+oname+".c"
fout=open(fileOut,'w')

string="#include \"i%s.h\""
stringout=string%(oname)
fout.write(stringout+"\n");

string="G_DEFINE_INTERFACE (%sI%s, %s_i%s, G_TYPE_INVALID);"
stringout=string%(Prefix,Oname,prefix,oname)
fout.write(stringout+"\n");
fout.write("\n");


string="static void"
fout.write(string+"\n");


string="%s_i%s_default_init (%sI%sInterface *iface) {"
stringout=string%(prefix,oname,Prefix,Oname)
fout.write(stringout+"\n");

string="}"
fout.write(string+"\n");

'''
g_return_if_fail (MY_IS_IANIMAL(self));
'''

fout.write("\n");
string="g_return_if_fail (%s_IS_I%s(self));"
stringout=string%(PREFIX,ONAME)
fout.write(stringout+"\n");

fout.close();


