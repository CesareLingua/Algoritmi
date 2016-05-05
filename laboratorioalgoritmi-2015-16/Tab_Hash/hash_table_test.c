#include "hash_table.h"

int main(int argc, char *argv[]){
	node** hash_table; 
	int i;
	hash_table = (node**)malloc(sizeof(node*)*HSIZE);
	for(i = 0; i < HSIZE; i++){
		hash_table[i] = (node*)malloc(sizeof(node)*100);
	}
	insert_file_records(hash_table);
	
}