CFLAGS = -std=gnu99 -Wall -pedantic

Start: binary_search_tree_test.o 
			gcc $(CFLAGS)  binary_search_tree_test.o -o Start

binary_search_tree_test.o: binary_search_tree.h binary_search_tree_test.c
			gcc $(CFLAGS) -c binary_search_tree_test.c

clean: 
	rm -f *.o
	rm -f binary_search_tree
	rm -f Start
