/*
** Int.h for Int in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Mon Jun 24 15:12:25 2013 root
** Last update Wed Aug  7 11:33:09 2013 root
*/

#ifndef INT_H_
# define INT_H_

#include <stdio.h>
#include "object.h"
#include "String.h"

typedef struct s_int
{
  Class		base;
  String	*(*toString)(struct s_int *);
  char		*(*toStr)(struct s_int *);
  void		(*valueOf)(struct s_int *, Object *);
  String	*(*toHexadecimal)(struct s_int *);
  String	*(*toOctal)(struct s_int *);
  int		_value;
}Int;

extern Class * IntType;

#endif /* !INT_H_ */
