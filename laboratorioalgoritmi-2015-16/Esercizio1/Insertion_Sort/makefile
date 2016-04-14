CFLAGS = -std=gnu99 -Wall -pedantic

Start: insertion_sort.o insertion_sort_test.o 
			gcc $(CFLAGS) insertion_sort.o insertion_sort_test.o -o Start

insertion_sort.o: insertion_sort.h insertion_sort.c 
			gcc $(CFLAGS) -c insertion_sort.c

insertion_sort_test.o: insertion_sort.h insertion_sort_test.c
			gcc $(CFLAGS) -c insertion_sort_test.c

clean: 
	rm -f *.o
	rm -f insertion_sort
	rm -f Start
