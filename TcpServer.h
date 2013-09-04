/*
** TcpServer.h for TcpServer in /root/Work/libobject-c
** 
** Made by root
** Login   <root@share.dedimax.com>
** 
** Started on  Mon Jul 29 09:47:30 2013 root
** Last update Mon Jul 29 10:40:48 2013 root
*/

#ifndef TCPSERVER_H_
# define TCPSERVER_H_

#include "Socket.h"
#include "Thread.h"
#include "List.h"
#include "object.h"

typedef void	*(*on_action_t)(Socket *);
//AllowList(Socket*, clients);

typedef struct s_tcpserver
{
  Class			base;
  Socket		*_masterSocket;
  int			(*listen)(struct s_tcpserver *, char *, int);
  Socket		*(*accept)(struct s_tcpserver *);
  int			(*select)(struct s_tcpserver *);
  List(clients)		*_clients;
  on_action_t		onConnect;
  on_action_t		onDelete;
  on_action_t		onData;
}TcpServer;

extern Class * TcpServerType;

#endif /* !TCPSERVER_H_ */
