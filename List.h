/*
** list.c for list in /home/tolsa_c/Work/List
** 
** Made by root
** Login   <root@nfast>
** 
** Started on  Fri Jun 28 19:20:20 2013 root
** Last update Thu Aug  1 10:26:45 2013 root
*/

#include <stdlib.h>
#include <stdio.h>
#include "object.h"
#include "new.h"

#define AllowList(T, tag)						\
									\
  typedef struct s_node##tag						\
  {									\
    T _value;								\
    struct s_node##tag * next;						\
  }Node##tag;								\
  typedef struct s_list##tag						\
  {									\
    Class		base;						\
    void		(*push_back)(struct s_list##tag *, T);		\
    void		(*push_front)(struct s_list##tag *, T);		\
    int			(*size)(struct s_list##tag *);			\
    T			(*back)(struct s_list##tag *);			\
    T			(*front)(struct s_list##tag *);			\
    void		(*pop_back)(struct s_list##tag *);		\
    void	     	(*pop_front)(struct s_list##tag *);		\
    void		(*pop_at)(struct s_list##tag *, int);		\
    T			(*at)(struct s_list##tag *, size_t);		\
    void		(*dump)(struct s_list##tag *, const char *);	\
    Node##tag		*lst;						\
  }List##tag;								\
  Node##tag		*__createNode##tag(T value)			\
  {									\
    Node##tag		*node;						\
									\
    node = malloc(sizeof(Node##tag));					\
    node->_value = value;						\
    node->next = 0;							\
  }									\
  void		_push_back##tag(List##tag *lst, T value)		\
  {									\
    Node##tag		*tmp;						\
    Node##tag		*item;						\
									\
    tmp = lst->lst;							\
    item = __createNode##tag(value);					\
    if (tmp == NULL)							\
      (lst->lst) = item;						\
    else								\
      {									\
	while (tmp->next)						\
	  tmp = tmp->next;						\
	tmp->next = item;						\
      }									\
  }									\
  void		_push_front##tag(List##tag *lst, T value)		\
  {									\
    Node##tag		*tmp;						\
    Node##tag		*item;						\
									\
    tmp = (lst->lst);							\
    item = __createNode##tag(value);					\
    if (tmp == NULL)							\
      {									\
	lst->lst = item;						\
      }									\
    else								\
      {									\
	item->next = lst->lst;						\
	lst->lst = item;						\
      }									\
  }									\
  void _dump##tag(List##tag *list, const char * printfString)		\
  {									\
    Node##tag *tmp;							\
									\
    tmp = (list->lst);							\
    if (list->lst == NULL)						\
      printf("[empty List]\n");						\
    while (tmp)								\
      {									\
	printf(printfString,tmp->_value);				\
	tmp = tmp->next;						\
      }									\
  }									\
  T	_frontList##tag(List##tag *lst)					\
  {									\
    return (lst->lst)->_value;						\
  }									\
  T	_backList##tag(List##tag *lst)					\
  {									\
    Node##tag	*tmp;							\
									\
    tmp = (lst->lst);							\
    while (tmp->next)							\
      tmp = tmp->next;							\
    return tmp->_value;							\
  }									\
  int	_sizeList##tag(List##tag *lst)					\
  {									\
    int	i;								\
    Node##tag	*tmp;							\
									\
    tmp = (lst->lst);							\
    if (tmp == NULL)							\
      return 0;								\
    i = 1;								\
    while (tmp->next)							\
      {									\
	++i;								\
	tmp = tmp->next;						\
      }									\
    return i;								\
  }									\
  void	_pop_back##tag(List##tag *lst)					\
  {									\
    Node##tag *tmp;							\
    if (lst->lst == NULL)						\
      return;								\
    else if (lst->lst->next == NULL)					\
      lst->lst = NULL;							\
    else								\
      {									\
	tmp = lst->lst;							\
	while (tmp->next->next)						\
	  tmp = tmp->next;						\
	tmp->next = tmp->next->next;					\
      }									\
  }									\
  void	_pop_front##tag(List##tag *lst)					\
  {									\
    if (lst->lst == NULL)						\
      return;								\
    else								\
      {									\
	lst->lst = lst->lst->next;					\
      }									\
  }									\
  void	_pop_at##tag(List##tag *lst, int where)				\
  {									\
    Node##tag *tmp;							\
    int		size;							\
    int		c;							\
    									\
    c = 0;								\
    size = _sizeList##tag(lst);						\
    if (where < 0 || where > size)					\
      return;								\
    if (where == size)							\
      {									\
	_pop_back##tag(lst);						\
	return;								\
      }									\
    if (where == 0)							\
      {									\
	_pop_front##tag(lst);						\
	return;								\
      }									\
    if (lst->lst == NULL)						\
      return;								\
    else if (lst->lst->next == NULL)					\
      return;								\
    else								\
      {									\
	tmp = lst->lst;							\
	while (++c < where)						\
	  tmp = tmp->next;						\
	tmp->next = tmp->next->next;					\
      }									\
  }									\
  T	_atList##tag(List##tag *lst, size_t p)				\
  {									\
    int	idx;								\
    Node##tag	*tmp;							\
									\
    tmp = (lst->lst);							\
    idx = -1;								\
    if (p >= 0 && p < _sizeList##tag(lst))				\
      {									\
	while (++idx < p)						\
	  tmp = tmp->next;						\
	return tmp->_value;						\
      }									\
  }									\
  void		__ctorList##tag(Object * this, va_list * ap)		\
  {}									\
  void		__dtorList##tag(Object * this)				\
  {}									\
  char const*	__toStringList##tag(Object * this)			\
  {									\
    return "List";							\
  }									\
  bool		__equalsList##tag(Object * this, Object * other)	\
  {									\
    return false;							\
  }									\
  Object		*__cloneList##tag(Object * this)		\
  {									\
    return NULL;							\
  }									\
  int		__lenList##tag(Object * this)				\
  {									\
    return _sizeList##tag((List##tag*)this);				\
  }									\
  List##tag _descriptionList##tag = {					\
    MAGIC,								\
    sizeof(List##tag),							\
    "List",								\
    0,									\
    &__ctorList##tag,							\
    &__dtorList##tag,							\
    &__toStringList##tag,						\
    &__cloneList##tag,							\
    &__equalsList##tag,							\
    &__lenList##tag,							\
    &_push_back##tag,							\
    &_push_front##tag,							\
    &_sizeList##tag,							\
    &_backList##tag,							\
    &_frontList##tag,							\
    &_pop_back##tag,							\
    &_pop_front##tag,							\
    &_pop_at##tag,							\
    &_atList##tag,							\
    &_dump##tag,							\
    NULL								\
  };									\
  Class * _##tag = (Class*) &_descriptionList##tag;			\
  
#define List(tag)					\
  struct s_list##tag					\
  
#define Node(tag)				\
  struct s_node##tag				\
  
#define createNode(tag, V)			\
  __createNode##tag(V);				\
  
