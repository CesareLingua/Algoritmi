CFLAGS = -std=gnu99 -Wall -pedantic

Start: binary_tree_method.o binary_search_tree_test.o
			gcc $(CFLAGS) binary_search_tree_test.o binary_tree_method.o -o stress_bin_tree

binary_search_tree_test.o: binary_search_tree.h binary_search_tree_test.c
			gcc $(CFLAGS) -c binary_search_tree_test.c -O2

binary_tree_method.o: binary_search_tree.h binary_search_tree_test.c
			gcc $(CFLAGS) -c binary_tree_method.c -O2

clean: 
	rm -f *.o
	rm -f binary_search_tree
	rm -f binary_tree_method
	rm -f stress_bin_tree
