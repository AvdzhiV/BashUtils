CC = gcc
CFLAGS = -Wall -Werror -Wextra
TARGET = s21_grep

all: final 

final: s21_grep

s21_grep: s21_grep.o grep_functions.o
		$(CC) $(CFLAGS) -o $(TARGET) s21_grep.o grep_functions.o


s21_grep.o: 
	$(CC) $(CFLAGS) -c s21_grep.c

grep_functions.o:
		$(CC) $(CFLAGS) -c grep_functions.c

clean:
	rm *.o

rebuild: clean all



