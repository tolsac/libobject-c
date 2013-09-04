#ifndef CLASS_H
# define CLASS_H

#define MAGIC 0x0effaced

# include <sys/types.h>
# include <stdarg.h>
# include "bool.h"

typedef void		*(*function)(void);
typedef void		*(*callable)(void*);

typedef void		Object;
typedef void		(*ctor_t)(Object * self, va_list * args);
typedef void		(*dtor_t)(Object * self);
typedef char const*	(*to_string_t)(Object* self);
typedef Object		*(*clone_t)(Object * self);
typedef bool		(*equals_t)(Object * self, Object * other);
typedef int		(*len_t)(Object * self);

typedef struct {
  unsigned long	      __magic__;
  const size_t        __size__;
  const char*         __name__;
  unsigned int	      __hash__;
  ctor_t              __init__;
  dtor_t              __del__;
  to_string_t         __str__;
  clone_t	      __clone__;
  equals_t	      __equals__;
  len_t		      __len__;
} Class;

# define str(o) ((o == NULL) ? "" : (((Class*) o)->__str__ != NULL ? ((Class*) o)->__str__(o) : ""))
# define len(o) ((o == NULL) ? 0 : (((Class*) o)->__len__ != NULL ? ((Class*) o)->__len__(o) : 0))
# define name(o) ((o == NULL) ? "" : (((Class*) o)->__name__ != NULL ? ((Class*) o)->__name__ : ""))
# define equals(o, r) ((o == NULL || r == NULL) ? false : (((Class*) o)->__equals__ != NULL ? ((Class*) o)->__equals__(o, r) : false))
# define hash(o) ((o == NULL) ? 0 : ((((Class*) o)->__hash__ == 0) ? (((Class*) o)->__hash__ = rand()) : (((Class*) o)->__hash__)))

#endif
