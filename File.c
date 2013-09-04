/*
** File.c for  in /home/tolsa_c//Work/File
** 
** Made by camille tolsa
** Login   <tolsa_c@epitech.net>
** 
** Started on  Tue Aug 13 11:48:43 2013 camille tolsa
** Last update Tue Sep  3 09:29:16 2013 root
*/

#include <stdarg.h>
#include "ByteArray.h"
#include "File.h"
#include "new.h"

/* parent class overriding methods */
void			__ctorFile__(Object * this, va_list * ap)
{
  (void)ap;
  ((File*)this)->_size = 0;
  ((File*)this)->_fp = NULL;
  ((File*)this)->_fname = new(StringType);
}

void			__dtorFile__(Object * this)
{
  if (((File*)this)->_fp != NULL)
    fclose(((File*)this)->_fp);
  delete(((File*)this)->_fname);
}

bool			__equalsFile__(Object * this, Object * other)
{
  //TODO
  return false;
}

Object			*__cloneFile__(Object * this)
{
  //TODO
  return NULL;
}

int			__lenFile__(Object * this)
{
  return ((File*)this)->size((File*)this);
}

char const		*_fileToString(Object * this)
{}

/* creation/deletion methods */
bool			_createFile(File * this, Object * arg)
{
  assert(this);
  assert(arg);
  this->setName(this, arg);
  if (this->exists(this))
    return false;
  if (isObject(arg))
    _createFileCore(this, str(arg));
  else
    _createFileCore(this, (char*)arg);
}

bool			_createIfNotExistsFile(File * this, Object * arg)
{
  assert(this);
  assert(arg);
  this->setName(this, arg);
  if (this->exists(this))
    return true;
  if (isObject(arg))
    _createFileCore(this, str(arg));
  else
    _createFileCore(this, (char*)arg);
}

bool			_createFileCore(File * this, char * name)
{
  this->_fp = fopen(name, "w+");
  if (this->_fp == NULL)
    return false;
  this->setName(this, name);
  this->_open = true;
  this->_size = 0;
  return true;
}

bool			_openFile(File * this, Object * arg)
{
  assert(this);
  assert(arg);
  if (isObject(arg))
    _openFileCore(this, str(arg));
  else
    _openFileCore(this, (char*)arg);
}

bool			_openFileCore(File * this, char * path)
{
  this->_fp = fopen(path, "r+");
  if (this->_fp == NULL)
    return false;
  this->setName(this, path);
  this->_open = true;
  this->_size = 0;
  return true;
}

bool			_reOpenFile(File * this, Object * arg)
{
  this->close(this);
  this->open(this, arg);
}

bool			_isOpenFile(File * this)
{
  assert(this);
  return this->_open;
}

bool			_existsFile(File * this)
{
  assert(this);
  if (access(this->_fname->str, F_OK) == -1)
    return false;
  return true;
}

bool			_closeFile(File * this)
{
  assert(this);
  if (fclose(this->_fp) == -1)
    return false;
  this->_open = false;
  return true;
}

bool			_renameFile(File * this, Object * arg)
{
  if (isObject(arg))
    _renameFileCore(this, str(arg));
  else
    _renameFileCore(this, (char*)arg);
}

bool			_renameFileCore(File * this, char * arg)
{
  if (rename(str(this->_fname), arg) == -1)
    return false;
  _setNameFileCore(this, arg);
  return true;
}

bool			_removeFile(File * this)
{
  assert(this);
  if (!_existsFile(this))
    return false;
  if (remove(str(this->getName(this))) == -1)
    return false;
  return true;
}


/* directory methods */
File			**_listRootsFile(File * this)
{
  DIR		*dp;
  File		**lst;
  struct dirent *ep;
  int		i = -1;
  int		j = -1;

  if (this->getName(this) == NULL)
    return NULL;
  dp = opendir(str(this->getName(this)));
  if (dp != NULL)
    {
      while (ep = readdir (dp))
	++i;
      closedir(dp);
    }
  else
    return NULL;
  lst = malloc(sizeof(FileType) * (i + 1));
  while (++j < i)
    lst[j] = malloc(sizeof(FileType));
  dp = opendir(str(this->getName(this)));
  if (dp != NULL)
    {
      j = -1;
      while (ep = readdir (dp))
	{
	  lst[++j] = new(FileType);
	  lst[j]->setName(lst[j], ep->d_name);
	}
      lst[++j] = NULL;
      closedir(dp);
    }
  else
    return NULL;
  return lst;
}

bool			_mkdirFile(File * this, Object * arg)
{
  if (arg == NULL && this->getName(this) == NULL)
    return false;
  if (arg == NULL)
    if (mkdir(str(this->getName(this)), S_IRWXU|S_IRGRP|S_IXGRP) != 0)
      return false;
    else
      return true;
  if (isObject(arg))
     _mkdirFile(this, str(arg));
  else
    if (mkdir((char*)arg, S_IRWXU|S_IRGRP|S_IXGRP) != 0)
      return false;
    else
      {
	_setNameFileCore(this, (char*)arg);
	return true;
      }
}

bool			_rmdirFile(File * this, Object * arg)
{
  if (arg == NULL && this->getName(this) == NULL)
    return false;
  if (arg == NULL)
    if (rmdir(str(this->getName(this))) != 0)
      return false;
    else
      return true;
  if (isObject(arg))
    _rmdirFile(this, str(arg));
  else
    if (rmdir((char*)arg) != 0)
      return false;
    else
      return true;
}

