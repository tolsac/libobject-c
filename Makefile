all:
	cc *.c -lpthread -g3 -D LOGGER_ERROR -w -pipe

clean:
	rm -f *.o
	rm -f *~
	rm -f #*#

fclean: clean

re:	fclean all