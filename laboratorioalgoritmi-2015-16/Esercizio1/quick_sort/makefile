CFLAGS = -std=gnu99 -Wall -pedantic

Start: quick_sort.o quick_sort_test.o 
			gcc $(CFLAGS) quick_sort.o quick_sort_test.o -o Start

quick_sort.o: quick_sort.h quick_sort.c 
			gcc $(CFLAGS) -c quick_sort.c -O2

quick_sort_test.o: quick_sort.h quick_sort_test.c
			gcc $(CFLAGS) -c quick_sort_test.c

clean: 
	rm -f *.o
	rm -f quick_sort
