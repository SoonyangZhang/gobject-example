#ifndef ECHOCON_H_
#define ECHOCON_H_
#include "my_object.h"
#include "my_dispatcher.h"

typedef struct _EchoCon EchoCon;
struct _EchoCon{
	MyDispatcher *con_ref;
};
EchoCon *echo_con_new();
void echo_con_set_dispatcher(EchoCon*self,MyDispatcher *dis);
void echo_con_unref(EchoCon *self);



#endif /* ECHOCON_H_ */
