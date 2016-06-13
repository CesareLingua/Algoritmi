#ifndef __MERGE_SORT_H_UVNDHRT56DJ__
#define __MERGE_SORT_H_UVNDHRT56DJ__

typedef int (*CompareFunc)(void*, void*);

/*
 * Implementa l'algoritmo di ordinamento Merge Sort
 * array: array da ordinare
 * left: primo elemento dell'array
 * right: ultimo elemento dell'array
 */
void merge_sort(void** array, int left, int right, CompareFunc compare);

#endif
