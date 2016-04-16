//#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct key{
	long int a;
	double b;
	char* c;
	int id;
}key;

typedef struct node{
	key* data;
	struct node* left;
	struct node* right;
	struct node* parent;
}node;

int main(){
	node* root;
	root = (node*)malloc(sizeof(node));
	root->data = (key*)malloc(sizeof(key));

	(root->data)->a = 2;

	printf("%li\n", (root->data)->a);
	return 0;
}