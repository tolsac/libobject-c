/*
** ByteArray.c for ByteArray in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Tue Jun 25 11:14:47 2013 root
** Last update Fri Aug  2 06:17:49 2013 root
*/

#include "ByteArray.h"
#include "Int.h"
#include "new.h"

void			_checkCapacity(ByteArray * this, size_t len)
{
  char			*tmp;
  
  if (len <= 0 || ((strlen(this->_array) + len) < this->_capacity))
    return;
  tmp = strdup(this->_array);
  free(this->_array);
  this->_capacity *= 2;
  this->_array = malloc(this->_capacity * sizeof(char));
  memset(this->_array, 0, this->_capacity - 1);
  memcpy(this->_array, tmp, strlen(tmp) - 1);
  free(tmp);
}

void			__ctorByteArray__(Object * this, va_list * ap)
{
  (void)ap;
  ((ByteArray*)this)->_array = malloc(BUFFER_SIZE_BYTEARRAY * sizeof(char));
  memset(((ByteArray*)this)->_array, 0, ((ByteArray*)this)->_capacity - 1);
  ((ByteArray*)this)->_capacity = BUFFER_SIZE_BYTEARRAY;
}

void			__dtorByteArray__(Object * this)
{
  free(((ByteArray*)this)->_array);
}

char const		*_byteArrayToString(Object * this)
{
  if (this != NULL)
    if (((ByteArray*)this)->_array != NULL)
      return ((ByteArray*)this)->_array;
  return "";
}

Object			*__cloneByteArray__(Object * this)
{
  ByteArray * clone = new(ByteArrayType);
  
  assert(this);
  clone->append(clone, ((ByteArray*)this)->_array, strlen(((ByteArray*)this)->_array));
  return clone;
}

bool			__equalsByteArray__(Object * this, Object * other)
{
  assert(this);
  assert(other);
  if (strcmp(((ByteArray*)this)->_array, ((ByteArray*)other)->_array) == 0)
    return true;
  return false;
}

int			__lenByteArray__(Object * this)
{
  assert(this);
  if (((ByteArray*)this)->_array != NULL)
    return strlen(((ByteArray*)this)->_array);
  return 0;
}

void			_appendIntByteArray(ByteArray * this, Int * i)
{
  _appendStringByteArray(this, i->toString(i));
}

void			_appendObjByteArray(ByteArray * this, Object * o, ...)
{
  va_list		ap;
  
  assert(this);
  assert(o);
  va_start(ap, o);
  if (isObject(o))
    {
      if (classOf(o, StringType))
	_appendStringByteArray(this, (String*)o);
      else if (classOf(o, ByteArrayType))
	_appendByteArrayByteArray(this, (ByteArray*)o);
      else if (classOf(o, IntType))
	_appendIntByteArray(this, (Int*)o);
    }
  else
    _appendByteArray(this, (char*)o, va_arg(ap, int));
  va_end(ap);
}

void			_appendByteArray(ByteArray * this, char * data, size_t len)
{
  _checkCapacity(this, len);
  memcpy(&(this->_array[strlen(this->_array)]), data, len);
}

void			_appendCharByteArray(ByteArray * this, char c)
{
  _checkCapacity(this, 1);
  this->_array[strlen(this->_array)] = c;
}

void			_appendStringByteArray(ByteArray * this, String * str)
{
  _appendByteArray(this, str->str, str->size(str));
}

void			_appendByteArrayByteArray(ByteArray * this, ByteArray * other)
{
  _appendByteArray(this, other->_array, strlen(other->_array));
}

void			_prependObjByteArray(ByteArray * this, Object * o, ...)
{
  va_list		ap;
  
  assert(this);
  assert(o);
  va_start(ap, o);
  if (isObject(o))
    {
      if (classOf(o, StringType))
	_prependStringByteArray(this, (String*)o);
      else if (classOf(o, ByteArrayType))
	_prependByteArrayByteArray(this, (ByteArray*)o);
      else if (classOf(o, IntType))
	_prependIntByteArray(this, (Int*)o);
    }
  else
    _prependByteArray(this, (char*)o, va_arg(ap, int));
  va_end(ap);
}

void			_prependIntByteArray(ByteArray * this, Int * i)
{
  _prependStringByteArray(this, i->toString(i));
}

void			_prependByteArray(ByteArray * this, char * data, size_t len)
{
  int			total;
  char			*tmp;

  total = len + strlen(this->_array);
  _checkCapacity(this, total);
  tmp = malloc(total * sizeof(char));
  memset(tmp, 0, total);
  memcpy(tmp, data, len);
  memcpy(&(tmp[len]), this->_array, total - len);
  free(this->_array);
  this->_array = tmp;
}

void			_prependCharByteArray(ByteArray * this, char c)
{
  _prependByteArray(this, &c, 1);
}

void			_prependStringByteArray(ByteArray * this, String * str)
{
  _prependByteArray(this, str->str, str->size(str));
}

void			_prependByteArrayByteArray(ByteArray * this, ByteArray * other)
{
  _prependByteArray(this, other->_array, strlen(other->_array));
}

char			_atByteArray(ByteArray * this, size_t idx)
{
  if (idx >= 0 && idx < strlen(this->_array))
    return this->_array[idx];
  return 0;
}

bool			_startwithObjByteArray(ByteArray * this, Object * o)
{
  assert(this);
  assert(o);
  if (isObject(o))
    {
      if (classOf(o, ByteArrayType))
	_startsWithByteArray(this, ((ByteArray*) o)->_array);
      else if (classOf(o, StringType))
	_startsWithByteArray(this, ((String*) o)->str);
      /*
	else
	wrong type of object
      */    
    }
  else
    _startsWithByteArray(this, (char*)o);
}

