/*
** Thread.c for  in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@epitech.net>
** 
** Started on  Sun Jun 23 15:36:49 2013 root
** Last update Thu Aug  1 10:26:04 2013 root
*/

#include "Thread.h"

int             _startThread(Thread * t, callable handle)
{
    int         ret = 0;

    if ((ret = pthread_create(&(t->_thread), NULL, handle, NULL)) == 0)
        t->_running = 1;
    return ret;
}

int             _startWithArgThread(Thread * t, callable handle, void *arg)
{
    int         ret = 0;
    
    if ((ret = pthread_create(&(t->_thread), NULL, handle, arg)) == 0)
        t->_running = 1;
    return ret;
}

int             _joinThread(Thread * t)
{
    if (!t->isRunning(t))
        return 1;
    return pthread_join(t->_thread, NULL);
}

int             _abortThread(Thread * t)
{
    int         ret = 0;
    
    if ((ret = pthread_cancel(t->_thread)) == 0)
        t->_running = 0;
    return ret;
}

int             _isRunningThread(Thread * t)
{
    return t->_running;
}

int             _hasArgThread(Thread * t)
{
    if (t->_arg != NULL)
        return 1;
    return 0;
}

void            __closeThread__(void *t)
{
    ((Thread*)t)->_running = 0;
}

void            *__getArgThread__(void *t)
{
    return ((Thread*)t)->_arg;
}

void            __ctorThread__(Object * thd, va_list * ap)
{
  ((Thread*)thd)->_running = 0;
  ((Thread*)thd)->_thread = (pthread_t)0;
  ((Thread*)thd)->_arg = NULL;
}

void            __dtorThread__(Object *t)
{
  ((Thread*)t)->_arg = NULL;
}

char const	*_threadToString(Object * t)
{
  return "Thread";
}

Thread	_descriptionThread = {
  MAGIC,
  sizeof(Thread),
  "Thread",
  0,
  &__ctorThread__,
  &__dtorThread__,
  &_threadToString,
  NULL,
  NULL,
  NULL,
  &_startThread,
  &_startWithArgThread,
  &_joinThread,
  &_abortThread,
  &_isRunningThread,
  &_hasArgThread,
  (pthread_t)0,
  -1,
  NULL
};

Class * ThreadType = (Class*) & _descriptionThread;
