#ifndef __BINARY_SEARCH_TREE_H_KEIXJ4PDU3__
#define __BINARY_SEARCH_TREE_H_KEIXJ4PDU3__


typedef struct key{
	long int a;
	double b;
	char* c;
	int id;
};

typedef struct node_struct{
	key chiave;
	struct node_struct* left;
	struct node_struct* right;
	struct node_struct* parent;
}node;

#endif