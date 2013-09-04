/*
** ThreadPool.c for 7 in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@epitech.net>
** 
** Started on  Sun Jun 23 16:10:19 2013 root
** Last update Thu Aug  1 10:26:16 2013 root
*/

#include "ThreadPool.h"
#include "new.h"
#include "Logger.h"

void                    _addTaskThread(ThreadPool *it, callable handle)
{
    int                 i;
    
    i = -1;
    while ((it->_tasks[++i] != NULL) && (i < MAX_CALLABLE));
    if (i < MAX_CALLABLE)
        it->_tasks[i] = handle;
}

void                    _addTaskWithArgThread(ThreadPool *it, callable handle, void *arg)
{
    int                 i;

    i = -1;
    while ((it->_tasks[++i] != NULL) && (i < MAX_CALLABLE));
    if (i < MAX_CALLABLE)
    {
        it->_tasks[i] = handle;
        it->_args[i] = arg;
    }
}

void                    _runTaskThread(ThreadPool *it, callable handle)
{
    int                 i;

    i = -1;
    while ((it->_pool[++i]->isRunning(it->_pool[i])) && (i < MAX_THREAD));
    if (i < MAX_THREAD)
      it->_pool[i]->start(it->_pool[i], handle);
}

void                    _runTaskWithArgThread(ThreadPool *it, callable handle, void *arg)
{
    int                 i;

    i = -1;
    while ((it->_pool[++i]->isRunning(it->_pool[i])) && (i < MAX_THREAD));
    if (i < MAX_THREAD)
      it->_pool[i]->startWithArg(it->_pool[i], handle, arg);
}

void                    _runAllThread(ThreadPool *it)
{
  int                 idxThread, idxTask;

  idxTask = -1;
  while ((++idxTask < MAX_CALLABLE) && (it->_tasks[idxTask] != NULL))
    {
      idxThread = -1;
      while ((++idxThread < MAX_THREAD) && (it->_pool[idxThread]->_running == 1));
      if (idxThread < MAX_THREAD)
        {
	  if (it->_args[idxTask] == NULL)
	    it->_pool[idxThread]->start(it->_pool[idxThread], it->_tasks[idxTask]);
	  else
	    it->_pool[idxThread]->startWithArg(it->_pool[idxThread], it->_tasks[idxTask], it->_args[idxTask]);
	}
      else
	logError("no available threads\n");
    }
}

void                    _joinAllThread(ThreadPool *it)
{
  int                 i;
    
  i = -1;
  while ((++i < MAX_THREAD))
    {
      if (it->_pool[i]->_running)
        {
	  it->_pool[i]->join(it->_pool[i]);   
	  __closeThread__(it->_pool[i]);
        }
    }
}

void			__ctorThreadPool__(Object * this, va_list * ap)
{
  ThreadPool          *it;
  Thread	      *tmp;
  int                 i;
    
  (void)ap;
  it = (ThreadPool*)this;
  i = -1;
  it->_pool = malloc(sizeof(Thread*) * MAX_THREAD);
  while (++i < MAX_THREAD)
    {
      tmp = new(ThreadType);
      it->_pool[i] = tmp;
    }
  i = -1;
  it->_tasks = malloc(sizeof(void*) * MAX_CALLABLE);
  while (++i < MAX_CALLABLE)
    it->_tasks[i] = NULL;
  i = -1;
  it->_args = malloc(sizeof(void*) * MAX_CALLABLE);
  while (++i < MAX_CALLABLE)
    it->_args[i] = NULL;
}

void                    __dtorThreadPool__(Object * it)
{
  int                 i;
    
  i = -1;
  while (++i < MAX_THREAD)
    delete(((ThreadPool*)it)->_pool[i]);
  free(((ThreadPool*)it)->_pool);
  free(((ThreadPool*)it)->_tasks);
  free(((ThreadPool*)it)->_args);
}

char const		*_threadPoolToString(Object * it)
{
  return "ThreadPool";
}

ThreadPool _descriptionThreadPool = {
  MAGIC,
  sizeof(ThreadPool),
  "ThreadPool",
  0,
  &__ctorThreadPool__,
  &__dtorThreadPool__,
  &_threadPoolToString,
  NULL,
  NULL,
  NULL,
  &_addTaskThread,
  &_addTaskWithArgThread,
  &_runTaskThread,
  &_runTaskWithArgThread,
  &_runAllThread,
  &_joinAllThread,
  NULL,
  NULL,
  NULL
};

Class * ThreadPoolType = (Class*) & _descriptionThreadPool;
