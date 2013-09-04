#ifndef __SOCKET__
#define __SOCKET__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

#include "object.h"

typedef struct s_socket
{
  Class		  base;    
  int             (*connect)(struct s_socket *, const char *, int);
  int             (*send)(struct s_socket *, Object *, ...);
  int             (*sendText)(struct s_socket *, Object *);
  int             (*available)(struct s_socket *);
  int		  (*bind)(struct s_socket *, char *, int);
  int             (*read)(struct s_socket *, Object *, int);
  int             (*close)(struct s_socket *);   
  int             _socket;
  int             _connected;
  int             _port;
}Socket;

extern Class * SocketType;

#endif
