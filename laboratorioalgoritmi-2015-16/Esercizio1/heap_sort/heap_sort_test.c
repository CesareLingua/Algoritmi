#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "heap_sort.h"

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

void test_heap_sort_on_null_array(){
  int* array = NULL;
  heap_sort((void**) array, 0, compare_long_int );

  assert(1);
}

void test_heap_sort_on_full_array_long(){
  long int array[7] = { 11, 4, 1, -8, 10, 9, 15};
  int i;
  
  heap_sort((void**) array, 7, compare_long_int);
  
  for(i=0; i<6; ++i)
    assert(array[i] <= array[i+1]);
}

void test_heap_sort_on_equals_array(){
	long int array[6] = {5,5,5,5,5,5};
	int i;

	heap_sort((void**) array, 6, compare_long_int);

	for(i = 0; i<5; ++i)
		assert(array[i] <= array[i+1]);
}

void test_heap_sort_on_full_array_double(){
	double array[5] = {1.263, 5.753, 0.5325, -3.0043, 2.8486};
	int i;

	heap_sort((void**) array, 5, compare_double);

	for(i = 0; i<4; ++i)
		assert(array[i] <= array[i+1]);	
}

void test_heap_sort_on_full_char_array(){
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

	heap_sort((void**) array, 4, compare_string);

	for(i = 0; i<3; ++i)
		assert(strcmp(array[i], array[i+1]) < 0);

	free(array);
}

void test_heap_sort_on_sorted_array(){
	long int array[8] = {-8, -2, 0, 7, 45, 89, 90, 178};
	int i;

	heap_sort((void**)array, 8, compare_long_int);

	for(i = 0; i<7; ++i)
		assert(array[i] <= array[i+1]);	

}

void test_heap_sort_on_not_increasing_sorted_array(){
	double array[6] =  {87, 4, 1, 0, -8, -77};
	int i;

	heap_sort((void**)array, 6, compare_double);

	for(i = 0; i < 5; ++i)
		assert(array[i] <= array[i+1]);
}

void fill_array (char** s, long int* l, double* d){
	int i, j;
	char c;
	char tmp[20];
	FILE* fp;
	fp = fopen("records.csv", "r");
	c = fgetc(fp);
	for(i = 0; i < N_RECORDS; ++i){
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

  int i;
  clock_t inizio, fine;
  double tempo;
  char tipo;

  char** array_string = NULL;
  long int* array_long_int = NULL;
  double* array_double  = NULL;

  test_heap_sort_on_null_array();
  test_heap_sort_on_full_array_long();
  test_heap_sort_on_full_array_double();
  test_heap_sort_on_full_char_array();
  test_heap_sort_on_equals_array();
  test_heap_sort_on_sorted_array();
  test_heap_sort_on_not_increasing_sorted_array();
  
  array_string = (char**)malloc(sizeof(char**)*N_RECORDS);
  array_long_int = (long int*) malloc(sizeof(long int*)*N_RECORDS);
  array_double = (double*) malloc(sizeof(double*)*N_RECORDS);

  for(i = 0; i < N_RECORDS; ++i){
  	array_string[i] = (char*) malloc(sizeof(char*)*10);
  }
  
  printf("-----------------------\n");
  printf("Leggo i records...\n");
	inizio = clock();
  fill_array(array_string, array_long_int, array_double);
  fine = clock();
  tempo = (double) (fine - inizio)/CLOCKS_PER_SEC;
  printf("Tempo impiegato = %lfsec\n",tempo);
  printf("-----------------------\n\n");

  printf("-----------------------\n");
  printf("Per ordinare long int: 1\n");
  printf("Per ordinare float  : 2\n");
  printf("Per ordinare le stringhe : 3\n");
  printf("-----------------------\n\n");
  printf("Cosa ordino? ");

  scanf("%c", &tipo);
  inizio = clock();
  switch(tipo){
  	case '1':
  		printf("Ordino i long int\n");
  		heap_sort((void**)array_long_int, N_RECORDS, compare_long_int);
  		break;

  	case '2':
  		printf("Ordino i float\n");
  		heap_sort((void**)array_double, N_RECORDS, compare_double);
  		break;

  	case '3':
  		printf("Ordino le stringhe\n");
  		heap_sort((void**)array_string, N_RECORDS, compare_string);
  		break;
  }
  fine = clock();
  tempo = (double) (fine-inizio)/CLOCKS_PER_SEC;
  printf("Tempo impiegato: %lfsec\n",tempo);
  printf("-----------------------\n\n");
  
  free(array_long_int);
  free(array_double);
  free(array_string);

  return 0;
}	
