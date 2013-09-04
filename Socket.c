/*
** Socket.c for  in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@epitech.net>
** 
** Started on  Sun Jun 23 15:09:24 2013 root
** Last update Fri Aug  2 10:18:23 2013 root
*/

#include "ByteArray.h"
#include "String.h"
#include "Socket.h"

int             _connectSocket(Socket *sck, const char *host, int port)
{
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host);
  addr.sin_port = htons(port);
  sck->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  return connect(sck->_socket,  (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
}

int		_sendObjSocket(Socket *sck, Object *o, ...)
{
  va_list	ap;
  int		ret;
  
  va_start(ap, o);
  if (isObject(o))
    {
      if (classOf(o, ByteArrayType))
	ret = _sendSocket(sck, ((ByteArray*)o)->_array, ((ByteArray*)o)->size(((ByteArray*)o)));
      else if (classOf(o, StringType))
	ret = _sendSocket(sck, ((String*)o)->str, strlen(((String*)o)->str));
    }
  else
    ret = _sendSocket(sck, (char*)o, va_arg(ap, int));
  va_end(ap);
  return ret;
}

int             _sendSocket(Socket *sck, const char *buff, int length)
{
    return send(sck->_socket, buff, length, 0);
}

int		_sendTextObjSocket(Socket *sck, Object *o)
{
  int		ret;

  if (isObject(o))
    {
      if (classOf(o, ByteArrayType))
	ret = _sendTextSocket(sck, ((ByteArray*)o)->_array);
      else if (classOf(o, StringType))
	ret = _sendTextSocket(sck, ((String*)o)->str);
    }
  else
    ret = _sendTextSocket(sck, (char*)o);
  return ret;
}

int             _sendTextSocket(Socket *sck, const char *buff)
{
  return send(sck->_socket, buff, strlen(buff), 0);
}

int             _availableSocket(Socket *sck)
{
  char        buff[65536] = {0};
  long        arg;
  int         ret;
    
  arg |= O_NONBLOCK; 
  fcntl(sck->_socket, F_SETFL, O_NONBLOCK);
  arg &= (~O_NONBLOCK);
  ret = recv(sck->_socket, buff, 65535, MSG_PEEK);
  fcntl(sck->_socket, F_SETFL, O_NONBLOCK);
  return ret;
}

int		_bindSocket(Socket *sck, char *host, int port)
{
  struct sockaddr_in addr;
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host);
  addr.sin_port = htons(port);
  sck->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  return bind(sck->_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
}

int		_readObjSocket(Socket *sck, Object * o, int length)
{
  char		*buff;
  int		ret;
  
  buff = malloc(sizeof(char) * length);
  memset(buff, 0, length);
  ret = recv(sck->_socket, buff, length, 0);
  if (isObject(o))
    {
      if (classOf(o, ByteArrayType))
	((ByteArray*)o)->append(((ByteArray*)o), buff, ret);
      else if (classOf(o, StringType))
	((String*)o)->append(((String*)o), buff); //TODO BUG CORRECTION passer length
    }
  else
    memcpy(o, buff, ret);
  free(buff);
  return ret;
}

int             _readSocket(Socket *sck, char *buff, int length)
{
    return recv(sck->_socket, buff, length, 0);
}

int             _closeSocket(Socket *sck)
{
    return close(sck->_socket);
}

void            __ctorSocket__(Object * this, va_list * ap)
{
  (void)ap;
  ((Socket*)this)->_socket = 0;
  ((Socket*)this)->_port = 0;
  ((Socket*)this)->_connected = 0;
}

void            __dtorSocket__(Object * this)
{
  ((Socket*)this)->close((Socket*)this);
}

char const	*_socketToString(Object * this)
{
  return "Socket";
}

int		__lenSocket__(Object * this)
{
  return _availableSocket((Socket*)this);
}

Socket	_descriptionSocket = {
  MAGIC,
  sizeof(Socket),
  "Socket",
  0,
  &__ctorSocket__,
  &__dtorSocket__,
  &_socketToString,
  NULL,
  NULL,
  &__lenSocket__,
  &_connectSocket,
  &_sendObjSocket,
  &_sendTextObjSocket,
  &_availableSocket,
  &_bindSocket,
  &_readObjSocket,
  &_closeSocket,
  -1,
  -1,
  -1
};

Class * SocketType = (Class*) &_descriptionSocket;
