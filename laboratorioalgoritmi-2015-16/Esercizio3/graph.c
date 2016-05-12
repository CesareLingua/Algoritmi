#include "graph.h"


key* new_key(char* c, double km){
	key* k = (key*)malloc(sizeof(key));
	km->km;
	city->c;
	return k;
}

node* new_node(key* k, node* next, node* prev){
	node* n = (node*)malloc(sizeof(node));
	n->record = k;
	n->next = next;
	n->prev = prev;
	return n;
}

node** make_graph(){
	key* k;
	node** graph;
	int i;
	graph = (node**)malloc(sizeof(node*)*HSIZE);
	for(i = 0; i < HSIZE; i++){
		k = new_key(0, "", 0, 0);
		graph[i] = new_node(k);
	}
	return graph;
}

int charValue(char c){
	return (c- 'a')+1;
}


int hash(char* w){
	int val = 0;
	while(*w!= '\0'){
		val = (27* + charValue(*w)) % HSIZE;
		w++;
	}
	return val;
}

node* insert_list(node* n, key* k){
  node* new_node = (node*)malloc(sizeof(node));
  new_node->record = k;
  new_node->next = n;
  new_node->prev = NULL;
  if(n != NULL)
    n->prev = new_node;
  return new_node;
}

int find_list(node* n, key* k){
  for(; n != NULL; n = n->next	){
   if((strcmp(n->record->city, k->city)) == 0){
      return 1;
    }
  }
  return -1;
}

void insert(node* n , key* k){
	if(find_list(n, k) == -1)
   	n = insert_list(n, k);
  
}

void read_record(node** graph){
	FILE* fp;
	char* c1;
	char* c2;
	char c;
	int i, hash_val;
	double km;
	node* n, n1;
	key* k, k1;

	c1 = (char*)malloc(sizeof(char)*50);
	c2 = (char*)malloc(sizeof(char)*50);

	fp = fopen("italian_dist_graph.csv", "r");

	c = fgetc(fp);
  for(i = 0; i <50; i++){
  	c1[i] = '\0';
  	if(c != ','){
    	c1[i] = c;
    	c = fgetc(fp);
  	} 
  }

  k = new_key(c1, 0);
  n = new_node(k, NULL, NULL);

   
  hash_val = hash(c1);
  insert(hash_table[hash_val] ,n);
  
  c = fgetc(fp);
  for(i = 0; i <50; i++){
  	c2[i] = '\0';
  	if(c != ','){
    	c2[i] = c;
    	c = fgetc(fp);
  	} 
  }

  fscanf(fp, "%lf", &km);

  k1 = new_key(c2, km); 
  n1 = new_node(k1, NULL, NULL);
	
  /*n->next = n1;
	n1->prev = n;*/

	insert(hash_table[hash_val], n1);
	
	
}

void fill(node** graph){
	int i;
	
	for(i = 0; i < HSIZE; i++){
		read_records(graph);
	}

}

