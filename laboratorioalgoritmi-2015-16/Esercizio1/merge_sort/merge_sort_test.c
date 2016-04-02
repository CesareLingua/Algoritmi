#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "merge_sort.h"



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

void test_merge_sort_on_null_array(int n_records) {
  int* array = NULL;
  merge_sort((void**) array, n_records, compare_long_int);

  assert(1);
  printf("test_merge_sort_on_null_array: OK\n");
}

void test_merge_sort_on_full_array_long() {
  long int array[8] = {11, 4, 1, -8, 10, 9, 15, 5};
  //int i = 0;
  time_t m;
  time_t now = time(NULL);

  merge_sort((void**) array, 8, compare_long_int);
  m = difftime(time(NULL), now);

	/*assert(array[i] <= array[i+1]);
  for(i=0; i < 7; ++i)
  	printf("%li \n", array[i]);*/

  printf("test_merge_sort_on_full_array_long: OK\n");
  printf("	tempo ordinamento : %ld\n", m);
}

void test_merge_sort_on_equals_array(){
	long int array[6] = {5,5,5,5,5,5};
	int i;

	merge_sort((void**) array, 6, compare_long_int);

	for(i = 0; i<5; ++i)
		assert(array[i] <= array[i+1]);

	printf("test_merge_sort_on_equals_array: OK\n");	
}

void test_merge_sort_on_full_array_double(){
	double array[5] = {1.263, 5.753, 0.5325, -3.0043, 2.8486};
	int i;

	merge_sort((void**) array, 5, compare_double);

	for(i = 0; i<4; ++i)
		assert(array[i] <= array[i+1]);	

	printf("test_merge_sort_on_full_array_float: OK\n");
}

void test_merge_sort_on_char_array(){
	char** array;
	int i;
	array = (char**)malloc(sizeof(char**)*4);
	for(i = 0; i <4; ++i){
		array[i] = (char*)malloc(sizeof(char*)*6); 
	}
	array[0] = "Cesare";
	array[1] = "Lingua";
	array[2] = "Elena";
	array[3] = "Famlin";

	/*for(i = 0; i<4; ++i){
		printf("%s\n", array[i] );
	}*/

	merge_sort((void**) array, 4, compare_string);

	for(i = 0; i<3; ++i)
		assert(strcmp(array[i], array[i+1]) < 0);

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
  n_records = 200; 
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
	//test_merge_sort_on_null_array(n_records);
  test_merge_sort_on_full_array_long(/*array_long_int, n_records*/);
  //test_merge_sort_on_equals_array();
  //test_merge_sort_on_full_array_double(array_double);
  //test_merge_sort_on_char_array(array_string);

  	free(array_long_int);
  	/*free(array_double);
  	free(array_string);*/
  return 0;
}	