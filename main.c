/*
** main.c for  in /home/tolsa_c/Work/Other/MailBomber
** 
** Made by root
** Login   <root@epitech.net>
** 
** Started on  Tue Jul  2 11:34:54 2013 root
** Last update Tue Sep  3 09:40:50 2013 root
*/
#include "Timer.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include "File.h"
#include "List.h"
#include "String.h"
#include "ByteArray.h"
#include "CircularBuffer.h"
#include "Int.h"
#include "new.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

AllowList(char*, string);
int		err = 0;

void		*onco(Socket *s)
{
  s->sendText(s, "testOnConnect");
}

int		assert_str(char* tag_test, char *res, void *fct)
{
  if (!isObject(fct))
    {
      if (strcmp(res, fct) == 0)
	{
	  printf(" %sTRUE%s => ", KGRN, KNRM);
	  printf("%s\n", tag_test);
	  return 0;
	}
    }
  else
    {
      if (strcmp(res, ((String*)fct)->str) == 0)
	{
	  printf(" %sTRUE%s => ", KGRN, KNRM);
	  printf("%s\n", tag_test);
	  return 0;
	}
    }
  if (isObject(fct))
    printf(" %sFALSE%s exepected [%s] got [%s] => ",KRED,KNRM, res, ((String*)fct)->str);
  else  
    printf(" %sFALSE%s exepected [%s] got [%s] => ",KRED,KNRM, res, (char*)fct);
  printf("%s\n", tag_test);
  err++;
}

int		assert_bool(char* tag_test, bool res, bool fct)
{
  if (res == fct)
    {
      printf(" %sTRUE%s => ", KGRN, KNRM);
      printf("%s\n", tag_test);
      return 0;
    }
  else
    printf(" %sFALSE%s => ", KRED, KNRM);
  printf("%s\n", tag_test);
  err++;
}

int		assert_int(char* tag_test, int res, int fct)
{
  if (res == fct)
    {
      printf(" %sTRUE%s => ", KGRN, KNRM);
      printf("%s\n", tag_test);
    return 0;
    }
  else
    printf(" %sFALSE%s exepected [%s] got [%s] => ",KRED,KNRM, res, fct);
  printf("%s\n", tag_test);    
  err++;
}


//TEST
void		testString_total()
{
  String	*str = new(StringType);
  
  str->assign(str, "a");
  str->append(str, "b");
  str->append(str, "c");
  str->append(str, "d");
  str->append(str, "e");
  assert_str("Test #1 assign", "abcde", str->str);
  str->clear(str);
  assert_str("Test #2 clear", "", str->str);
  assert_int("Test #3 size", 0, len(str->str));
  str->append(str, "waka <-S-> waka");
  assert_str("Test #4 append_c", "waka <-S-> waka", str->str);
}

void		testString_assign_append()
{
  String        *str = new(StringType);
  String        *other = new(StringType);
  String	*sentence = new(StringType);

  str->append(str, "Hello ");
  other->append(str, "World!");
  sentence->assign(sentence, str);
  sentence->append(sentence, other);
  assert_str("Test #1 append", "Hello World!", sentence->str);
  delete(str);
  delete(other);
  delete(sentence);
}

void		testString_toInt()
{
  String	*str = new(StringType);
  
  str->assign(str, "42");
  assert_int("Test #2 to_int", 42, str->toInt(str));
  delete(str);  
}

void		testString()
{
  testString_assign_append();
  testString_toInt();
  testString_total();
}

void		testByteArray()
{
  ByteArray	*ba = new(ByteArrayType);
  ByteArray	*other = new(ByteArrayType);
  String	*str = new(StringType);
  
  other->append(other, "ByteArray", 9);
  str->assign(str, "I'm a ");
  
  ba->append(ba, "Hello", 5);
  ba->append(ba, " ", 1);
  ba->append(ba, str);
  ba->append(ba, other);
  assert_str("Test #1 append", "Hello I'm a ByteArray", ba->_array);
  assert_int("Test #2 size", 21, ba->size(ba));
  ba->replace(ba, "Hello", "Hi");
  assert_str("Test #3 replace", "Hi I'm a ByteArray", ba->_array);
  assert_int("Test #4 startsWith", 1, ba->startsWith(ba, "Hi I'"));
  assert_int("Test #5 endsWith", 1, ba->endsWith(ba, "ByteArray"));
  ba->prepend(ba, "Hey ... ", 8);
  assert_str("Test #6 prepend", "Hey ... Hi I'm a ByteArray", ba->_array);
  assert_int("Test #7 contains", 1, ba->contains(ba, "..."));
  assert_int("Test #8 contains", 1, ba->contains(ba, str));
  delete(ba);
  delete(other);
  delete(str);
}

