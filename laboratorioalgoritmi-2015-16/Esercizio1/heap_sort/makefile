CFLAGS = -std=gnu99 -Wall -pedantic

Start: heap_sort.o heap_sort_test.o 
			gcc $(CFLAGS) heap_sort.o heap_sort_test.o -o Start

heap_sort.o: heap_sort.h heap_sort.c 
			gcc $(CFLAGS) -c heap_sort.c -O2

heap_sort_test.o: heap_sort.h heap_sort_test.c
			gcc $(CFLAGS) -c heap_sort_test.c

clean: 
	rm -f *.o
	rm -f heap_sort
	rm -f Start
