CC = gcc
CFLAGS = -Wall -Werror -Wextra
TARGET = s21_cat

all: final 

final: s21_cat

s21_cat: s21_cat.o cat_functions.o
		$(CC) $(CFLAGS) -o $(TARGET) s21_cat.o cat_functions.o


s21_cat.o: 
	$(CC) $(CFLAGS) -c s21_cat.c

cat_functions.o:
		$(CC) $(CFLAGS) -c cat_functions.c

clean:
	rm *.o

rebuild: clean all