void		testCircularBuffer()
{
  CircularBuffer *c = new(CircularBufferType);
  
  c->append(c, "Cir");
  c->append(c, "cu");
  c->append(c, "lar");
  c->append(c, "\n");
  assert_str("Test #1 append", "Circular\n", c->get(c));
  c->append(c, "Buffer\n");
  assert_str("Test #2 append", "Circular\n", c->get(c));
  assert_str("Test #3 read", "Circular\n", c->read(c));
  assert_str("Test #4 read", "Buffer\n", c->read(c));
  c->append(c, "empty_ring\n");
  assert_str("Test #5 get", "empty_ring\n", c->get(c));
  free(c);
}

int		testBuiltin()
{
  String		*s = new(StringType);
  ByteArray		*b = new(ByteArrayType);
  CircularBuffer	*c = new(CircularBufferType);
  List(string)		*l = new(_string);
  Int			*i = new(IntType);
  Int			*j = new(IntType);
  int			a = hash(s);
  char			*notAnObj = "0xdeadbeef";
  
  i->_value = 42;
  j = i->base.__clone__(i);
  s->assign(s, "123456789");
  b->append(b, "normal", 6);
  c->append(c, "normal\n");
  l->push_back(l, "one");
  l->push_back(l, "two");

  assert_str("Test #1 name()", "String", name(s));
  assert_str("Test #2 name()", "ByteArray", name(b));
  assert_str("Test #3 name()", "CircularBuffer", name(c));
  assert_str("Test #4 name()", "List", name(l));

  assert_str("Test #5 str()", "123456789", str(s));
  assert_str("Test #6 str()", "normal", str(b));
  assert_str("Test #7 str()", "normal\n", str(c));
  assert_str("Test #8 str()", "List", str(l));
  
  assert_int("Test #9 len()", 9, len(s));
  assert_int("Test #10 len()", 6, len(b));
  assert_int("Test #11 len()", 7, len(c));
  assert_int("Test #12 len()", 2, len(l));
  
  assert_bool("Test #13 equals() ", true, equals(i, j));
  assert_bool("Test #14 equals() ", false, equals(NULL, j));
  assert_bool("Test #15 equals() ", false, equals(i, NULL));
  assert_bool("Test #16 equals() ", false, equals(NULL, NULL));

  assert_int("Test #17 hash()", a, hash(s));
  a = hash(b);
  assert_int("Test #18 hash()", a, hash(b));
  a = hash(c);
  assert_int("Test #19 hash()", a, hash(c));
  a = hash(l);
  assert_int("Test #20 hash()", a, hash(l));

  assert_bool("Test #21 isObject()", true, isObject(c));
  assert_bool("Test #22 isObject()", true, isObject(s));
  assert_bool("Test #23 isObject()", true, isObject(b));
  assert_bool("Test #24 isObject()", true, isObject(l));
  assert_bool("Test #25 isObject()", false, isObject(&a));
  assert_bool("Test #25 isObject()", false, isObject(notAnObj));

  assert_bool("Test #26 classOf()", true, classOf(c, CircularBufferType));
  assert_bool("Test #27 classOf()", true, classOf(s, StringType));
  assert_bool("Test #28 classOf()", true, classOf(b, ByteArrayType));
  assert_bool("Test #29 classOf()", true, classOf(l, _string));
  assert_bool("Test #30 classOf()", false, classOf(&a, IntType));
  assert_bool("Test #31 classOf()", false, classOf(notAnObj, StringType));
  
  delete(s);
  delete(b);
  delete(c);
  delete(l);
}

void		testInt()
{
  Int		*i = new(IntType);
  Int		*j = new(IntType);
  Int		*k = new(IntType);
  String	*s = new(StringType);
  
  s->append(s, "42");
  i->valueOf(i, "42");
  j->valueOf(j, s);
  k->valueOf(k, "32");
  assert_int("Test #1 valueOf", 42, i->_value);
  assert_int("Test #2 valueOf", 42, j->_value);
  assert_bool("Test #3 equals", true, equals(i, j));
  assert_str("Test #4 str", str(i), str(s));
  assert_str("Test #5 str", str(j), str(s));
  assert_str("Test #6 str", str(i), str(j));
  assert_int("Test #7 len", 2, len(i));
  assert_str("Test #8 toHex", "20", k->toHexadecimal(k));
  assert_str("Test #9 toOct", "40", k->toOctal(k));
  delete(i);
  delete(j);
  delete(s);
  delete(k);
}

