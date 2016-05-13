#include "unit_test.h"
#include "hash_table.h"

void insert_equal_element(){
	node** hash_table;
	key* k;
	int i;

	hash_table = (node**)malloc(sizeof(node*)*5);
	for(i = 0; i < 5; i++){
		k = new_key(0, "", 0, 0);
		hash_table[i] = new_node(k);
	}
	k = new_key(0, NULL, 52, 0);
	insert_hash_table(hash_table, k, compare_long_int);
	
	insert_hash_table(hash_table, k, compare_long_int);
	//print_table(hash_table, "-i");
	free(k);
	free(hash_table);
}

int find_list_test(node* n, key* k, CompareFunc compare){
  for(; n != NULL; n = n->next	){
   if((compare(n->record, k)) == 0){
      return 1;
    }
  }
  return -1;
}

void insert_on_same_key(){
	node** hash_table;
	double* key_value;
	key** k;
	key* k1;
	int i;

	hash_table = (node**)malloc(sizeof(node*)*5);
	k = (key**)malloc(sizeof(key*));
	for(i = 0; i < 5; i++){
		k1 = new_key(0, "", 0, 0);
		hash_table[i] = new_node(k1);
	}

	key_value = (double*)malloc(sizeof(double)*5);
	key_value[0] = 225.354;
	key_value[1] = 654.2315;
	key_value[2] = 124578.21;
	key_value[3] = 87946.354;
	key_value[4] = 32198.65445;

	for(i = 0; i < 5; i++){
		//k[i] = (key*)malloc(sizeof(key));
		k[i] = new_key(0, "", 0, key_value[i]);
		insert_hash_table(hash_table, k[i], compare_double);
	}
	for(i = 0; i < 5; i++){
		assert(find_list_test(hash_table[0], k[i], compare_double) == 1);
	}

	for(i = 0; i < 5; i++){
		free(k[i]);
		free(hash_table[i]);
	}
	free(key_value);
	free(k1);
	free(hash_table);
}

void delete_first(){
	node** hash_table;
	char** string_value;
	key** k;
	key* k1;
	int i;

	hash_table = (node**)malloc(sizeof(node*)*5);
	string_value = (char**)malloc(sizeof(char*)*20);
	k = (key**)malloc(sizeof(key*)*5);

	for(i = 0; i < 5; i++){
		k1 = new_key(0, "", 0, 0);
		hash_table[i] = new_node(k1);
	}

	string_value[0] = "Overflow";
	string_value[1] = "TeSt";
	string_value[2] = "TURING";
	string_value[3] = "AckerMann";
	string_value[4] = "function";
	for(i = 0; i < 5; i++){
		k[i] = new_key(i, string_value[i], 0, 0); 
		insert_hash_table(hash_table, k[i], compare_string);
	}
	delete(hash_table, k[2], compare_string);

	
	assert(strcmp(hash_table[2]->record->word , "") == 0); 

}
void delete_last(){
	node** hash_table;
	long int* n_value;
	key** k;
	key* k1;
	int i;

	hash_table = (node**)malloc(sizeof(node*)*5);
	n_value = (long int*)malloc(sizeof(long int)*10);
	k = (key**)malloc(sizeof(key*)*5);

	for(i = 0; i < 5; i++){
		k1 = new_key(0, "", 0, 0);
		hash_table[i] = new_node(k1);
	}

	n_value[0] = 21; 
	n_value[1] = 78;
	n_value[2] = 456;
	n_value[3] = 3;
	n_value[4] = 15;

	for(i = 0; i < 5; i++){
		k[i] = new_key(0, "", n_value[i], 0);
		insert_hash_table(hash_table, k[i], compare_long_int);
	}
	
	delete(hash_table, k[4], compare_long_int);
	assert(hash_table[4]->record->linum == 0);
}

void delete_random_one(){
	node** hash_table;
	long int* n_value;
	key** k;
	key* k1;
	int i;

	hash_table = (node**)malloc(sizeof(node*)*5);
	n_value = (long int*)malloc(sizeof(long int)*10);
	k = (key**)malloc(sizeof(key*)*5);

	for(i = 0; i < 5; i++){
		k1 = new_key(0, "", 0, 0);
		hash_table[i] = new_node(k1);
	}

	n_value[0] = 21; 
	n_value[1] = 78;
	n_value[2] = 456;
	n_value[3] = 3;
	n_value[4] = 15;

	for(i = 0; i < 5; i++){
		k[i] = new_key(0, "", n_value[i], 0);
		insert_hash_table(hash_table, k[i], compare_long_int);
	}

	delete(hash_table, k[2], compare_long_int);
	assert(hash_table[2]->record->linum == 0);	
}

void unit_test(){
	insert_equal_element();
	insert_on_same_key();
	delete_first();
	delete_last();
	delete_random_one();
}