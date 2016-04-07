#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "insertion_sort.h"

int compare_long_int(void* ptr1, void* ptr2){
  long int el1 = (long int) ptr1;
  long int el2 = (long int) ptr2;

  if(el1<el2) {
    return -1;
  }
  if (el1 == el2) {
    return 0;
  }
  return 1; 
}

int compare_string(void* ptr1, void* ptr2){
	return strcmp((char*) ptr1, (char*) ptr2);
}

int compare_double(void* ptr1, void* ptr2){
	double el1 = *(double*) &ptr1;
	double el2 = *(double*) &ptr2;

	if(el1<el2) 
	  return -1;
	if (el1 == el2)
	    return 0;

	return 1;
}

void test_insertion_sort_on_null_array(){
  int* array = NULL;
  insertion_sort((void**) array, 0, compare_long_int );

  assert(1);
}

void test_insertion_sort_on_full_array_long(){
  long int array[7] = { 11, 4, 1, -8, 10, 9, 15};
  int i;
  
  insertion_sort((void**) array, 7 , compare_long_int);
  
  for(i=0; i<6; ++i)
    assert(array[i] <= array[i+1]);
}

void test_insertion_sort_on_equals_array(){
	long int array[6] = {5,5,5,5,5,5};
	int i;

	insertion_sort((void**) array, 6, compare_long_int);

	for(i = 0; i<5; ++i)
		assert(array[i] <= array[i+1]);
}

void test_insertion_sort_on_full_array_double(){
	double array[5] = {1.263, 5.753, 0.5325, -3.0043, 2.8486};
	int i;

	insertion_sort((void**) array, 5, compare_double);

	for(i = 0; i<4; ++i)
		assert(array[i] <= array[i+1]);	
}

void test_insertion_sort_on_char_array(){
	char** array;
	int i;

	array = (char**)malloc(sizeof(char**)*4);
	for(i = 0; i <4; ++i){
		array[i] = (char*)malloc(sizeof(char*)*6); 
	}

	array[0] = "array";
	array[1] = "Stack";
	array[2] = ".heap";
	array[3] = "voId";

	insertion_sort((void**) array, 4, compare_string);

	for(i = 0; i<3; ++i)
		assert(strcmp(array[i], array[i+1]) < 0);

	free(array);
}

void test_insertion_sort_on_sorted_array(){
	long int array[8] = {-8, -2, 0, 7, 45, 89, 90, 178};
	int i;

	insertion_sort((void**)array, 8, compare_long_int);

	for(i = 0; i<7; ++i)
		assert(array[i] <= array[i+1]);	

}

void test_insertion_sort_on_not_increasing_sorted_array(){
	double array[6] =  {87, 4, 1, 0, -8, -77};
	int i;

	insertion_sort((void**)array, 6, compare_double);

	for(i = 0; i < 5; ++i)
		assert(array[i] <= array[i+1]);
}

int count_records(){
	int n_records;
	char c;
	FILE* fp;
	if((fp = fopen("records.csv", "r")) == NULL) 
		perror("Non sono riuscito ad aprire il file (records.csv)\n");

	while(!feof(fp)){
		c = fgetc(fp);
		if(c == '\n')
			n_records++;
	}
	fclose(fp);
	return n_records;
}

void fill_array (char** s, long int* l, double* d, int n_records){
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
		d[i] = strtod((char*)tmp	,NULL);
	}
	fclose(fp);
}


int main(int argc, char const *argv[]){

  int n_records, i;
  time_t m, now;

  char** array_string = NULL;
  long int* array_long_int = NULL;
  double* array_double  = NULL;

  test_insertion_sort_on_null_array();
  test_insertion_sort_on_full_array_long();
  test_insertion_sort_on_full_array_double();
  test_insertion_sort_on_full_char_array();
  test_insertion_sort_on_equals_array();
  test_insertion_sort_on_sorted_array();
  test_insertion_sort_on_not_increasing_sorted_array();

  printf("Conto il numero di righe...\n");
  now = time(NULL);
  n_records = count_records();
  m = difftime(time(NULL), now); 
  printf("	-Numero righe: %d\n", n_records );
  printf("	-Tempo impiegato = %ldsec\n", m);
  
  array_string = (char**)malloc(sizeof(char**)*n_records);
  array_long_int = (long int*) malloc(sizeof(long int*)*n_records);
  array_double = (double*) malloc(sizeof(double*)*n_records);

  for(i = 0; i < n_records; ++i){
  	array_string[i] = (char*) malloc(sizeof(char*)*10);
  }
  
  printf("\nLeggo %d di records...\n",n_records);
	now = time(NULL);
  fill_array(array_string, array_long_int, array_double, n_records);
  m = difftime(time(NULL), now);
  printf("	-Tempo impiegato = %ldsec\n",m);

  printf("\nInizio ad ordinare...\n");
  now = time(NULL);
  //insertion_sort((void**)array_string, n_records, compare_string);
  //insertion_sort((void**)array_long_int, n_records, compare_long_int);
  //insertion_sort((void**)array_double, n_records, compare_double);
  m = difftime(time(NULL), now);
  printf("	-Tempo impiegato = %ldsec\n", m);

  free(array_long_int);
  free(array_double);
  free(array_string);

  return 0;
}	