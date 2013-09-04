/*
** Int.c for Int in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Mon Jun 24 15:14:17 2013 root
** Last update Wed Aug  7 11:32:39 2013 root
*/

#include "Int.h"
#include "new.h"

void		__ctorInt__(Object * this, va_list * ap)
{
  ((Int*)this)->_value = va_arg(*ap, int);
}

void		__dtorInt__(Object * this)
{
  (void)this;
}

Object		*__cloneInt__(Object * this)
{
  return new(IntType, ((Int*)this)->_value);
}

bool		__equalsInt__(Object * this, Object * other)
{
  if (((Int*)this)->_value == ((Int*)other)->_value)
    return true;
  return false;
}

int		__lenInt__(Object * this)
{
  return strlen(((Int*)this)->toStr((Int*)this));
}

char const	*_intToString(Object * this)
{
  char		*str;
  
  asprintf(&str, "%d", ((Int*)this)->_value);
  return str;
}

String		*_toStringInt(Int * this)
{
  char		*str;
  String	*s = new(StringType);
  
  asprintf(&str, "%d", this->_value);
  s->append(s, str);
  return s;
}

String		*_toHexadecimalInt(Int * this)
{
  String	*ret = new(StringType);
  char		buff[50] = {0};
  
  sprintf(buff, "%x", this->_value);
  ret->append(ret, (char*)buff);
  return ret;
}

String		*_toOctalInt(Int * this)
{
  int		rem;
  int		i = 1;
  int		octal = 0;
  Int		*ret = new(IntType);
  int		n = this->_value;
  String	*s;
  
  while (n != 0)
    { 
      rem=n%8;
      n/=8;
      octal+=rem*i;
      i*=10;
    }
  ret->_value = octal;
  s = ret->toString(ret);
  delete(ret);
  return s;
}

char		*_toStrInt(Int * this)
{
  char		*str;

  asprintf(&str, "%d", this->_value);
  return str;
}

void		_valueOfInt_char(Int * this, char * str)
{
  this->_value = atoi(str);
}

void		_valueOfInt(Int * this, Object * arg)
{
  if (isObject(arg))
    {
      if (classOf(arg, StringType))
	_valueOfInt_char(this, ((String*)arg)->str);
    }
  else
    _valueOfInt_char(this, (char*)arg);
}

Int _descriptionInt = {
  MAGIC,
  sizeof(Int),
  "Int",
  0,
  &__ctorInt__,
  &__dtorInt__,
  &_intToString,
  &__cloneInt__,
  &__equalsInt__,
  &__lenInt__,
  &_toStringInt,
  &_toStrInt,
  &_valueOfInt,
  &_toHexadecimalInt,
  &_toOctalInt,
  0
};

Class * IntType = (Class*) & _descriptionInt;
