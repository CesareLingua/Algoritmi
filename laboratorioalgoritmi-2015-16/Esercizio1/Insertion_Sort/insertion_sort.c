#include "insertion_sort.h"
#include <stdio.h>

void swap(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}	

void insertion_sort(void** array, int size, CompareFunc compare) {
  int i, j;
  
 	for(i = 1; i < size; ++i){
  	j = i - 1;
  	while(j >= 0 && (compare(array[j], array[i]) > 0)){
  		swap(&array[i], &array[j]);
  		i = j;
  		j--;
  	}
  }
}