#ifndef __BINARY_SEARCH_TREE_H_KEIXJ4PDU3__
#define __BINARY_SEARCH_TREE_H_KEIXJ4PDU3__

#define N_RECORDS 20000
#define N_OPER 300

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

typedef int (*CompareFunc)(node*, node*);

/*
 * Funzione di stampa di --help
 */

void print_help();

/*
 * Crea una nuova chiave
 */
key* new_key(int id, char* w, long int i, double f);

/*
 * Crea un nuovo nodo
 */
node* new_node(key* k);

/*
 * Crea un nuovo albero
 */
bin_tree* new_bin_tree();

/*
 * Legge un record, crea una chiave con i valori letti e restituisce un puntatore a key
 */
key* read_record(FILE* fp);

/*
 * Funzioni di confronto
 */
int compare_long_int(node* root, node* n);
int compare_string(node* root, node* n);
int compare_double(node* root, node* n);

/*
 * Funzioni di inserimento a seconda del tipo scelto
 */
node* binary_search_tree_insert(node* root, node* n, CompareFunc compare);
void fill(bin_tree* tree, char* argv);

/*
 * Genera un intero casuale compreso tra 1 e N_OPER
 */
int random_generator();

/*
 * Dato un intero compreso tra 1 e N_OPER restiusce il record corrispondente 
 * letto da "records.csv"
 */
key* search_id(int rnd);

/*
 * Metodi di ricerca in base al tipo scelto
 */
int random_search(node* root, node* n, CompareFunc compare);
void search_1ml_records(node* root, CompareFunc compare);
void search(bin_tree* tree, char* argv);

/*
 * Data la radice restituisce il nodo con valore scelto minimo nell'albero
 */
node* min_node_value(node* n);

/*
 *	Metodi di cancellazione in base al tipo scelto
 */

void delete_1ml_records(node* root, CompareFunc compare);
node* random_delete(node* root, node* n, CompareFunc compare);
void delete(bin_tree* tree, char* argv);

void unit_test();

#endif
