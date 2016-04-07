#include "heap_sort.h"
#include <stdio.h>

void swap(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}	

int left(int i){
  return 2*i+1;
}

int right(int i){ 
  return 2*i+2;
}

int p(int i){
  return (i-1)/2;
}

void heapify(void** array, int i, int size, CompareFunc compare){
  int l, r;
  int largest;
  l = left(i);
  r = right(i);
  if (l < size && compare(array[l], array[i]) > 0)
    largest = l;
  else 
    largest = i;
  if (r < size && compare(array[r], array[largest]) > 0)
    largest = r;
  if (largest != i) {
    swap(&array[i], &array[largest]);
    heapify(array, largest, size, compare);
  }
}

void build_heap(void** array, int size, CompareFunc compare){
  int i;
  for (i = size/2; i >= 0; i--)
    heapify(array, i, size, compare);
}

void heap_sort(void** array, int size, CompareFunc compare){
  int i;
  build_heap(array, size, compare);
  for (i = size-1; i >= 1; i--){
    swap(&array[0], &array[i]);
    size--;
    heapify(array, 0, size, compare);
  }
}