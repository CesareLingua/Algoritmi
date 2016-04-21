#include "binary_search_tree.h"

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

key* new_key(int id, char* w, long int i, double f){
	key* k = (key*) malloc(sizeof(node));
	k->linum = i;
	k->fnum = f;
	k->word = w;
	k->id = id;
	return k;
}

node* new_node(key* k, node* l, node* r){
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
	word = (char*)malloc(sizeof(char)*10);
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

node* binary_search_tree_insert(node* root, node* n, CompareFunc compare ){
	if(root == NULL){
		root = n;
		return root;
	}
	
	if(compare(root, n) == 0)
		return root;

	if(compare(root, n) < 0){
		root->left = binary_search_tree_insert(root->left, n, compare);
	}else
		root->right = binary_search_tree_insert(root->right, n, compare);

	return root;
}

void fill_tree(bin_tree* tree, int ord_type){
	int i;
	key* k;
	node* n;
	FILE* fp;

	if((fp = fopen("records.csv", "r")) == NULL)
		perror("File not found\n");
	

	for(i = 0; i < N_RECORDS; i++){
		k = read_record(fp);
		n = new_node(k, NULL, NULL);

		switch(ord_type){
			case 1:
				tree->root = binary_search_tree_insert(tree->root, n, compare_string);

			case 2:
				tree->root = binary_search_tree_insert(tree->root, n, compare_long_int);

			case 3:
				tree->root = binary_search_tree_insert(tree->root, n, compare_double);
		}
	}
	fclose(fp);
	free(k);
	free(n);
}

