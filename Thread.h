#ifndef __THREAD__
#define __THREAD__

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "object.h"

typedef struct s_thread
{
  Class		  base;    
  int             (*start)(struct s_thread *, callable);
  int             (*startWithArg)(struct s_thread *, callable, void *arg);
  int             (*join)(struct s_thread *);
  int             (*abort)(struct s_thread *);
  int             (*isRunning)(struct s_thread *);
  int             (*hasArg)(struct s_thread *);
  pthread_t       _thread;
  int             _running;
  void            *_arg;
}Thread;

extern Class * ThreadType;

#endif
