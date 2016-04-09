#include "quick_sort.h"
#include <stdio.h>

void swap(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}	 

int partition(void** array, int start, int end, CompareFunc compare){
  void* p;
  int i;
  int j;

  p = array[start];
  i = start+1;
  j = end;
  while(i <= j){
    if(compare(array[i], p) <= 0)
      i++;
    else if(compare(array[j], p) > 0)
      j--;
    else{
      swap(&array[i], &array[j]);
      i++;
      j--;
    } 
  }
  swap(&array[start], &array[j]);
  return j;
}

void quick_sort(void** array, int start, int end, CompareFunc compare) {
  int p;
 
  if(start < end){
    p = partition(array, start, end, compare);
    quick_sort(array, start, p-1, compare);
    quick_sort(array, p+1, end, compare);
  }
}

