#include "binary_search_tree.h"
#include "unit_test.h"

// inserimento test: vuoto, crescenti, tutti uguali, normali
// ricerca test: normale, elemento min/max, radice
// cancellazione test: normale, elemento min/max, radice, 3 casi

/*
 * Testa se root è la radice di un albero binario di ricerca
 * Restituise 1 in caso di succeso e -1 in caso di insuccesso
 */
int is_bst(node* root, CompareFunc compare){
	if(root == NULL)
		return -1;
	if(root->left == NULL || root->right == NULL)
		return 1;
	if(compare(root->left, root) <= 0 && compare(root->right, root) >= 0){
		if(is_bst(root->left, compare) == 1 && is_bst(root->right, compare) == 1)
			return 1;
		else
			return -1;
	}else
		return -1;
}

/*
 * Testa l'inserimento di un nodo nullo in radice 
 */
void test_empty_insert(){
	bin_tree* tree;
	key* k = NULL;
	node* n;
	tree = new_bin_tree();
	n = new_node(k);

	tree->root = binary_search_tree_insert(tree->root, n, compare_double);
	assert(1);
}

/*
 * Testa l'inserimento di 5 long int random 
 */
void test_full_insert(){
	bin_tree* tree;
	node** array_node;
	key** array_key;
	int i;

	tree = new_bin_tree();
	array_node = (node**)malloc(sizeof(node*)*20);
	array_key = (key**)malloc(sizeof(key*)*20);

	for(i = 0; i < 5; i++){
		array_key[i] = new_key(0, NULL, (long int)rand()%100, 0);
	}

	for(i = 0; i < 5; i++){
		array_node[i] = new_node(array_key[i]);
	}

	for(i = 0; i < 5; i++){
		tree->root = binary_search_tree_insert(tree->root, array_node[i], compare_long_int);
	}

	assert(is_bst(tree->root, compare_long_int) > 0);

	delete_min(tree->root);
	
	free(array_key);
	free(array_node);
	free(tree);
}

void test_min_insert(){
	int i;
	bin_tree* tree_string;
	key** k;
	node** n;
	node* node_min;
	key* key_min;

	tree_string = new_bin_tree();
	n = (node**)malloc(sizeof(node*)*50);
	k = (key**)malloc(sizeof(key*)*50);
	k[0] = new_key(0, "CIAO", 0, 0);
	k[1] = new_key(0, "STACK", 0, 0);
	k[2] = new_key(0, "push", 0, 0);
	k[3] = new_key(0, "PC=PC+1", 0, 0);
	k[4] = new_key(0, "Asus", 0, 0);

	for(i = 0; i < 5; i++){
		n[i] = new_node(k[i]);
		tree_string->root = binary_search_tree_insert(tree_string->root, n[i], compare_string);
	}

	key_min = new_key(0, "AAAAA", 0, 0);
	node_min = new_node(key_min);
	tree_string->root = binary_search_tree_insert(tree_string->root, node_min, compare_string);
	assert(compare_string(min_node_value(tree_string->root), node_min) == 0);

	for(int i = 0; i < 5; i++){
		free(k[i]);
		free(n[i]);
	}
	free(k);
	free(key_min);
	free(node_min);
	free(n);
	free(tree_string);

}

void test_search_min_and_root(){
	int i;
	bin_tree* tree_float;
	key** k;
	node** n;

	tree_float = new_bin_tree();
	n = (node**)malloc(sizeof(node*)*20);
	k = (key**)malloc(sizeof(key*)*20);
	k[0] = new_key(0, NULL, 0, 2.65489);
	k[1] = new_key(0, NULL, 0, 2.6241);
	k[2] = new_key(0, NULL, 0, 1000.1);
	k[3] = new_key(0, NULL, 0, 1254.3569);
	k[4] = new_key(0, NULL, 0, -254.365417);

	for(i = 0; i < 5; i++){
		n[i] = new_node(k[i]);
		tree_float->root = binary_search_tree_insert(tree_float->root, n[i], compare_double);
	}

	assert(random_search(tree_float->root, n[4], compare_double) > 0);
	assert(random_search(tree_float->root, n[0], compare_double) > 0);

	for(int i = 0; i < 5; i++){
		free(k[i]);
		free(n[i]);
	}
	free(k);
	free(n);
	free(tree_float);

}

/*cancellazione minimo*/
void delete_min(node* root){
	node* min = min_node_value(root);
	random_delete(root, min, compare_long_int);
	min = min_node_value(root);
	assert(1);
}

int tree_height(node* root){
	int hl = 0;
	int hr = 0;
	if(root->left == NULL && root->right == NULL)
		return 0;
	else{
		if(root->left != NULL)
			hl = tree_height(root->left);
		if(root->right != NULL)
			hr = tree_height(root->right);
		if(hl > hr)
			return 1 + hl;
		else
			return 1 + hr;
	}
}

void insert_degenerate(){
	int i;
	bin_tree* tree_deg;
	key** k;
	node** n;

	tree_deg = new_bin_tree();
	n = (node**)malloc(sizeof(node*)*20);
	k = (key**)malloc(sizeof(key*)*20);
	k[0] = new_key(0, NULL, 146, 0);
	k[1] = new_key(0, NULL, 256, 0);
	k[2] = new_key(0, NULL, 333, 0);
	k[3] = new_key(0, NULL, 405, 0);
	k[4] = new_key(0, NULL, 587, 0);

  for(i = 0; i < 5; i++){
		n[i] = new_node(k[i]);
		tree_deg->root = binary_search_tree_insert(tree_deg->root, n[i], compare_long_int);
	}
	assert(tree_height(tree_deg->root) == 4);

	for(i = 0; i < 5; i++){
		free(k[i]);
		free(n[i]);
	}
	free(k);
	free(n);
	free(tree_deg);
}


/*
 * Funzione che effettua gli unit test
 */

void unit_test(){
	test_empty_insert();
	test_full_insert();
	test_min_insert();
	test_search_min_and_root();
	insert_degenerate();
}