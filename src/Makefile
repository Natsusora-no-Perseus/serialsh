CFLAGS = -Wall -Wextra
main : main.c serialsh.o
	gcc $(CFLAGS) -o main main.c serialsh.o
mainfs : main.c serialsh.o
	gcc $(CFLAGS) -o mainfs main.c serialsh.o -fsanitize=address
serialsh.o : serialsh.c serialsh.h
	gcc $(CFLAGS) -c serialsh.c -o serialsh.o
