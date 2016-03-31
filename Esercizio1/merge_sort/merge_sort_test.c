#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "merge_sort.h"


/*int compare_string(void* ptr1, void* ptr2){
	char* el1 = (char*) ptr1;
	char* el2 = (char*) ptr2;

	return strcmp(el1, el2);
}*/


void fill_array (char** s,  int* l, double* d, int n_records){
	int i, j;
	char c;
	char tmp[20];
	FILE* fp;
	fp = fopen("records.csv", "r");
	c = fgetc(fp);
	for(i = 0; i < n_records; ++i){

		for(j = 0; c != ','; ++j){
			c = fgetc(fp);
		}
		c = getc(fp);
		for(j = 0; c != ','; ++j){
			s[i][j] = c;
			c = getc(fp);	
		}
		c = getc(fp);
		for(j = 0; c !=','; ++j){
			tmp[j] = c;
			c = getc(fp);
		}
		for(;tmp[j] !='\0';++j){
			tmp[j] = '\0';
		}
		l[i] = strtol((char*)tmp, NULL, 10);
		c = getc(fp);
		for (j = 0; c != '\n'; ++j){
			tmp[j] = c;
			c = fgetc(fp);
		}
		d[i] = strtod((char*)tmp,NULL);
	}
	printf("Ho finito di riempire l'array\n");
}

int main(int argc, char const *argv[]){
	int i, j;
	char c;
	char tmp[20];
	
	int n_records = 20000000; 

  	//Inizializzo gli array
  	char** array_string;
  	 int* array_long_int;
  	double* array_double;
  

 	array_string = (char**)malloc(sizeof(char**)*n_records);
  array_long_int = ( int*) malloc(sizeof( int*)*n_records);
  array_double = (double*) malloc(sizeof(double*)*n_records);

	for(i = 0; i < n_records; ++i){
	  array_string[i] = (char*) malloc(sizeof(char*)*10);
	}

	fill_array(array_string, array_long_int, array_double, n_records);
	merge_sort(array_long_int, 0, n_records );



	free(array_long_int);
  free(array_double);
  free(array_string);
  return 0;
}	