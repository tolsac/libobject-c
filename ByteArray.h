/*
** ByteArray.h for ByteArray in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Tue Jun 25 10:58:15 2013 root
** Last update Thu Aug  1 13:55:10 2013 root
*/

#ifndef BYTEARRAY_H_
# define BYTEARRAY_H_

#define BUFFER_SIZE_BYTEARRAY	2048

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Int.h"
#include "String.h"
#include "object.h"

typedef struct s_bytearray
{
  Class			base;
  void			(*append)(struct s_bytearray *, Object *, ...);
  void			(*prepend)(struct s_bytearray *, Object *, ...);
  bool			(*contains)(struct s_bytearray *, Object *);
  char			(*at)(struct s_bytearray *, size_t);
  bool			(*startsWith)(struct s_bytearray *, Object *);
  bool			(*endsWith)(struct s_bytearray *, Object *);
  void			(*replace)(struct s_bytearray *, char *, char *);
  size_t		(*size)(struct s_bytearray *);
  void			(*resize)(struct s_bytearray *, size_t);
  void			(*trim)(struct s_bytearray *);
  size_t		(*capacity)(struct s_bytearray *);
  char			*_array;
  size_t		_capacity;
}ByteArray;

extern Class * ByteArrayType;

void                    _checkCapacity(ByteArray * this, size_t len);
void                    _appendIntByteArray(ByteArray * this, Int * i);
void                    _appendObjByteArray(ByteArray * this, Object * o, ...);
void                    _appendByteArray(ByteArray * this, char * data, size_t len);
void                    _appendCharByteArray(ByteArray * this, char c);
void                    _appendStringByteArray(ByteArray * this, String * str);
void                    _appendByteArrayByteArray(ByteArray * this, ByteArray * other);
void                    _prependObjByteArray(ByteArray * this, Object * o, ...);
void                    _prependIntByteArray(ByteArray * this, Int * i);
void                    _prependByteArray(ByteArray * this, char * data, size_t len);
void                    _prependCharByteArray(ByteArray * this, char c);
void                    _prependStringByteArray(ByteArray * this, String * str);
void                    _prependByteArrayByteArray(ByteArray * this, ByteArray * other);
char                    _atByteArray(ByteArray * this, size_t idx);
bool                    _startsWithByteArray(ByteArray * this, char * needle);
bool                    _endsWithByteArray(ByteArray * this, char * needle);
void                    _replaceByteArray(ByteArray * this, char * search, char * replace);
bool                    _containsObjByteArray(ByteArray * this, Object * o);
bool                    _containsByteArray(ByteArray * this, char * needle);
bool                    _containsStringByteArray(ByteArray * this, String * needle);
bool                    _containsIntByteArray(ByteArray * this, Int * other);
bool                    _containsByteArrayByteArray(ByteArray * this, ByteArray * other);
size_t                  _sizeByteArray(ByteArray * this);
void                    _resizeByteArray(ByteArray * this, size_t len);
void                    _trimByteArray(ByteArray * this);
size_t                  _capacityByteArray(ByteArray * this);

#endif /* !BYTEARRAY_H_ */
