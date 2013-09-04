/*
** Quartz.c for Quartz in /home/tolsa_c/Work/LogWatcher
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Fri Jun 28 18:47:55 2013 root
** Last update Thu Aug  1 10:25:15 2013 root
*/

#include "Quartz.h"

void		__ctorQuartz__(Object * this, va_list * ap)
{
  ((Quartz*)this)->_secInterval = va_arg(ap, int);
}

void		__dtorQuartz__(Object * this)
{
  (void)this;
}

char const	*__quartzToString__(Object * this)
{
  return "Quartz";
}

bool		__equalsQuartz__(Object * this, Object * other)
{
  (void)this;
  (void)other;
  return false;
}

Object		*__cloneQuartz__(Object * this)
{
  return NULL;
}

int		__lenQuartz__(Object * this)
{
  return 0;
}

void		_runQuartz(Quartz * this, callable c)
{
  Thread	*worker = new(ThreadType);
  
  while (1)
    {
      if (this->_usecInterval != 0)
	usleep(this->_usecInterval);
      else
	sleep(this->_secInterval);
      worker->start(worker, c);
      worker->join(worker);
    }
}

void		_runWithArgQuartz(Quartz * this, callable c, void *arg)
{
  Thread	*worker = new(ThreadType);
  
  while (1)
    {
      if (this->_usecInterval != 0)
	usleep(this->_usecInterval);
      else
	sleep(this->_secInterval);
      worker->startWithArg(worker, c, arg);
      worker->join(worker);
    }
}

Quartz _descriptionQuartz = {
  MAGIC,
  sizeof(Quartz),
  "Quartz",
  0,
  &__ctorQuartz__,
  &__dtorQuartz__,
  &__quartzToString__,
  &__cloneQuartz__,
  &__equalsQuartz__,
  &__lenQuartz__,
  &_runQuartz,
  &_runWithArgQuartz,
  0,
  0
};

Class * QuartzType = (Class*) & _descriptionQuartz;
