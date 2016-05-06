#ifndef __HASH_TABLE_H_KEIXJ4PDU3__
#define __HASH_TABLE_H_KEIXJ4PDU3__

#define N_RECORDS 200
#define HSIZE 50/* dimensione della tabella hash */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

typedef struct key_frame{
	int id;
	char* word;					
	long int linum;			
 	double fnum;					
 }key;

/*  struttura che rappresenta un nodo della lista		*/
typedef struct lnode { 		
 	key* record;					
	struct lnode *next;		
 	struct lnode *prev; 	
}node;

typedef int (*CompareFunc)(key*, key*);

void print_table(node** hash_table, char* argv);
void print_list(node* n, char* argv);

void print_help();

int compare_long_int(key* k1, key* k2);
int compare_string(key* k1, key* k2);
int compare_double(key* k1, key* k2);
node* insert_list(node* n, key* k);
node* find_list(node* n, key* k, CompareFunc compare);
int hash(int id);
void insert_hash_table(node** hash_table, key* k, CompareFunc compare);
key* new_key(int id, char* w, long int i, double f);
node* new_node(key* k);
key* read_record(FILE* fp);
void insert_file_records(node** hash_table, char* argv);
node** make_table();
void free_mem();


#endif