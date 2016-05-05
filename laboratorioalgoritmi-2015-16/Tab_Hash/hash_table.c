#include "hash_table.h"
#include "unit_test.h"

int compare_long_int(key* k1, key* k2){
  long int el1 = k1->linum;
  long int el2 = k2->linum;

  if(el1 < el2) {
    return -1;
  }
  if (el1 == el2) {
    return 0;
  }
  return 1; 
}

int compare_string(key* k1, key* k2){
	return strcmp(k1->word, k2->word);
}

int compare_float(key* k1, key* k2){
	float el1 = k1->fnum;
	float el2 = k2->fnum;

	if(el1<el2) 
	  return -1;
	if (el1 == el2)
	    return 0;

	return 1;
}

/*void initTable(node* hash_table[]){
	int i;
	for(i = 0; i < HSIZE; i++){ 
		hash_table[i] = NULL;
	} 
}*/

key* new_key(int id, char* w, long int i, float f){
	key* k = (key*)malloc(sizeof(node));
	k->linum = i;
	k->fnum = f;
	k->word = w;
	k->id = id;
	return k;
}

int hash(int id){
	int hash_val;
	hash_val = (id*999983)%600071;
	return hash_val;
}

void insert_file_records(node** hash_table){
	int i;
	FILE* fp;
	fp = fopen("records.csv", "r");

	for(i = 0; i < N_RECORDS; i++){
		key* k;
		k = read_record(fp);
		insert_hash_table(hash_table, k, compare_long_int);	
	}
	fclose(fp);
}

key* read_record(FILE* fp){
	int i, id;
	long int linum;
	float fnum;
	char* word;
	word = (char*)malloc(sizeof(char)*13);
	char c;
	
	if(fscanf(fp, "%d,", &id) <= 0)
		perror("Not id read\n");

	c = fgetc(fp);
	for(i = 0; c != ','; i++){
		word[i] = c;
		c = fgetc(fp);
	}
	if(fscanf(fp, "%li,%f", &linum, &fnum) <= 0)
		perror("No number read\n");
	return new_key(id, word, linum, fnum);

}

node* find_list(node* n, key* k, CompareFunc compare){
	while(n != NULL){
		if(compare(n->record, k) == 0)
			return n;
		n = n->next;
	}
	return NULL;
}

node* insert_list(node* n, key* k){
	node* new_node = (node*)malloc(sizeof(node));
	new_node->record = k;
	new_node->next = n;
	new_node->prev = NULL;
	if(n != NULL)				/* lista non vuota */
		n->prev = new_node;
	return new_node;
}

void insert_hash_table(node** hash_table, key* k, CompareFunc compare){
	int hash_value;
	node* n;
	hash_value = hash(k->id);
	if((n = find_list(hash_table[hash_value], k, compare)) == NULL){
		hash_table[hash_value] = insert_list(hash_table[hash_value], k);
	}
}

