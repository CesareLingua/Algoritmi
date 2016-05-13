#ifndef __HASH_TABLE_H_KEIXJ4PDU3__
#define __HASH_TABLE_H_KEIXJ4PDU3__

#define N_RECORDS 20000000
#define HSIZE 5000000
#define N_OPER 1000000

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

void print_table(node** hash_table, char* argv, int num);
void print_list(node* n, char* argv);

void print_help();

int compare_long_int(key* k1, key* k2);
int compare_string(key* k1, key* k2);
int compare_double(key* k1, key* k2);
key* new_key(int id, char* w, long int i, double f);
node* new_node(key* k);
node** make_table();
int hash(int id);

key* read_record(FILE* fp);
node* insert_list(node* n, key* k);
node* find_list(node* n, key* k, CompareFunc compare);
void insert_hash_table(node** hash_table, key* k, CompareFunc compare);
void insert_file_records(node** hash_table, char* argv);

int random_generator();
void search_id(key** k);
double search_key(node** hash_table, char* argv);
void search(node** hash_table, key* k, CompareFunc compare);

double delete_key(node** hash_table, char* argv);
void delete(node** n, key* k, CompareFunc compare);
node* delete_node(node* n, node* tmp, CompareFunc compare);
void unit_test();

#endif