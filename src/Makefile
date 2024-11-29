CFLAGS = -Wall -Wextra
main : main.c serialsh.o
	gcc $(CFLAGS) -o main main.c serialsh.o
mainfs : main.c serialsh.o
	gcc $(CFLAGS) -o mainfs main.c serialsh.o -fsanitize=address
serialsh.o : Serialsh.c Serialsh.h
	gcc $(CFLAGS) -c Serialsh.c -o serialsh.o