bool			_endswithObjByteArray(ByteArray * this, Object * o)
{
  assert(this);
  assert(o);
  if (isObject(o))
    {
      if (classOf(o, ByteArrayType))
	_endsWithByteArray(this, ((ByteArray*) o)->_array);
      else if (classOf(o, StringType))
	_endsWithByteArray(this, ((String*) o)->str);
      /*
	else
	 wrong type of object
      */    
    }
  else
    _endsWithByteArray(this, (char*)o);
}

bool			_startsWithByteArray(ByteArray * this, char * needle)
{
  char			*haystack;
  
  haystack = malloc(strlen(needle) * sizeof(char));
  strncpy(haystack, needle, strlen(needle));
  if (strncmp(haystack, needle, strlen(needle)) == 0)
    {
      free(haystack);
      return true;
    }
  free(haystack);
  return false;
}

bool			_endsWithByteArray(ByteArray * this, char * needle)
{
  if (strncmp(&(this->_array[strlen(this->_array) - strlen(needle)]), needle, strlen(needle)) == 0)
    return true;
  return false;
}

void			_replaceByteArray(ByteArray * this, char * search, char * replace)
{
  char			*p;
  char			*old;
  char			*new;
  int			c;
  int			sz;
  int			diff;

  c = 0;
  diff = 0;
  sz = strlen(search);
  for (p = strstr(this->_array, search); p != NULL; p = strstr(p + sz, search))
    {
      ++c;
      ++diff;
    }
  c = (strlen(replace) - sz) * c + strlen(this->_array);
  new = malloc(c * sizeof(char));
  memset(new, 0, c);
  old = this->_array;
  for (p = strstr(this->_array, search); p != NULL; p = strstr(p + sz, search))
    {
      strncpy(new + strlen(new), old, p - old);
      strcpy(new + strlen(new), replace);
      old = p + sz;
    }
  strcpy(new + strlen(new), old);
  _checkCapacity(this, strlen(new) - strlen(this->_array));
  if (strlen(search) <= strlen(replace))
    diff *= (strlen(search) - strlen(replace));
  else
    diff = 0;
  memset(this->_array, 0, this->_capacity - 1);
  memcpy(this->_array, new, strlen(new) - diff);
  free(new);
}

bool			_containsObjByteArray(ByteArray * this, Object * o)
{
  assert(this);
  assert(o);
  if (isObject(o))
    {
      if (classOf(o, StringType))
	_containsStringByteArray(this, (String*)o);
      else if (classOf(o, ByteArrayType))
	_containsByteArrayByteArray(this, (ByteArray*)o);
      else if (classOf(o, IntType))
	_containsIntByteArray(this, (Int*)o);
    }
  else
    _containsByteArray(this, (char*)o);
}


bool			_containsByteArray(ByteArray * this, char * needle)
{
  if (strstr(this->_array, needle) == NULL)
    return false;
  return true;
}

bool			_containsStringByteArray(ByteArray * this, String * needle)
{
  if (strstr(this->_array, needle->str) == NULL)
    return false;
  return true;
}

bool			_containsIntByteArray(ByteArray * this, Int * other)
{
  _containsStringByteArray(this, other->toString(other));
}

bool			_containsByteArrayByteArray(ByteArray * this, ByteArray * other)
{
  if (strstr(this->_array, other->_array) == NULL)
    return false;
  return true;
}

size_t			_sizeByteArray(ByteArray * this)
{
  return strlen(this->_array);
}

void			_resizeByteArray(ByteArray * this, size_t len)
{
  memcpy(&(this->_array[len]), 0, strlen(this->_array) - len);
}

void			_trimByteArray(ByteArray * this)
{
  char			*ibuf;
  char			*obuf;
  int			i;
  int			cnt;

  i = 0;
  cnt = 0;
  ibuf = this->_array;
  obuf = this->_array;
  if (this->_array)
    {
      for (ibuf = this->_array; *ibuf && (*ibuf == ' '); ++ibuf);
      if (this->_array != ibuf)
	memmove(this->_array, ibuf, ibuf - this->_array);
      while (*ibuf)
	{
	  if ((*ibuf == ' ') && cnt)
	    ibuf++;
	  else
	    {
	      if (!(*ibuf == ' '))
		cnt = 0;
	      else
		{
		  *ibuf = ' ';
		  cnt = 1;
		}
	      obuf[i++] = *ibuf++;
	    }
	}
      obuf[i] = '\0';
      while (--i >= 0)
	{
	  if (!(obuf[i] == ' '))
	    break;
	}
      obuf[++i] = '\0';
    }
}

size_t			_capacityByteArray(ByteArray * this)
{
  return this->_capacity;
}

ByteArray _descriptionByteArray = {
  MAGIC,
  sizeof(ByteArray),
  "ByteArray",
  0,
  &__ctorByteArray__,
  &__dtorByteArray__,
  &_byteArrayToString,
  &__cloneByteArray__,
  &__equalsByteArray__,
  &__lenByteArray__,
  &_appendObjByteArray,
  &_prependObjByteArray,
  &_containsObjByteArray,
  &_atByteArray,
  &_startsWithByteArray,
  &_endsWithByteArray,
  &_replaceByteArray,
  &_sizeByteArray,
  &_resizeByteArray,
  &_trimByteArray,
  &_capacityByteArray,
  NULL,
  BUFFER_SIZE_BYTEARRAY
};

Class * ByteArrayType = (Class*) & _descriptionByteArray;