/* I/O Methods */
String			*_readLineFile(File * this)
{
  char			*buf;
  String		*str = new(StringType);
  int			len;
  size_t		nmemb = 0;
  static bool		reentrant = true;

  if (reentrant == true)
    rewind(this->_fp);
  buf = NULL;
  len = getline(&buf, &nmemb, this->_fp);
  if (len != -1)
    {
      str->append(str, buf);
      free(buf);
      reentrant = false;
      return str;
    }
  reentrant = true;
  return NULL;
}

String			*_readAllFile(File * this)
{
  String		*file = new(StringType);
  char			*buf;
  int			curs_pos;
  
  curs_pos = ftell(this->_fp);
  buf = malloc(this->size(this));
  rewind(this->_fp);
  fread(buf, this->size(this), 1, this->_fp);
  file->assign(file, buf);
  free(buf);
  fseek(this->_fp, curs_pos, SEEK_SET);
  return file;
}

int			_appendFileCore(File * this, char * s, int len)
{
  return fwrite(s, len, 1, this->_fp) * len;
}

int			_appendFile(File * this, Object * arg, ...)
{
  va_list		ap;
  int			ret;
  
  va_start(ap, arg);
  if (isObject(arg))
    ret = _appendFileCore(this, str(arg), len(arg));
  else
    ret = _appendFileCore(this, (char*)arg, va_arg(ap, int));
  va_end(ap);
  return ret;
}

bool			_writeLineFileCore(File * this, char * s, int len)
{
  if ((fwrite(s, len, 1, this->_fp) * len) == len)
    return true;
  return false;
}

bool			_writeLineFile(File * this, Object * arg, ...)
{
  va_list		ap;
  bool			ret;
  
  va_start(ap, arg);
  if (isObject(arg))
    ret = _writeLineFileCore(this, str(arg), len(arg));
  else
    ret = _writeLineFileCore(this, (char*)arg, va_arg(ap, int));
  va_end(ap);
  return ret;
}

int			_prependFileCore(File * this, char * s, int len)
{
  /*
  ByteArray		*content = new(ByteArrayType);
  String		*temp;
  
  temp = _readAllFile(this);
  content->append(content, temp);
  delete(temp);
  content->prepend(content, s, len);
  //this->close(this);
  if ((this->_fp = freopen(this->_fname->c_str(this->_fname), "r+", this->_fp)) == NULL)
    {
      this->_open = false;
      return -1;
    }
  char *e = str(content);
  fwrite(e, len(content), 1, this->_fp);
  _sizeFile(this);
  this->_open = true;
  return len;
  */
  return -1;
}

int			_prependFile(File * this, Object *arg, ...)
{
  va_list		ap;
  int			ret;
  
  va_start(ap, arg);
  if (isObject(arg))
    ret = _prependFileCore(this, str(arg), len(arg));
  else
    ret = _prependFileCore(this, (char*)arg, va_arg(ap, int));
  va_end(ap);
  return ret;
}


/* utils Methods */
int			_sizeFile(File * this)
{
  struct stat		s;

  if (stat(this->_fname->c_str(this->_fname), &s) == -1)
    return -1;
  this->_size = s.st_size;
  return this->_size;
}

bool			_canReadFile(File * this)
{
  if (access(this->_fname->c_str(this->_fname), R_OK) == -1)
    return false;
  return true;
}

bool			_canWriteFile(File * this)
{
  if (access(this->_fname->c_str(this->_fname), W_OK) == -1)
    return false;
  return true;
}

bool			_canExecuteFile(File * this)
{
  if (access(this->_fname->c_str(this->_fname), X_OK) == -1)
    return false;
  return true;
}

bool			_isFileFile(File * this)
{
  struct stat		s;

  if (stat(this->_fname->c_str(this->_fname), &s) == -1)
    return false;
  if (S_ISREG(s.st_mode))
    return true;
  return false;
}

bool			_isDirectoryFile(File * this)
{
  struct stat		s;

  if (stat(this->_fname->c_str(this->_fname), &s) == -1)
    return false;
  if (S_ISDIR(s.st_mode))
    return true;
  return false;
}

String			*_getNameFile(File * this)
{
  return this->_fname;
}

void			*_setNameFileCore(File * this, char * arg)
{
  this->_fname->assign(this->_fname, arg);
}

void			*_setNameFile(File * this, Object * arg)
{
  if (isObject(arg))
    _setNameFileCore(this, str(arg));
  else
    _setNameFileCore(this, (char*)arg);
}


File _descriptionFile = {
  MAGIC,
  sizeof(File),
  "File",
  0,
  &__ctorFile__,
  &__dtorFile__,
  &_fileToString,
  &__cloneFile__,
  &__equalsFile__,
  &__lenFile__,
  &_createFile,
  &_createIfNotExistsFile,
  &_openFile,
  &_reOpenFile,
  &_isOpenFile,
  &_existsFile,
  &_closeFile,
  &_renameFile,
  &_removeFile,
  &_listRootsFile,
  &_mkdirFile,
  &_rmdirFile,
  &_readLineFile,
  &_readAllFile,
  &_appendFile,
  &_writeLineFile,
  &_prependFile,
  &_sizeFile,
  &_canReadFile,
  &_canWriteFile,
  &_canExecuteFile,
  &_isFileFile,
  &_isDirectoryFile,
  &_getNameFile,
  &_setNameFile,
  0,
  0,
  false,
  NULL
};

Class * FileType = (Class*) & _descriptionFile;
