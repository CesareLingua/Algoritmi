#ifndef __BINARY_SEARCH_TREE_H_KEIXJ4PDU3__
#define __BINARY_SEARCH_TREE_H_KEIXJ4PDU3__

#define N_RECORDS 200
#define N_OPER 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

typedef struct keyFrame{
	long int linum;
	double fnum;
	char* word;
	int id;
}key;

typedef struct tnode{
	key* record;
	struct tnode* left;
	struct tnode* right;
}node;

typedef struct bin_tree_frame {
	node* root;
}bin_tree;

/*
 * Crea una nuova chiave
 */
key* new_key(int id, char* w, long int i, double f);

/*
 * Crea un nuovo nodo
 */
node* new_node(key* k);

/*
 * Legge un record, crea una chiave con i valori letti e restituisce un puntatore a key
 */
key* read_record(FILE* fp);

typedef int (*CompareFunc)(node*, node*);

/*
 * Inserisce in ordine il nodo n in base al tipo scelto
 */
node* binary_search_tree_insert(node* root, node* n, CompareFunc compare);

/*
 * Crea un nuovo albero
 */
bin_tree* new_bin_tree();

/*
 * Funzioni di confronto
 */
int compare_long_int(node* root, node* n);
int compare_string(node* root, node* n);
int compare_double(node* root, node* n);

void fill(bin_tree* tree, char* argv);

int random_generator();
key* search_id(int rnd);
int random_search(node* root, node* n, CompareFunc compare);
void search_1ml_records(node* root, CompareFunc compare);
void print_help();
void search(bin_tree* tree, char* argv);
node* min_node_value(node* n);
void delete_1ml_records(node* root, CompareFunc compare);
node* random_delete(node* root, node* n, CompareFunc compare);
void delete(bin_tree* tree, char* argv);

void unit_test();

#endif
