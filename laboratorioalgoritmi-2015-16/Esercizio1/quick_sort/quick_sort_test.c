#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "quick_sort.h"

int compare_long_int(void* ptr1, void* ptr2) {
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
	char* el1 = (char*) ptr1;
	char* el2 = (char*) ptr2;

	return strcmp(el1, el2);
}

int compare_double(void* ptr1, void* ptr2){
	//printf("primo: %f\nsecondo %f\n", *(float*)&ptr1, *(float*)&ptr2);

	double el1 = *(double*) &ptr1;
	double el2 = *(double*) &ptr2;

	if(el1<el2) 
	  return -1;

	if (el1 == el2)
	    return 0;

	return 1;
}

void test_quick_sort_on_null_array() {
  int* array = NULL;
  quick_sort((void**) array, 0, 0, compare_long_int );

  assert(1);
  printf("test_quick_sort_on_null_array: OK\n");
}

void test_quick_sort_on_full_array_long(long int* array, int n_records) {
  //long int array[7] = { 11, 4, 1, -8, 10, 9, 15};
  int i;
  time_t m;
  time_t now = time(NULL);

  quick_sort((void**) array, 0, n_records -1 , compare_long_int);
  m = difftime(time(NULL), now);

  for(i=0; i<n_records-1; ++i)
    assert(array[i] <= array[i+1]);

  printf("\ntest_quick_sort_on_full_array_long: OK\n");
  printf("	tempo ordinamento : %ld\n", m);
}

void test_quick_sort_on_equals_array(){
	long int array[6] = {5,5,5,5,5,5};
	int i;

	quick_sort((void**) array, 0, 6, compare_long_int);

	for(i = 0; i<5; ++i)
		assert(array[i] <= array[i+1]);

	printf("test_quick_sort_on_equals_array: OK\n");	
}

void test_quick_sort_on_full_array_double(double* array, int n_records){
	//double array[5] = {1.263, 5.753, 0.5325, -3.0043, 2.8486};
	int i;
	time_t m;
  	time_t now = time(NULL);

	quick_sort((void**) array, 0, n_records-1, compare_double);

	m = difftime(time(NULL), now);
	for(i = 0; i<n_records-1; ++i)
		assert(array[i] <= array[i+1]);	

	printf("test_quick_sort_on_full_array_double: OK\n");
	printf("	tempo ordinamento : %ld\n", m);
}

void test_quick_sort_on_char_array(char** array, int n_records){
	//char** array;
	int i;
	/*array = (char**)malloc(sizeof(char**)*4);
	for(i = 0; i <4; ++i){
		array[i] = (char*)malloc(sizeof(char*)*6); 
	}
	array[0] = "Cesare";
	array[1] = "Lingua";
	array[2] = "Elena";
	array[3] = "Famlin";*/

	/*for(i = 0; i<4; ++i){
		printf("%s\n", array[i] );
	}*/
	time_t m;
  	time_t now = time(NULL);

	quick_sort((void**) array, 0, n_records-1, compare_string);

	m = difftime(time(NULL), now);

	for(i = 0; i<n_records-1; ++i)
		assert(strcmp(array[i], array[i+1]) <= 0);

	printf("test_quick_sort_on_full_array_CHAR: OK\n");
	printf("	tempo ordinamento : %ld\n", m);
	/*for(i = 0; i<4; ++i){
		free(array[i]);
	}
	free(array);*/
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
}


int main(int argc, char const *argv[]) {

 
  //Conto numero elementi
  //char c[100];
  int n_records, i;
  time_t m;
  time_t now;
  /*FILE* fp = fopen("records.csv", "r"); 
  while(fgets(c, 100, fp) != NULL){
  	n_records++;
  }
	
  printf("Numero di righe del file records.csv = %d\n", n_records);*/
  n_records = 20000000; 
  //Inizioalizzo gli array
  char** array_string;
  long int* array_long_int;
  double* array_double;
  

  array_string = (char**)malloc(sizeof(char**)*n_records);
  array_long_int = (long int*) malloc(sizeof(long int*)*n_records);
  array_double = (double*) malloc(sizeof(double*)*n_records);

  for(i = 0; i < n_records; ++i){
  	array_string[i] = (char*) malloc(sizeof(char*)*10);
  }
	now = time(NULL);
  fill_array(array_string, array_long_int, array_double, n_records);
  m = difftime(time(NULL), now);
  printf("Tempo lettura da file = %ld\n",m);
/*
 * Unit test su:
 * array nullo, con elementi casuali e tutti uguali
 */
  //test_quick_sort_on_null_array();
  //test_quick_sort_on_full_array_long(array_long_int, n_records);
  //test_quick_sort_on_equals_array();
  test_quick_sort_on_full_array_double(array_double, n_records);
  //test_quick_sort_on_char_array(array_string, n_records);

  free(array_long_int);
  free(array_double);
  free(array_string);
  return 0;
}	