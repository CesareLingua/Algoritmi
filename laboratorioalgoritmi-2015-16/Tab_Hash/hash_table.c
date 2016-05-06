#include "hash_table.h"
//#include "unit_test.h"

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

int compare_double(key* k1, key* k2){
	double el1 = k1->fnum;
	double el2 = k2->fnum;

	if(el1<el2) 
	  return -1;
	if (el1 == el2)
	    return 0;

	return 1;
}

void print_help(){
	printf("\nUSAGE: $./stress_bin_tree [options]\n");
	printf("		-s           Fill the tree by String\n");	
	printf("		-i           Fill the tree by long int\n");
	printf("		-f           Fill the tree by float\n");
	printf("\n");	
	exit(EXIT_SUCCESS);
}

node* insert_list(node* n, key* k){
  node* new_node = (node*)malloc(sizeof(node));
  new_node->record = k;
  new_node->next = n;
  new_node->prev = NULL;
  if(n != NULL)       /* lista non vuota */
    n->prev = new_node;
  return new_node;
}

node* find_list(node* n, key* k, CompareFunc compare){
  for(; n != NULL; n = n->next){
   if((compare(n->record, k)) == 0){
      return n;
    }
  }
  return NULL;
}

int hash(int id){
  int hash_val;
  hash_val = id%HSIZE;
  return hash_val;
}

void insert_hash_table(node** hash_table, key* k, CompareFunc compare){
  int hash_value;
  node* n;
  hash_value = hash(k->id);
  if((n = find_list(hash_table[hash_value], k, compare)) == NULL){
   	hash_table[hash_value] = insert_list(hash_table[hash_value], k);
  }
}

key* new_key(int id, char* w, long int i, double f){
  key* k = (key*)malloc(sizeof(key));
  k->linum = i;
  k->fnum = f;
  k->word = w;
  k->id = id;
  return k;
}

node* new_node(key* k){
	node* n = (node*) malloc(sizeof(node));
	n->record = k;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

node** make_table(){
	key* k;
	node** hash_table;
	int i;
	hash_table = (node**)malloc(sizeof(node*)*HSIZE);
	for(i = 0; i < HSIZE; i++){
		k = new_key(0, "_", 0, 0);
		hash_table[i] = new_node(k);
	}
	return hash_table;
}

void print_table(node** n, char* argv){
	int i;
	if(N_RECORDS < 500){
		for(i = 0; i < HSIZE; i++){
			if(n[i]!= NULL){
				printf("-----------------------------------------------\n");
				print_list(n[i], argv);
			}
		}
	}else
		printf("NON POSSO STAMPARE LA TABELLA DI HASH, TROPPI ELEMENTI\n");
}

void print_list(node* n,char* argv){
	if(strcmp(argv, "-s") == 0){
   	for(;n != NULL; n = n->next){
			printf("	%s, ", n->record->word);
		}
		printf("\n");
  }else if(strcmp(argv, "-i") == 0){
  	for(;n != NULL; n = n->next){
			printf("	%li, ", n->record->linum);
		}
		printf("\n");
  }else if(strcmp(argv, "-f") == 0){
   	for(;n != NULL; n = n->next){
			printf("	%lf, ", n->record->fnum);
		}
		printf("\n");
  }else{
  	exit(EXIT_FAILURE);
  }
}

key* read_record(FILE* fp){
  int i, id;
  long int linum;
  double fnum;
  char* word;
  word = (char*)malloc(sizeof(char)*20);
  char c;
  if(fscanf(fp, "%d,", &id) <= 0)
    perror("Not id read\n");
  c = fgetc(fp);
  for(i = 0; c != ','; i++){
    word[i] = c;
    c = fgetc(fp);
  }
  if(fscanf(fp, "%li,%lf", &linum, &fnum) <= 0)
    perror("No number read\n");

	return new_key(id, word, linum, fnum);
}

void insert_file_records(node** hash_table, char* argv){
  int i;
  FILE* fp;
  key* k;

  fp = fopen("records.csv", "r");
  for(i = 0; i < N_RECORDS; i++){
    k = read_record(fp);
    if(strcmp(argv, "-s") == 0){
   		insert_hash_table(hash_table, k, compare_string); 
    }else if(strcmp(argv, "-i") == 0){
   		insert_hash_table(hash_table, k, compare_long_int); 
    }else if(strcmp(argv, "-f") == 0){
   		insert_hash_table(hash_table, k, compare_double); 
    }else{
    	printf("ERROR: incorrect options\n");
			exit(EXIT_FAILURE);
    }
  }
  fclose(fp);
}