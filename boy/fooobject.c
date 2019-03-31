/*

* fooobject.c

* Copyright (C) 2006 gclassfactory

*

* This library is free software; you can redistribute it and/or

* modify it under the terms of the GNU Lesser General Public

* License as published by the Free Software Foundation; either

* version 2 of the License, or (at your option) any later version.

*

* This library is distributed in the hope that it will be useful,

* but WITHOUT ANY WARRANTY; without even the implied warranty of

* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU

* Lesser General Public License for more details.

*

* You should have received a copy of the GNU Lesser General Public

* License along with this library; if not, write to the

* Free Software Foundation, Inc., 59 Temple Place - Suite 330,

* Boston, MA 02111-1307, USA.

*/

#include "fooobject.h"


enum {

PROP_0,

PROP_VISIBLE,

PROP_WIDTH,

PROP_HEIGHT,

PROP_LAST

};


static GObjectClass* parent_class = NULL;


static void foo_object_class_init(FooObjectClass *class);

static void foo_object_init (FooObject *object);

static void foo_object_set_property (GObject *object,

guint property_id,

const GValue *value,

GParamSpec *pspec);

static void foo_object_get_property (GObject *object,

guint property_id,

GValue *value,

GParamSpec *pspec);

GType

foo_object_get_type (void)

{

static GType object_type = 0;


if (!object_type)

{

static const GTypeInfo object_info =

{

sizeof (FooObjectClass),

NULL, /* base_init */

NULL, /* base_finalize */

(GClassInitFunc) foo_object_class_init,

NULL, /* class_finalize */

NULL, /* class_data */

sizeof (FooObject),

0, /* n_preallocs */

(GInstanceInitFunc) foo_object_init,

};

object_type = g_type_register_static (G_TYPE_OBJECT, "FooObject", &object_info, 0);

};


return object_type;

}


FooObject* foo_object_new(void)

{

return (FooObject*)g_object_new(FOO_TYPE_OBJECT, 0);

}


static void foo_object_class_init(FooObjectClass *class)

{

GObjectClass* gobject_class = G_OBJECT_CLASS(class);


gobject_class->set_property = foo_object_set_property;

gobject_class->get_property = foo_object_get_property;


g_object_class_install_property (gobject_class,

PROP_VISIBLE,

g_param_spec_boolean ("visible",

("Visible"),

("Whether the widget is visible"),

FALSE,

G_PARAM_READWRITE));


g_object_class_install_property (gobject_class,

PROP_HEIGHT,

g_param_spec_int ("height",

("Height"),

("Override for height request of the widget, or -1 if natural request should be used"),

-1,

G_MAXINT,

-1,

G_PARAM_READWRITE));

g_object_class_install_property (gobject_class,

PROP_WIDTH,

g_param_spec_int ("width",

("Width request"),

("Override for width request of the widget, or -1 if natural request should be used"),

-1,

G_MAXINT,

-1,

G_PARAM_READWRITE));


return;

}


static void foo_object_init (FooObject *object)

{

return;

}


static void foo_object_set_property (GObject *object,

guint property_id,

const GValue *value,

GParamSpec *pspec)

{

FooObject* foo_object = FOO_OBJECT(object);


switch(property_id)

{

case PROP_VISIBLE:

{

foo_object->visible = g_value_get_boolean(value);

break;

}

case PROP_WIDTH:

{

foo_object->width = g_value_get_int(value);

break;

}

case PROP_HEIGHT:

{

foo_object->height = g_value_get_int(value);

break;

}

default:

{

G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);

break;

}

}


return;

}

static void foo_object_get_property (GObject *object,

guint property_id,

GValue *value,

GParamSpec *pspec)

{

FooObject* foo_object = FOO_OBJECT(object);


switch(property_id)

{

case PROP_VISIBLE:

{

g_value_set_boolean(value, foo_object->visible);

break;

}

case PROP_WIDTH:

{

g_value_set_int(value, foo_object->width);

break;

}

case PROP_HEIGHT:

{

g_value_set_int(value, foo_object->height);

break;

}

default:

{

G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);

break;

}

}


return;

}


static void property_change (gpointer data1,

gpointer arg_1,

gpointer data2)

{

GParamSpec *pspec = (GParamSpec*) arg_1;


g_printf("property %s change/n", g_param_spec_get_name(pspec));

return;

}


int main(int argc, char* argv[])

{

GValue value = {0};


FooObject* object = NULL;


g_type_init();


object = foo_object_new();


g_signal_connect(G_OBJECT(object), "notify", G_CALLBACK(property_change), object);

g_value_init(&value, G_TYPE_BOOLEAN);

g_value_set_boolean(&value, TRUE);

g_object_set_property(G_OBJECT(object), "visible", &value);


g_value_unset(&value);


g_value_init(&value, G_TYPE_INT);


g_value_set_int(&value, 400);

g_object_set_property(G_OBJECT(object), "width", &value);


g_value_set_int(&value, 300);

g_object_set_property(G_OBJECT(object), "height", &value);


g_object_unref(object);


return 0;

}
