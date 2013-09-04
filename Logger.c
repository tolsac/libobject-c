/*
** ZLogger.c for ZLogger in /home/tolsa_c/Work/Logger
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Sat Jun 22 12:34:08 2013 root
** Last update Mon Jun 24 10:12:09 2013 root
*/

#include <stdio.h>
#include <stdarg.h>
#include "Logger.h"
#include "String.h"

void		logInfo(const char *s, ...)
{
#if defined LOGGER_INFO  || defined LOGGER_DEBUG
  va_list	ap;
  
  va_start(ap, s);
  vprintf(s, ap);
#endif
}

void		logDebug(const char *s, ...)
{
#if defined LOGGER_DEBUG 
  va_list	ap;

  va_start(ap, s);    
  vprintf(s, ap);
#endif
}

void		logWarn(const char *s, ...)
{
#if defined LOGGER_WARN || defined LOGGER_DEBUG
  va_list	ap;
    
  va_start(ap, s);
  vprintf(s, ap);
#endif
}

void		logError(const char *s, ...)
{
#if defined LOGGER_ERROR || defined LOGGER_DEBUG
  va_list	ap;
    
  va_start(ap, s);
  vprintf(s, ap);
#endif
}

