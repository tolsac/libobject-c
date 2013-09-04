/*
** CircularBuffer.h for CircularBuffer in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Mon Jun 24 11:25:22 2013 root
** Last update Wed Jul 31 05:06:28 2013 root
*/

#ifndef CIRCULARBUFFER_H_
# define CIRCULARBUFFER_H_

#include "object.h"

#define BUFFER_SIZE_CB	2048

typedef struct s_circularbuffer
{
  Class		base;
  int           (*append)(struct s_circularbuffer *, char *);
  char          *(*read)(struct s_circularbuffer *);
  char          *(*get)(struct s_circularbuffer *);
  void          (*clear)(struct s_circularbuffer *);
  char          buf[BUFFER_SIZE_CB];
  int           w;
  int           r;
  int           c;
}CircularBuffer;

extern Class * CircularBufferType;

#endif /* !CIRCULARBUFFER_H_ */
