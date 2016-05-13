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

void print_table(node** n, char* argv, int num){
	int i;
	if(N_RECORDS < 500){
		for(i = 0; i < num; i++){
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
		k = new_key(0, "", 0, 0);
		hash_table[i] = new_node(k);
	}
	return hash_table;
}

node* insert_list(node* n, key* k){
  node* new_node = (node*)malloc(sizeof(node));
  new_node->record = k;
  new_node->next = n;
  new_node->prev = NULL;
  if(n != NULL)
    n->prev = new_node;
  return new_node;
}



node* find_list(node* n, key* k, CompareFunc compare){
  for(; n != NULL; n = n->next	){
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
  hash_value = hash(k->id);
  if(find_list(hash_table[hash_value], k, compare) == NULL){
   	hash_table[hash_value] = insert_list(hash_table[hash_value], k);
  }
}

key* read_record(FILE* fp){
  int i; 
  int id = 0;
  long int linum = 0;
  double fnum = 0;
  char* word = NULL;
  word = (char*)malloc(sizeof(char)*20);

  char c = '\0';
  if(fscanf(fp, "%d,", &id) <= 0)
    perror("No id read\n");
  c = fgetc(fp);
  for(i = 0; i <20; i++){
  	word[i] = '\0';
  	if(c != ','){
    	word[i] = c;
    	c = fgetc(fp);
  	} 
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

int random_generator(){
  int rnd;
  rnd = rand()%20;
  return rnd;
}

void search_id(key** k){ //pre: N_OPER < N_RECORDS
  FILE* fpl;
  key* tmp = NULL;
  int i, j, rnd;

  fpl = fopen("records.csv", "r");

  for(j = 0; j < N_OPER; j++){
  	rnd = random_generator();
  	for(i = 0; i < rnd; i++){
    	tmp = read_record(fpl);
    	if(tmp->id >= N_RECORDS){
    		fclose(fpl);
    		fpl = fopen("records.csv", "r");
    		tmp = read_record(fpl);
    	}
  	}
  	k[j] = tmp;	
  }
  fclose(fpl);
}

void search(node** hash_table, key* k, CompareFunc compare){
	int hash_val;
	hash_val = hash(k->id);
	assert(find_list(hash_table[hash_val], k, compare) != NULL);
}

double search_key(node** hash_table, char* argv){
  int i;
  key** k;
  clock_t start, end; 
  double t = 0;

  k = (key**)malloc(sizeof(key*)*N_OPER);

  //genero chiavi random e le salvo nell'array k
  start = clock();
  search_id(k);
  end = clock();
  t = (double)(end - start)/CLOCKS_PER_SEC;
  printf("HO GENERATO %d chiavi casuali in %lfsec\n",N_OPER , t);
  t = 0;

  for(i = 0; i < N_OPER; i++){
    
    if(strcmp(argv, "-s") == 0){
      start = clock();
      search(hash_table, k[i], compare_string); 
      end = clock();
      t = t + (double)(end - start)/CLOCKS_PER_SEC;
    }else if(strcmp(argv, "-i") == 0){
      start = clock();
      search(hash_table, k[i], compare_long_int); 
      end = clock();
      t = t + (double)(end - start)/CLOCKS_PER_SEC;
    }else if(strcmp(argv, "-f") == 0){
      start = clock();
      search(hash_table, k[i], compare_double); 
      end = clock();
      t = t + (double)(end - start)/CLOCKS_PER_SEC;
    }else{
      printf("ERROR: incorrect options\n");
      exit(EXIT_FAILURE);
    }
  }
  free(k);
  return t;
}

node* delete_node(node* n, node* tmp, CompareFunc compare){
   if(tmp->prev != NULL) 
      tmp->prev->next = tmp->next;  
    else  
      n = tmp->next;  
    if(tmp->next != NULL) 
      tmp->next->prev = tmp->prev; 
    free(tmp);
    return n;
}

void delete(node** hash_table, key* k, CompareFunc compare){
  int hash_val;
  hash_val = hash(k->id);
  node* tmp;
  if((tmp = find_list(hash_table[hash_val], k, compare)) != NULL){
  	hash_table[hash_val] = delete_node(hash_table[hash_val], tmp, compare);
  }
}

double delete_key(node** hash_table, char* argv){
  int i;
  key** k;
  clock_t start, end; 
  double t = 0;

  k = (key**)malloc(sizeof(key*)*N_OPER);

  //genero chiavi random e le salvo nell'array k
  start = clock();
  search_id(k);
  end = clock();
  t = (double)(end - start)/CLOCKS_PER_SEC;
  printf("\nHO GENERATO %d chiavi casuali in %lfsec\n",N_OPER , t);
  t = 0;

  for(i = 0; i < N_OPER; i++){
    
    if(strcmp(argv, "-s") == 0){
      start = clock();
      delete(hash_table, k[i], compare_string);
      end = clock();
      t = t + (double)(end - start)/CLOCKS_PER_SEC;
    }else if(strcmp(argv, "-i") == 0){
       start = clock();
      delete(hash_table, k[i], compare_long_int);
      end = clock();
      t = t + (double)(end - start)/CLOCKS_PER_SEC;
    }else if(strcmp(argv, "-f") == 0){
       start = clock();
      delete(hash_table, k[i], compare_double);
      end = clock();
      t = t + (double)(end - start)/CLOCKS_PER_SEC;
    }else{
      printf("ERROR: incorrect options\n");
      exit(EXIT_FAILURE);
    }
  }
  free(k);
  return t;

}

