#include "binary_search_tree.h"
#include "unit_test.h"

// inserimento test: vuoto, crescenti, tutti uguali, normali
// ricerca test: normale, elemento min/max, radice
// cancellazione test: normale, elemento min/max, radice, 3 casi

/*int is_bin_tree(node* root, CompareFunc compare){
	int t;
	if(root == NULL){
		t = -1;
		return t;
	}
	if(compare(root->left, root) <= 0){
		t = is_bin_tree(root->left, compare);
		return 1;
	}
	if(compare(root->right, root) >= 0){
		t = is_bin_tree(root->right, compare);
		return 1;
	}


}*/


/*void test_empty_insert(){
	bin_tree* tree;
	key* k = NULL;
	node* n;
	tree = new_bin_tree();
	n = new_node(k);

	tree->root = binary_search_tree_insert(tree->root, n, compare_double);
	assert(1);
}*/

void test_full_insert(){
	bin_tree* tree;
	node** array_node;
	key** array_key;
	int i;
	
	tree = new_bin_tree();

	array_node = (node**)malloc(sizeof(node*));
	array_key = (key**)malloc(sizeof(key*));

	for(i = 0; i < 5; i++){
		array_key[i] = new_key(0, NULL, rand()%100, 0);
	}
	
	for(i = 0; i < 5; i++){
		array_node[i] = new_node(array_key[i]);
	}

	for(i = 0; i < 5; i++){
		tree->root = binary_search_tree_insert(tree->root, array_node[i], compare_long_int);
	}

	//assert(is_bin_tree(tree->root, compare_long_int) > 0);

	delete_min(tree->root);
	delete_root(tree->root);	
	
	
	/*free(tree);
	for(i = 0; i < 5; i++){
		free(array_node[i]);
		free(array_key[i]);
	}*/	
}

/*cancellazione minimo*/
void delete_min(node* root){
	node* min = min_node_value(root);
	printf("Minimo prima della cancellazione: %li\n", min->record->linum);
	random_delete(root, min, compare_long_int);
	min = min_node_value(root);
	printf("Minimo dopo la cancellazione: %li\n", min->record->linum);
	assert(1);
}

/*cancellazione radice*/
void delete_root(node* root){
	printf("La radice e': %li\n",root->record->linum);
	root = random_delete(root, root, compare_long_int);
	printf("La nuova radice e': %li\n",root->record->linum);
}


void unit_test(){
	//test_empty_insert();
	test_full_insert();
}