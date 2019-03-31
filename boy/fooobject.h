/*

* fooobject.h

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

#ifndef FOO_OBJECT_H

#define FOO_OBJECT_H


#include <glib.h>

#include <glib-object.h>


G_BEGIN_DECLS


#define FOO_TYPE_OBJECT (foo_object_get_type ())

#define FOO_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FOO_TYPE_OBJECT, FooObject))

#define FOO_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), FOO_TYPE_OBJECT, FooObjectClass))

#define FOO_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FOO_TYPE_OBJECT))

#define FOO_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), FOO_TYPE_OBJECT))

#define FOO_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), FOO_TYPE_OBJECT, FooObjectClass))


typedef struct _FooObject FooObject;

typedef struct _FooObjectClass FooObjectClass;


struct _FooObject

{

GObject gobject;


gint width;

gint height;

gboolean visible;


};


struct _FooObjectClass

{

GObjectClass parent_class;




};


GType foo_object_get_type(void) G_GNUC_CONST;

FooObject* foo_object_new(void);


G_END_DECLS


#endif /*FOO_OBJECT_H*/