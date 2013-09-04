/*
** string.h for  in /home/tolsa_c//piscine2/ex00
** 
** Made by camille tolsa
** Login   <tolsa_c@epitech.net>
** 
** Started on  Fri Jan  6 09:05:03 2012 camille tolsa
** Last update Thu Aug  1 11:21:24 2013 root
*/
#ifndef __STRING_H__
#define __STRING_H__

#include "object.h"

typedef struct s_string
{
  Class         base;
  char          (*at)(struct s_string * this, size_t);
  void          (*append)(struct s_string * this, Object *);
  void          (*assign)(struct s_string * this, Object *);
  void          (*clear)(struct s_string * this);
  int           (*size)(struct s_string * this);
  int           (*compare)(struct s_string * this, Object *);
  size_t        (*copy)(struct s_string * this, char* s, size_t n, size_t pos);
  char const*   (*c_str)(struct s_string * this);
  int           (*empty)(struct s_string * this);
  int           (*find)(struct s_string * this, Object *, size_t pos);
  void          (*insert)(struct s_string * this, size_t pos, Object *);
  int           (*toInt)(struct s_string * this);
  struct s_string*(*split)(struct s_string * this, char separator);
  char**        (*splitToChar)(struct s_string * this, char separator);
  char          *str;
}String;

extern Class * StringType;

#endif
