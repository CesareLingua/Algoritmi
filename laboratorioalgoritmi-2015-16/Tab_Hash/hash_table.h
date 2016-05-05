#ifndef __HASH_TABLE_H_KEIXJ4PDU3__
#define __HASH_TABLE_H_KEIXJ4PDU3__

#define N_RECORDS 100
#define HSIZE 5000 /* dimensione  della tabella hash */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* contiene prototipo di isspace() */

typedef struct key_frame{
	int id;
	char* word;						/* dato string del record */
	long int linum;				/* dato intero del record */
 	double fnum;					/* dato double del record */
}key;

/*  struttura che rappresenta un nodo della lista		*/
typedef struct lnode { 		
 	key* record;					/* puntatore a dato stringa del record */
	struct lnode *next;		/* nodo successivo */
 	struct lnode *prev; 	/* nodo precedente */
}node;

typedef int (*CompareFunc)(key*, key*);

int compare_long_int(key* k1, key* k2);
int compare_string(key* k1, key* k2);
int compare_float(key* k1, key* k2);
void initTable(node* hash_table[]);
key* new_key(int id, char* w, long int i, float f);
int hash(int id);
void insert_hash_table(node** hash_table, key* k, CompareFunc compare);
key* read_record(FILE* fp);
void insert_file_records();
node* find_list(node* n, key* k, CompareFunc compare);
node* insert_list(node* n, key* k);




#endif