void		testNetwork()
{
  
  Socket	*clt1 = new(SocketType);
  Socket	*clt2 = new(SocketType);
  ByteArray	*buff = new(ByteArrayType);
  
  assert_int("Test #1 connect", 0, clt1->connect(clt1, "127.0.0.1", 4321));
  assert_int("Test #2 connect", 0, clt2->connect(clt2, "127.0.0.1", 4321));
  usleep(1);
  assert_int("Test len(Socket)", 13, len(clt1));
  assert_int("Test #3 read", 13, clt1->read(clt1, buff, 500));
  assert_str("Test #4 read", "testOnConnect", buff->_array);
  assert_bool("Test #5 read", false, buff->contains(buff, "onConnect"));
  assert_bool("Test #6 read", true, buff->contains(buff, "OnConnect"));
  delete(clt1);
  delete(clt2);
  delete(buff);
}

void		*run_srv(void *d)
{
  TcpServer	*srv = new(TcpServerType);
  
  srv->onConnect = onco;
  srv->listen(srv, "127.0.0.1", 4321);
  srv->select(srv);
}

void		testFile()
{
  File          *f = new(FileType);
  File          *dir = new(FileType);
  File          **lst;
  File          *tree = new(FileType);
  String        *s = new(StringType);
  String        *result = new(StringType);

  f->setName(f, "testfile.tst");
  if (!f->exists(f))
    assert_bool("Test creation", true, f->create(f, "testfile.tst"));
  if (!f->isOpen(f))
    f->open(f, "testfile.tst");
  assert_bool("Test writeLine  ", true, f->writeLine(f, "one\n", 4));
  assert_bool("Test writeLine  ", true, f->writeLine(f, "two\n", 4));
  assert_bool("Test writeLine  ", true, f->writeLine(f, "three\n", 6));
  assert_bool("Test writeLine  ", true, f->writeLine(f, "zero\n", 5));

  result->append(result, f->readAll(f));
  s->append(s, "one\ntwo\nthree\nzero\n");
  assert_bool("Test checkTests ", true, equals(s, result));
  assert_bool("Test deletion", true, f->remove(f));

  dir->setName(dir, "sample");
  assert_bool("Test creation", true, dir->mkdir(dir, NULL));
  assert_bool("Test deletion", true, dir->rmdir(dir, NULL));
  delete(f);
  delete(dir);

  int h = -1;
  tree->setName(tree, "/");
  lst = tree->listRoots(tree);
  //  while (lst[++h])
  //  printf("[%s]\n", str(lst[h]->getName(lst[h])));
  delete(tree);
  delete(*lst);


  File			*test = new(FileType);
  
  test->setName(test, "a.out");
  assert_bool("Test exists", true, test->exists(test));
  delete (test);
  
  test = new(FileType);
  test->setName(test, "testfile.tst");
  test->create(test, "testfile.tst");
  assert_bool("Test exists", true, test->exists(test));
  assert_bool("Test rename", true, test->rename(test, "renamed_file.tst"));
  assert_bool("Test canRead", true, test->canRead(test));
  assert_bool("Test canWrite", true, test->canWrite(test));
  assert_bool("Test canExecute", false, test->canExecute(test));
  assert_bool("Test isFile", true, test->isFile(test));
  assert_bool("Test isOpen", true, test->isOpen(test));
  test->close(test);
  assert_bool("Test isOpen", false, test->isOpen(test));
  assert_bool("Test remove", true, test->remove(test));
  //  delete(test);

  File			*test2 = new(FileType);
  test2->setName(test2, "oneDir");
  assert_bool("Test mkdir", true, test2->mkdir(test2, NULL));
  assert_bool("Test isDir", true, test2->isDirectory(test2));
  assert_bool("Test isFile", false, test2->isFile(test2));
  assert_bool("Test rmdir", true, test2->rmdir(test2, NULL));
  delete(test2);
}

int		main(int ac, char **av)
{
  Timer		*t = new(TimerType);
  Thread	*thd = new(ThreadType);

  t->start(t);
  thd->start(thd, run_srv);
  while (t->getElapsedTime(t) < 0.2f);
  printf("\nString test \n");
  testString();
  printf("\nByteArray test \n");
  testByteArray();
  printf("\nCircularBuffer test \n");
  testCircularBuffer();  
  printf("\nlibrary builtin test \n");
  testBuiltin();  
  printf("\nNetwork test \n");
  testNetwork();  
  printf("\nInt test \n");
  testInt();  
  printf("\nFile test \n");
  testFile();  
  printf("\nTests duration %0.3f sec with %d errors \n", t->getElapsedTime(t), err);
}
