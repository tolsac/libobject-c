/*
** new.h for  in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@epitech.net>
** 
** Started on  Mon Jun 24 16:45:22 2013 root
** Last update Thu Aug  1 09:02:37 2013 root
*/

#ifndef NEW_H
# define NEW_H

#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "object.h"

Object*		 new(Class * class, ...);
Object*		 va_new(Class* class, va_list* ap);
void		 delete(Object * ptr);
//bool		 equals(Class *, Class *);
Object		 *_clone(Class *);

#endif
