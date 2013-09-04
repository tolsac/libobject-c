/*
** File.h for  in /home/tolsa_c//Work/File
** 
** Made by camille tolsa
** Login   <tolsa_c@epitech.net>
** 
** Started on  Tue Aug 13 11:33:31 2013 camille tolsa
** Last update Tue Sep  3 09:25:20 2013 root
*/

#ifndef FILE_H_
# define FILE_H_

#define SEPARATOR_RL		'\n'
#define BUFFER_SIZE_RL		4096
#define LENGTH_MAX_RL		1024

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "String.h"

#include "object.h"

typedef struct s_file
{
  /* parent class */
  Class         base;

  /* file creation/deletion methods */
  bool		(*create)(struct s_file *, Object *);
  bool		(*createIfNotExists)(struct s_file *, Object *);
  bool		(*open)(struct s_file *, Object *);
  bool		(*reOpen)(struct s_file *, Object *, int);
  bool		(*isOpen)(struct s_file *);
  bool		(*exists)(struct s_file *);
  bool		(*close)(struct s_file *);
  bool		(*rename)(struct s_file *, Object *);
  bool		(*remove)(struct s_file *);
  
  /* directory methods */
  struct s_file	**(*listRoots)(struct s_file*);
  bool		(*mkdir)(struct s_file *, Object *);
  bool		(*rmdir)(struct s_file *, Object *);

  /* I/O methods*/
  String	*(*readLine)(struct s_file *);
  String	*(*readAll)(struct s_file *);
  int		(*append)(struct s_file *, Object *, ...);
  bool		(*writeLine)(struct s_file *, Object *, ...);
  
  /* unused bugged function*/
  int		(*prepend)(struct s_file *, Object *, ...);
  
  /* utils methods */
  int		(*size)(struct s_file *);
  bool		(*canRead)(struct s_file *);
  bool		(*canWrite)(struct s_file *);
  bool		(*canExecute)(struct s_file *);
  bool		(*isFile)(struct s_file *);
  bool		(*isDirectory)(struct s_file *);
  String	*(*getName)(struct s_file *);
  void		*(*setName)(struct s_file *, Object *);

  /* attributes */
  FILE		*_fp;
  int		_size;
  bool		_open;
  String	*_fname;
}File;

void                    *_setNameFileCore(File *, char *);

extern Class * FileType;

#endif /* !FILE_H_ */
