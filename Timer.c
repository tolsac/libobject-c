/*
** Timer.c for Timer in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Mon Jun 24 12:12:51 2013 root
** Last update Thu Aug  1 10:26:26 2013 root
*/

#include "Timer.h"
#include "new.h"

void		__ctorTimer__(Object * this, va_list * ap)
{
  (void)ap;
  struct timeval t;
  gettimeofday(&t, NULL);
  ((Timer*)this)->_start = t.tv_sec * (uint64_t)1000000 + t.tv_usec; 
}

void		__dtorTimer__(Object * this)
{
  (void)this;
}

Object		*__cloneTimer__(Object * this)
{
  Timer		*clone = new(TimerType);
  
  clone->_start = ((Timer*)this)->_start;
  return clone;
}

bool		__equalsTimer__(Object * this, Object * other)
{
  if (((Timer*)this)->_start == ((Timer*)other)->_start)
    return true;
  return false;
}

void		_startTimer(Timer * this)
{
  struct timeval t;

  if (this != NULL)
    {
      gettimeofday(&t, NULL);
      this->_start = t.tv_sec * (uint64_t)1000000 + t.tv_usec; 
    }  
  else
    logError("Timer: start: null pointer\n");
}

double		_getElapsedTimeTimer(Timer * this)
{
  struct timeval	t;
  uint64_t		real;

  gettimeofday(&t, NULL);
  real = t.tv_sec * (uint64_t)1000000 + t.tv_usec; 
  return (double)((double)(real - this->_start)/(double)1000000);
}

char const	*_timerToString(Object * this)
{
  return "Timer";
}

Timer _descriptionTimer = {
  MAGIC,
  sizeof(Timer),
  "Timer",
  0,
  &__ctorTimer__,
  &__dtorTimer__,
  &_timerToString,
  &__cloneTimer__,
  &__equalsTimer__,
  NULL,
  &_startTimer,
  &_getElapsedTimeTimer,
  0
};

Class * TimerType = (Class*) & _descriptionTimer;
