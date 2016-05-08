CFLAGS = -std=gnu99 -Wall -pedantic

stress_bin_tree: binary_tree_method.o binary_search_tree_test.o unit_test.o
			gcc $(CFLAGS) binary_search_tree_test.o binary_tree_method.o unit_test.o -o stress_bin_tree

binary_search_tree_test.o: binary_search_tree.h unit_test.h binary_search_tree_test.c unit_test.c
			gcc $(CFLAGS) -c binary_search_tree_test.c -O2

binary_tree_method.o: binary_search_tree.h unit_test.h binary_search_tree_test.c
			gcc $(CFLAGS) -c binary_tree_method.c -O2

unit_test.o: unit_test.h binary_search_tree.h unit_test.c
			gcc $(CFLAGS) -c unit_test.c -O2

clean: 
	rm -f *.o
	rm -f stress_bin_tree
