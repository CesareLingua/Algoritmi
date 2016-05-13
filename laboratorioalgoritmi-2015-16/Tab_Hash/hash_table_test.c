#include "hash_table.h"
#include "unit_test.h"

int main(int argc, char* argv[]){
	node** hash_table;
	clock_t start, end; 
	double t;
	srand((int)clock());

	if(strcmp(argv[1], "--help") == 0){
		print_help();
	}

	//unit_test();

	hash_table = make_table();

	start = clock();
	insert_file_records(hash_table, argv[1]);
	end = clock();
	t = (double) (end - start)/ CLOCKS_PER_SEC;
	printf("\nTempo totale di INSERIMENTO di %d di records: %lf sec\n\n", N_RECORDS, t);


	t = search_key(hash_table, argv[1]);
	printf("Tempo totale netto di RICERCA di %d di records: %lf sec\n", N_OPER, t);

	//print_table(hash_table, argv[1], HSIZE);

	t = delete_key(hash_table, argv[1]);
	printf("\nTempo totale di CANCELLAZIONE di %d di records: %lf sec\n", N_OPER, t);

	//print_table(hash_table, argv[1], HSIZE);

	free(hash_table);
}