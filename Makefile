main : main.o projet2019.o listes_generiques.o
	gcc main.o projet2019.o listes_generiques.o -o main
main.o : main.c projet2019.h listes_generiques.h
	gcc -c -Wall main.c
projet2019.o : projet2019.c
	gcc -c -Wall projet2019.c
listes_generiques.o  : listes_generiques.c
	gcc -c -Wall listes_generiques.c
clean :
	rm *.o

