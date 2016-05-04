#include "binary_search_tree.h"
#include "unit_test.h"

int compare_long_int(node* root, node* n){
  long int el1 = root->record->linum;
  long int el2 = n->record->linum;

  if(el1 < el2) {
    return -1;
  }
  if (el1 == el2) {
    return 0;
  }
  return 1; 
}

int compare_string(node* root, node* n){
	return strcmp(root->record->word, n->record->word);
}

int compare_double(node* root, node* n){
	double el1 = root->record->fnum;
	double el2 = n->record->fnum;

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

key* new_key(int id, char* w, long int i, double f){
	key* k = (key*) malloc(sizeof(key));
	k->linum = i;
	k->fnum = f;
	k->word = w;
	k->id = id;
	return k;
}

node* new_node(key* k){
	node* n = (node*) malloc(sizeof(node));
	n->record = k;
	n->left = NULL;
	n->right = NULL;
	return n;
}

bin_tree* new_bin_tree (){
	bin_tree* bt = (bin_tree*)malloc (sizeof(bin_tree));
	bt->root = NULL;
	return bt;
}

key* read_record(FILE* fp){
	int i, id;
	long int linum;
	double fnum;
	char* word;
	word = (char*)malloc(sizeof(char)*15);
	char c;
	
	if(fscanf(fp, "%d,", &id) <= 0)
		perror("No id read\n");

	c = fgetc(fp);
	for(i = 0; c != ','; i++){
		word[i] = c;
		c = fgetc(fp);
	}
	if(fscanf(fp, "%li,%lf", &linum, &fnum) <= 0)
		perror("No number read\n");
	return new_key(id, word, linum, fnum);

}

node* binary_search_tree_insert(node* root, node* n, CompareFunc compare ){
	if(root == NULL){
		root = n;
		return root;
	}
	
	if(compare(root, n) == 0)
		return root;

	if(compare(root, n) > 0){
		root->left = binary_search_tree_insert(root->left, n, compare);
	}else
		root->right = binary_search_tree_insert(root->right, n, compare);

	return root;
}

void fill(bin_tree* tree, char* argv){
	int i;
	key* k;
	node* n;
	FILE* fp;

	if((fp = fopen("records.csv", "r")) == NULL)
		perror("File not found\n");
	
	for(i = 0; i < N_RECORDS; i++){
		k = read_record(fp);
		n = new_node(k);
		if(strcmp(argv, "-s") == 0){
			tree->root = binary_search_tree_insert(tree->root, n, compare_string);
			assert(is_bst(tree->root, compare_string) > 0);
		}else if(strcmp(argv, "-i") == 0){
			tree->root = binary_search_tree_insert(tree->root, n, compare_long_int);
			assert(is_bst(tree->root, compare_long_int) > 0);
		}else if(strcmp(argv, "-f") == 0)	{		
			tree->root = binary_search_tree_insert(tree->root, n, compare_double);
			assert(is_bst(tree->root, compare_double) > 0);
		}else{
			printf("ERROR: incorrect options\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(fp);
	free(k);
	free(n);
}


int random_generator(){
	int rnd;
	rnd = rand()%N_RECORDS;
	return rnd;
}

key* search_id(int rnd){
	FILE* fp;
	key* k = NULL;
	int i;

	fp = fopen("records.csv", "r");

	for(i = 0; i < rnd; i++){
		k = read_record(fp);
	}
	fclose(fp);
	return k;
}

int random_search(node* root, node* n, CompareFunc compare){
	if(root == NULL)
		return -1;
	if(compare(root, n) == 0)
		return 1;
	if(compare(root, n) > 0)
		return random_search(root->left, n, compare);
	else
		return random_search(root->right, n, compare);
}

void search_1ml_records(node* root, CompareFunc compare){
	int i, rnd;
	node* n;
	key* k;
	for(i = 0; i < N_OPER; i++){
		rnd = random_generator();
		k = search_id(rnd);
		n = new_node(k);
		assert(random_search(root, n, compare) == 1);
		free(k);
		free(n);
	}
}

void search(bin_tree* tree, char* argv){
		if(strcmp(argv, "-s") == 0){
			search_1ml_records(tree->root, compare_string);
		}else if(strcmp(argv, "-i") == 0){
			search_1ml_records(tree->root, compare_long_int);
		}else if(strcmp(argv, "-f") == 0)	{		
			search_1ml_records(tree->root, compare_double);
		}else{
			printf("ERROR: incorrect options\n");
			exit(EXIT_FAILURE);
		} 
}


node* min_node_value(node* n){
	node* tmp = n;

	while(tmp->left != NULL){
		tmp = tmp->left;
	}
	return tmp;

}

node* random_delete(node* root, node* n, CompareFunc compare){
	if(root == NULL)
		return root;
	if(compare(root, n) > 0)
		root->left = random_delete(root->left, n, compare);
	else if(compare(root, n) < 0)
		root->right = random_delete(root->right, n, compare);
	else{
		if(root->right == NULL){
			node* tmp = root->left;
			free(root);
			return tmp;			
		}else if(root->left == NULL){
			node* tmp = root->right;
			free(root);
			return tmp;
		}else{
			node* tmp = min_node_value(root->right);

			root->record = tmp->record;

			root->right = random_delete(root->right, tmp, compare);
		}
	}
	return root;

}

void delete_1ml_records(node* root, CompareFunc compare){
	int i, rnd;
	node* n;
	key* k;
	for(i = 0; i < N_OPER; i++){
		rnd = random_generator();
		k = search_id(rnd);
		n = new_node(k);
		random_delete(root, n, compare);
		free(k);
		free(n);
	}
}

void delete(bin_tree* tree, char* argv){
	if(strcmp(argv, "-s") == 0){
			delete_1ml_records(tree->root, compare_string);
		}else if(strcmp(argv, "-i") == 0){
			delete_1ml_records(tree->root, compare_long_int);
		}else if(strcmp(argv, "-f") == 0)	{		
			delete_1ml_records(tree->root, compare_double);
		}else{
			printf("ERROR: incorrect options\n");
			exit(EXIT_FAILURE);
		}
}



