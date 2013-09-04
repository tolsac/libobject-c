/*
** CircularBuffer.c for CircularBuffer in /home/tolsa_c/Work
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Mon Jun 24 11:31:40 2013 root
** Last update Thu Aug  1 10:24:38 2013 root
*/

#include "CircularBuffer.h"
#include "Logger.h"
#include "new.h"

void		__ctorCircularBuffer__(Object * this, va_list *ap)
{
  (void)ap;
  if (memset(((CircularBuffer*)this)->buf, 0, BUFFER_SIZE_CB) == NULL)
    logError("CircularBuffer: __ctor__: memset: fail\n");
  ((CircularBuffer*)this)->w = 0;
  ((CircularBuffer*)this)->r = 0;
  ((CircularBuffer*)this)->c = 0;
}

void		__dtorCircularBuffer__(Object * this)
{
  (void)this;
}

Object		*__cloneCircularBuffer(Object * this)
{
  CircularBuffer	*clone = new(CircularBufferType);
  
  clone->w = ((CircularBuffer*)this)->w;
  clone->r = ((CircularBuffer*)this)->r;
  clone->c = ((CircularBuffer*)this)->c;
  memcpy(clone->buf, ((CircularBuffer*)this)->buf, BUFFER_SIZE_CB);
  return clone;
}

bool		__equalsCircularBuffer(Object * this, Object * other)
{
  if (((CircularBuffer*)this)->r == ((CircularBuffer*)other)->r &&
      ((CircularBuffer*)this)->w == ((CircularBuffer*)other)->w &&
      ((CircularBuffer*)this)->c == ((CircularBuffer*)other)->c &&
      strncmp((char*)((CircularBuffer*)this)->buf, (char*)((CircularBuffer*)other)->buf, BUFFER_SIZE_CB))
    return true;
  return false;
}

char            *_getCircularBuffer(CircularBuffer * b)
{                                                          
  int                   i;                                 
  int                   j;                                 
  char                  *s;                                
                                                           
  if (b->w == b->r)                                        
    return (NULL);                                         
  s = malloc(BUFFER_SIZE_CB);                                 
  i = b->r;                                                
  j = 0;                                                   
  while (b->buf[i])                                        
    {                                                      
      s[j++] = b->buf[i];                                  
      i = (i + 1) % BUFFER_SIZE_CB;                           
    }                                                      
  s[j] = '\0';                                             
  if (s[j - 1] != '\n')                                    
    return (NULL);                                         
  return (s);                                              
}                                                          

int		__lenCircularBuffer(Object * this)
{
  char		*str;
  
  str = _getCircularBuffer((CircularBuffer*)this);
  if (str == NULL)
    return 0;
  else
    return strlen(str);
}

int             _writeCircularBuffer(CircularBuffer * b, char *s)  
{                                                          
  int                   i;                                 
                                                           
  i = -1;                                                  
  while (s[++i])                                           
    if (s[i] == '\n')                                      
      {                                                    
	b->buf[b->w] = '\n';                               
	b->w = (b->w + 1) % BUFFER_SIZE_CB;                   
	b->buf[b->w] = '\0';                               
	b->w = (b->w + 1) % BUFFER_SIZE_CB;                   
	b->c++;                                            
      }                                                    
    else                                                   
      {                                                    
	b->buf[b->w] = s[i];                               
	b->w = (b->w + 1) % BUFFER_SIZE_CB;                   
      }                                                    
  return (i);                                              
}                             

char            *_readCircularBuffer(CircularBuffer * b)           
{                                                          
  int                   j;                                 
  char                  *s;                                
                                                           
  if (b->w == b->r)                                        
    return (NULL);                                         
  s = malloc(BUFFER_SIZE_CB);                                 
  j = 0;                                                   
  while (b->buf[b->r])                                     
    {                                                      
      s[j++] = b->buf[b->r];                               
      b->r = (b->r + 1) % BUFFER_SIZE_CB;                     
    }                                                      
  b->c--;                                                  
  b->r = (b->r + 1) % BUFFER_SIZE_CB;                         
  s[j] = '\0';                                             
  /*
    if (s[j - 1] != '\n')                                    
    {                                                      
    b->r = (b->r - j) % BUFFER_SIZE_CB;                     
    return (NULL);                                       
    }
  */                                                      
  return (s);                                              
}            
                                                           
void            _clearCircularBuffer(CircularBuffer * b)                  
{                                                          
  b->w = 0;                                                
  b->r = 0;                                                
  b->c = 0;                                                
  memset(b->buf, 0, BUFFER_SIZE_CB);                          
} 

char const	*_circularBufferToString(Object * this)
{
  return _getCircularBuffer((CircularBuffer*)this);
}                                       


CircularBuffer _descriptionCircularBuffer = {
  MAGIC,
  sizeof(CircularBuffer),
  "CircularBuffer",
  0,
  &__ctorCircularBuffer__,
  &__dtorCircularBuffer__,
  &_circularBufferToString,
  &__cloneCircularBuffer,
  &__equalsCircularBuffer,
  &__lenCircularBuffer,
  &_writeCircularBuffer,
  &_readCircularBuffer,
  &_getCircularBuffer,
  &_clearCircularBuffer,
  {0},
  0,
  0,
  0
};

Class * CircularBufferType = (Class*) & _descriptionCircularBuffer;
