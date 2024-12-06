CC = gcc
FLAG = -Wall -Wextra -Werror -std=c11 -pedantic

all: Day-3

Day-1:
	$(CC) $(FLAG) Day-1/TasBinaireMin.c -c -o Day-1/TasBinaireMin.o
	$(CC) $(FLAG) Day-1/Day1.c Day-1/TasBinaireMin.o -o Day-1/main
	cd Day-1 && ./main
	rm -f Day-1/*.o Day-1/main

Day-2:
	$(CC) $(FLAG) Day-2/Day-2.c -o Day-2/main
	cd Day-2 && ./main
	rm -f Day-2/*.o Day-2/main

Day-3:
	$(CC) $(FLAG) Day-3/Day-3.c -o Day-3/main
	cd Day-3 && ./main
	rm -f Day-3/*.o Day-3/main