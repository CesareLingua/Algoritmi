#include "binary_search_tree.h"

int main(int argc, char *argv[]){	
	bin_tree* tree;
	node* min;
	clock_t start, end; 
	double t;
	srand((int)clock());
	if(strcmp(argv[1], "--help") == 0){
		print_help();
	}

	unit_test();

	tree = new_bin_tree();
	start = clock();
	fill(tree, argv[1]);
	end = clock();
	t = (double) (end-start)/CLOCKS_PER_SEC;
	printf("\nTempo totale di inserimento di %d di records: %lf sec\n", N_RECORDS, t);
  
	start = clock();
	search(tree, argv[1]);
	end = clock();
	t = (double) (end-start)/CLOCKS_PER_SEC;
	printf("Tempo totale di ricerca di %d records: %lf sec\n", N_OPER, t);

	min = min_node_value(tree->root);
	printf("Stampa nodo MINIMO: 	%li\n", min->record->linum);

	start = clock();
	delete(tree, argv[1]);
	end = clock();
	t = (double) (end-start)/CLOCKS_PER_SEC;
	printf("Tempo totale di cancellazione di %d records: %lf sec\n\n", N_OPER, t);
	random_delete(tree->root, min, compare_long_int);

	min = min_node_value(tree->root);
	printf("Stampa nodo MINIMO: 	%li\n", min->record->linum);

	free(tree);
	
	return 0;
}
