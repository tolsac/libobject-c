/*
** Timer.h for Timer in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Mon Jun 24 12:09:32 2013 root
** Last update Mon Jun 24 14:35:27 2013 root
*/

#ifndef TIMER_H_
# define TIMER_H_

#include <stdint.h>
#include <sys/types.h>
#include "object.h"
#include "Logger.h"

typedef struct s_timer
{
  Class		base;
  void		(*start)(struct s_timer*);
  double  	(*getElapsedTime)(struct s_timer*);
  uint64_t	_start;
}Timer;

extern Class * TimerType;

#endif /* !TIMER_H_ */
