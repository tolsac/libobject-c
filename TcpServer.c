/*
** TcpServer.c for TcpServer in /root/Work/libobject-c
** 
** Made by root
** Login   <root@share.dedimax.com>
** 
** Started on  Mon Jul 29 09:53:26 2013 root
** Last update Fri Aug  2 09:58:06 2013 root
*/

#include "TcpServer.h"
#include "Logger.h"
#include "new.h"

AllowList(Socket*,clients);

void		__ctorTcpServer__(Object * this, va_list * ap)
{
  (void)ap;
  ((TcpServer*)this)->_masterSocket = new(SocketType);
  ((TcpServer*)this)->_clients = new(_clients);
}

void		__dtorTcpServer__(Object * this)
{
  delete(((TcpServer*)this)->_masterSocket);
  free(this);
}

char const	*__tcpServerToString__(Object * this)
{
  return "TcpServer";
}

int		_listenTcpServer(TcpServer * this, char * host, int port)
{
  struct sockaddr_in	addr;
  int			ret[3] = {0};
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;//inet_addr(host);
  addr.sin_port = htons(port);
  ret[0] = this->_masterSocket->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ret[1] = bind(this->_masterSocket->_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  ret[2] = listen(this->_masterSocket->_socket, 100);
  logInfo("----- Server is starting -----\n");
  logInfo("# socket = %d\n", ret[0]);
  logInfo("# bind   = %d\n", ret[1]);
  logInfo("# listen = %d\n", ret[2]);
  return ((ret[0] && ret[1] && ret[2]) ? 1 : 1);
}

Socket		*_acceptTcpServer(TcpServer * this)
{
  Socket	*sck = new(SocketType);
  
  sck->_socket = accept(this->_masterSocket->_socket, NULL, NULL);
  sck->_connected = 1;
  logInfo("# new connection : %d\n", sck->_socket); 
  this->_clients->push_back(this->_clients, sck);
  if (this->onConnect != NULL)
    this->onConnect(sck);
  return sck;
}

int	        _selectTcpServer(TcpServer * this)
{
  fd_set	fread;
  Node(clients) *node;
  int		highest;
  Socket	*iter;
  
  logInfo("server is starting select() loop\n");
  while (1)
    {
      highest = this->_masterSocket->_socket;
      FD_ZERO(&fread);
      node = this->_clients->lst;
      FD_SET(this->_masterSocket->_socket, &fread);
      while (node)
	{
	  if (node->_value->_socket > highest)
	    highest = node->_value->_socket;
	  if (node->_value->_connected == 1)
	    FD_SET(node->_value->_socket, &fread);
	  node = node->next;
	}
      if (select(highest + 1, &fread, NULL, NULL, NULL) > -1)
	{
	  if (FD_ISSET(this->_masterSocket->_socket, &fread))
	    this->accept(this);
	  node = this->_clients->lst;
	  while (node)
	    {
	      if (FD_ISSET(node->_value->_socket, &fread))
		if (this->onData != NULL)
		  {
		    iter = new(SocketType);
		    iter->_socket = node->_value->_socket;
		    this->onData(iter);
		  }
	      node = node->next;
	    } 
	}
    }
}

TcpServer _descriptionTcpServer = {
  MAGIC,
  sizeof(TcpServer),
  "TcpServer",
  0,
  &__ctorTcpServer__,
  &__dtorTcpServer__,
  &__tcpServerToString__,
  NULL,
  NULL,
  NULL,
  NULL,
  &_listenTcpServer,
  &_acceptTcpServer,
  &_selectTcpServer,
  NULL,
  NULL,
  NULL,
  NULL
};

Class * TcpServerType = (Class*) & _descriptionTcpServer;
