/*
** Quartz.h for Quartz in /home/tolsa_c/Work/LogWatcher
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Fri Jun 28 18:42:33 2013 root
** Last update Fri Jun 28 19:10:27 2013 root
*/

#ifndef QUARTZ_H_
# define QUARTZ_H_

#include "object.h"
#include "new.h"
#include "Thread.h"

typedef struct s_quartz
{
  Class			base;
  void			(*start)(struct s_quartz *, callable);
  void			(*startWithArg)(struct s_quartz *, callable, void*);
  int			_usecInterval;  
  int			_secInterval;  
}Quartz;

extern Class * QuartzType;

#endif /* !QUARTZ_H_ */
