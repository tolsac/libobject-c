#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "new.h"

void			*va_new(Class* class, va_list *ap)
{
  void			*my_class;

  assert(ap);
  if ((my_class = malloc(class->__size__)) == NULL)
    raise("Out of memory\n");
  memcpy(my_class, class, class->__size__); 
  class->__init__(my_class, ap);
  return (my_class);
}

void			*new(Class* class, ...)
{
  void			*my_class;
  va_list		ap;

  srand(time(NULL));
  assert(class);
  va_start(ap, class);
  my_class = va_new(class, &ap);
  va_end(ap);
  return (my_class);
}

void			delete(Object* ptr)
{
  const Class		*cp = ptr;

  assert(ptr);
  if (ptr && cp && (cp)->__del__)
    ((Class*)ptr)->__del__(ptr);
  free(ptr);
}

bool			isObject(Object *it)
{
  assert(it);
  if (*((unsigned long*)it) == MAGIC)
    return true;
  return false;
}

bool			classOf(Object *it, Object *rhs)
{
  assert(it);
  assert(rhs);
  if (isObject(it) && isObject(rhs))
    {
      if ((strcmp(((Class*) it)->__name__, ((Class*) rhs)->__name__) == 0) &&
	  (((Class*) it)->__size__ == ((Class*) rhs)->__size__))
	return true;
      return false;
    }
  return false;
}

/*
bool equals(Class *a, Class *b)
{
  return a->__equals__(a, b);
}
*/
Object *clone(Class *ptr)
{
  return ptr->__clone__(ptr);
}
