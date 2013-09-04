#ifndef __THREADPOOL__
#define __THREADPOOL__

#include "Thread.h"
#include "object.h"

#define MAX_THREAD 20
#define MAX_CALLABLE 20

typedef struct s_threadpool
{
  Class		  base;    
  void            (*addTask)(struct s_threadpool *, callable);
  void            (*addTaskWithArg)(struct s_threadpool *, callable, void *);
  void            (*runTask)(struct s_threadpool *, callable);
  void            (*runTaskWithArg)(struct s_threadpool *, callable, void *);
  void            (*runAll)(struct s_threadpool *);
  void            (*joinAll)(struct s_threadpool *);
  Thread          **_pool;
  callable        *_tasks;
  void            **_args;

}ThreadPool;

extern Class * ThreadPoolType;

#endif
