#ifndef __GRAPH_H_KEIXJ4PDU3__
#define __GRAPH_H_KEIXJ4PDU3__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#define HSIZE 20000 

typedef struct key_frame{
	char* city;	
	double km;								
 }key;

 typedef struct lnode { 		
 	key* record;					
	struct lnode *next;		
 	struct lnode *prev; 	
}node;

key* new_key(char* c, double km);

node* new_node(key* k, node* next, node* prev);

node** make_graph(node** graph);

int charValue(char c);

int hash(char* w);

void read_record();

