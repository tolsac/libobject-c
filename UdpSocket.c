/*
** UdpSocket.c for  in /home/tolsa_c/Work
**
** Made by root
** Login   <root@epitech.net>
**
** Started on  Sun Jun 23 15:09:24 2013 root
** Last update Fri Aug  2 10:18:23 2013 root
*/

#include <netdb.h>
#include "ByteArray.h"
#include "String.h"
#include "UdpSocket.h"

int		_sendObjUdpSocket(UdpSocket *sck, Object *o, ...)
{
  va_list	ap;
  int		ret;

  va_start(ap, o);
  if (isObject(o))
    ret = _sendUdpSocket(sck, str(o), len(o));
  else
    ret = _sendUdpSocket(sck, (char*)o, va_arg(ap, int));
  va_end(ap);
  return ret;
}

int             _sendUdpSocket(UdpSocket *sck, const char *buff, int length)
{
    return send(sck->_socket, buff, length, 0);
}

int		_sendTextObjUdpSocket(UdpSocket *sck, Object *o)
{
  int		ret;

  if (isObject(o))
    {
      if (classOf(o, ByteArrayType))
	ret = _sendTextUdpSocket(sck, ((ByteArray*)o)->_array);
      else if (classOf(o, StringType))
	ret = _sendTextUdpSocket(sck, ((String*)o)->str);
    }
  else
    ret = _sendTextUdpSocket(sck, (char*)o);
  return ret;
}

int             _sendTextUdpSocket(UdpSocket *sck, const char *buff)
{
  return send(sck->_socket, buff, strlen(buff), 0);
}

int             _availableUdpSocket(UdpSocket *sck)
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

int		_bindUdpSocket(UdpSocket *sck, char *host, int port)
{
  struct sockaddr_in addr;
  struct protoent    *p;

  p = getprotobyname("UDP");
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host);
  addr.sin_port = htons(port);
  sck->_socket = socket(AF_INET, SOCK_DGRAM, p->p_proto);
  return bind(sck->_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
}

int		_readObjUdpSocket(UdpSocket *sck, Object * o, int length)
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

int             _readUdpSocket(UdpSocket *sck, char *buff, int length)
{
    return recv(sck->_socket, buff, length, 0);
}

int             _closeUdpSocket(UdpSocket *sck)
{
    return close(sck->_socket);
}

void            __ctorUdpSocket__(Object * this, va_list * ap)
{
  (void)ap;
  ((UdpSocket*)this)->_socket = 0;
  ((UdpSocket*)this)->_port = 0;
  ((UdpSocket*)this)->_connected = 0;
}

void            __dtorUdpSocket__(Object * this)
{
  ((UdpSocket*)this)->close((UdpSocket*)this);
}

char const	*_socketToString(Object * this)
{
  return "UdpSocket";
}

int		__lenUdpSocket__(Object * this)
{
  return _availableUdpSocket((UdpSocket*)this);
}

UdpSocket	_descriptionUdpSocket = {
  MAGIC,
  sizeof(UdpSocket),
  "UdpSocket",
  0,
  &__ctorUdpSocket__,
  &__dtorUdpSocket__,
  &_socketToString,
  NULL,
  NULL,
  &__lenUdpSocket__,
  &_connectUdpSocket,
  &_sendObjUdpSocket,
  &_sendTextObjUdpSocket,
  &_availableUdpSocket,
  &_bindUdpSocket,
  &_readObjUdpSocket,
  &_closeUdpSocket,
  -1,
  -1,
  -1
};

Class * UdpSocketType = (Class*) &_descriptionUdpSocket;
