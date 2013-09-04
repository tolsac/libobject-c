/*
** ZLogger.h for ZLogger in /home/tolsa_c/Work/Logger
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Sat Jun 22 12:34:27 2013 root
** Last update Sun Jun 23 22:21:00 2013 root
*/

#ifndef ZLOGGER_H_
# define ZLOGGER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void		logInfo(const char *s, ...);
void		logWarn(const char *s, ...);
void		logDebug(const char *s, ...);
void		logError(const char *s, ...);

/*

Logger:
si def #LOGGER_ERROR_FILE

*/

#endif /* !ZLOGGER_H_ */
