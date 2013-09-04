/*
** string.c for  in /home/tolsa_c//piscine2/ex00
** 
** Made by camille tolsa
** Login   <tolsa_c@epitech.net>
** 
** Started on  Fri Jan  6 09:06:48 2012 camille tolsa
** Last update Thu Aug 29 08:06:12 2013 root
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "new.h"
#include "String.h"
#include "ByteArray.h"

bool		__equalsString__(Object * this, Object * other)
{
  if (strcmp(((String*)this)->str, ((String*)other)->str) == 0)
    return true;
  return false;
}

Object		*__cloneString__(Object * this)
{
  String	*clone = new(StringType);
  
  clone->assign(clone, ((String*)this)->str);
  return clone;
}

String * split_sString(String * this, char separator)
{
  String        **my_tab;
  int           i;
  int           j;
  int           w;

  if ((this) == NULL)
    return (NULL);
  if ((this)->str == NULL)
    return (NULL);
  w = 0;
  i = 0;
  my_tab = (String**)malloc((strlen((this)->str)) * 3);
  ((String**)my_tab)[0]->str = malloc((strlen((this)->str)) + 1);
  while ((this)->str[i])
    {
      ((String**)my_tab)[w]->str = malloc((strlen((this)->str)) + 1);
      j = 0;
      while ((this)->str[i] != ' ' && (this)->str[i] != '\0')
        ((String**)my_tab)[w]->str[j++] = (this)->str[i++];
      ((String**)my_tab)[w++]->str[j] = '\0';
      i++;
    }
  ((String**)my_tab)[w] = NULL;
  return (*((String**)my_tab));
}

char** split_cString(String * this, char separator)
{
  char          **my_tab;
  int           i;
  int           j;
  int           w;
  
  if ((this) == NULL)
    return (NULL);
  if ((this)->str == NULL)
    return (NULL);
  w = 0;
  i = 0;
  my_tab = malloc((strlen((this)->str)) * 3);
  my_tab[0] = malloc((strlen((this)->str)) + 1);
  while ((this)->str[i])
    {
      my_tab[w] = malloc((strlen((this)->str)) + 1);
      j = 0;
      while ((this)->str[i] != separator && (this)->str[i] != '\0')
        my_tab[w][j++] = (this)->str[i++];
      my_tab[w++][j] = '\0';
      i++;
    }
  my_tab[w] = NULL;
  return (my_tab);
}

int to_intString(String * this)
{
  if ((this) != NULL)
    if ((this)->str != NULL)
      return (atoi((this)->str));
  return (0);
}

void		_insertObjString(String * this, size_t pos, Object * ap)
{
  assert(this);
  assert(ap);
  if (isObject(ap))
    {
      if (classOf(ap, StringType))
	return insert_sString(this, pos, (String*)ap);
      else if (classOf(ap, ByteArrayType))
	return insert_cString(this, pos, ((ByteArray*)ap)->_array);
    }
  else
    return insert_cString(this, pos, (char*)ap);  
}

void insert_sString(String * this, size_t pos, const String * str)
{
  int		i=0;
  char		*tmp;
  int		save_pos;

  if ((this) != NULL)
    if ((this)->str != NULL)
      if (str != NULL)
	if ((str)->str != NULL)
	  {
	    (this)->str = realloc((this)->str, strlen((str)->str) + 1);
	    if (pos > strlen((this)->str))
	      (this)->str = strcat((this)->str, (str)->str);
	    else
	      {
		save_pos = pos;
		tmp = malloc(strlen((this)->str));
		while ((this)->str[save_pos])
		  tmp[i++] = (this)->str[save_pos++];
		save_pos = pos;
		i = 0;
		while ((str)->str[i])
		  (this)->str[save_pos++] = (str)->str[i++]; 
		i = 0;
		pos += strlen((str)->str);
		while (tmp[i])
		  (this)->str[pos++] = tmp[i++];
	      }
	  }
}

void insert_cString(String * this, size_t pos, char const* str)
{
  int		i=0;
  char		*tmp;
  int		save_pos;

  if ((this) != NULL)
    if ((this)->str != NULL)
      if (str != NULL)
	{
	  (this)->str = realloc((this)->str, strlen(str) + 1);
	  if (pos > strlen((this)->str))
	    (this)->str = strcat((this)->str, str);
	  else
	    {
	      save_pos = pos;
	      tmp = malloc(strlen((this)->str));
	      while ((this)->str[save_pos])
		tmp[i++] = (this)->str[save_pos++];
	      save_pos = pos;
	      i = 0;
	      while (str[i])
		(this)->str[save_pos++] = str[i++]; 
	      i = 0;
	      pos += strlen(str);
	      while (tmp[i])
		(this)->str[pos++] = tmp[i++];
	    }
	}
}

int		_findObjString(String * this, Object * ap, size_t pos)
{
  assert(this);
  assert(ap);
  if (isObject(ap))
    {
      if (classOf(ap, StringType))
	return find_sString(this, (String*)ap, pos);
      else if (classOf(ap, ByteArrayType))
	return find_cString(this, ((ByteArray*)ap)->_array, pos);
    }
  else
    return find_cString(this, (char*)ap, pos);  
}

int find_sString(String * this, const String * str, size_t pos)
{
  int   j,lenght;
  
  j = 0;
  lenght = 0;
  if (pos > strlen((this)->str))
      return (-1);
  while ((str)->str[lenght])
    lenght = lenght + 1;
  while ((this)->str[pos])
    {
      while ((this)->str[pos + j] == (str)->str[j])
	j = j + 1;
      if (j == lenght)
	return (pos);
      else
        j = 0;
      pos++;
    } 
  return (-1);
}

int find_cString(String * this, char  const *str, size_t pos)
{
 int   j,lenght;
  
  j = 0;
  lenght = 0;
  if (pos > strlen(str))
      return (-1);
  while (str[lenght])
    lenght = lenght + 1;
  while ((this)->str[pos])
    {
      while ((this)->str[pos + j] == str[j])
	j = j + 1;
      if (j == lenght)
	return (pos);
      else
        j = 0;
      pos++;
    } 
  return (-1);
}

int emptyString(String * this)
{
  if ((this)->str != NULL && (this) != NULL)
    if ((this)->str[0] == '\0')
      return (1);
  return (-1);
}

char const*   c_strString(String * this)
{
  return ((this)->str);
}
size_t copyString(String * this, char* s, size_t n, size_t pos)
{
  unsigned int          i=0;
  unsigned int          j=0;

  s = malloc(strlen((this)->str));
  if ((this) == NULL)
    return (-1);
  if ((this)->str == NULL)
    return (-1);
  if (pos < 0)
    return (-1);
  while ((this)->str[i])
    {
      if (i >= pos && j < n)
        {
          s[j] = (this)->str[i];
          i++;
          j++;
        }
      else
        i++;
    }
  return (j);
}

int	_compareObjString(String * this, Object * ap)
{
  assert(this);
  assert(ap);
  if (isObject(ap))
    {
      if (classOf(ap, StringType))
	return compare_sString(this, (String*)ap);
      else if (classOf(ap, ByteArrayType))
	return compare_cString(this, ((ByteArray*)ap)->_array);
    }
  else
    return compare_cString(this, (char*)ap);  
}

int compare_sString(String * this, const String * str)
{
  return (strcmp((this)->str, (str)->str));
}

int compare_cString(String * this, char const* str)
{
  return (strcmp((this)->str, str));
}
int sizeString(String * this)
{
  if ((this) == NULL)
    return (-1);
  if ((this)->str == NULL || (this)->str[0] == '\0')
    return (-1);
  else
    return (strlen((this)->str));
}

void clearString(String * this)
{
  if ((this) != NULL)
    if ((this)->str != NULL)
      (this)->str[0] = '\0';
}

void		_assignObjectString(String * this, Object * ap)
{
  assert(this);
  assert(ap);
  if (isObject(ap))
    {
      if (classOf(ap, StringType))
	assign_sString(this, (String*)ap);
      else if (classOf(ap, ByteArrayType))
	assign_cString(this, ((ByteArray*)ap)->_array);
    }
  else
    assign_cString(this, (char*)ap);
}

void assign_sString(String * this, const String * str)
{
  if ((this) != NULL)
    if (str != NULL)
      if ((str)->str != NULL)
        (this)->str = strdup((str)->str);
}

void assign_cString(String * this, char const * s)
{
  if ((this) != NULL)
    if (s != NULL)
      (this)->str = strdup(s);
}

void	_appendObjectString(String * this, Object * ap)
{
  assert(this);
  assert(ap);
  if (isObject(ap))
    {
      if (classOf(ap, StringType))
	append_sString(this, (String*)ap);
      else if (classOf(ap, ByteArrayType))
	append_cString(this, ((ByteArray*)ap)->_array);
    }
  else
    append_cString(this, (char*)ap);
}

void append_sString(String * this, String * ap)
{
  char          *tmp;

  if ((this) != NULL)
    if ((ap) != NULL)
      if (this->str == NULL)
	this->assign(this, ap);
      else
	if ((ap)->str != NULL)
	  {
	    tmp = malloc(len(this) + len(ap));
	    tmp = strcat((this)->str, (ap)->str);
	    free(this->str);
	    this->str = strdup(tmp);
	    free(tmp);
	  }
}

void append_cString(String * this, char const* ap)
{
  char		*tmp;
  
  if ((this) != NULL)
    if (ap != NULL)
      if (this->str != NULL)
	{      
	  tmp = strcat((this)->str, ap);
	  //free(this->str);
	  this->str = strdup(tmp);
	  free(tmp);
	}
      else
	assign_cString(this, ap);
}

char atString(String * this, size_t pos)
{
  unsigned int          i=0;

  if ((this) != NULL)
    {
      if ((this)->str != NULL)
        {
          if (pos > strlen((this)->str))
            return (-1);
          else
            {
              while ((this)->str[i])
                {
                  if (pos == i)
                    return ((this)->str[i]);
                  i++;
                }
            }
          return (-1);
        }
    }
  return (-1);
}

char const	*to_stringString(Object * this)
{
  if (this != NULL)
    if (((String*)this)->str != NULL)
      return ((String*)this)->str;
  return "";
}

void	String_ctor(Object * this, va_list * ap)
{
  ((String*)this)->str = NULL;
  //  ((String*)this)->str = va_arg(*ap, char*);
}

void	String_dtor(Object * this)
{
  free(((String*)this)->str);
}

int	__lenString__(Object * this)
{
  if (this != NULL)
    if (((String*)this)->str != NULL)
      return strlen(((String*)this)->str);
  return 0;
}

String _descriptionString = {
  MAGIC,
  sizeof(String),
  "String",
  0,
  &String_ctor,
  &String_dtor,
  &to_stringString,
  &__cloneString__,
  &__equalsString__,
  &__lenString__,
  &atString,
  &_appendObjectString,
  &_assignObjectString,
  &clearString,
  &sizeString,
  &_compareObjString,
  &copyString,
  &c_strString,
  &emptyString,
  &_findObjString,
  &_insertObjString,
  &to_intString,
  &split_sString,
  &split_cString,
  ""
};

Class * StringType =  (Class*) &_descriptionString;
