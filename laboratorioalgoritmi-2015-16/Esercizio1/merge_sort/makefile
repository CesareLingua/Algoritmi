CFLAGS = -std=gnu99 -Wall -pedantic

Start: merge_sort.o merge_sort_test.o 
			gcc $(CFLAGS) merge_sort.o merge_sort_test.o -o Start

quick_sort.o: merge_sort.h merge_sort.c 
			gcc $(CFLAGS) -c merge_sort.c -O2

quick_sort_test.o: merge_sort.h merge_sort_test.c
			gcc $(CFLAGS) -c merge_sort_test.c

clean: 
	rm -f *.o
	rm -f Start
