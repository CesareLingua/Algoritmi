#ifndef __QUICK_SORT_H_KEIXJ4PDU3__
#define __QUICK_SORT_H_KEIXJ4PDU3__

typedef int (*CompareFunc)(void*, void*);

/*
 * Implementa l'algoritmo di ordinamento Quick Sort
 * array: array da ordinare 
 * size: taglia dell'array
 * compare: funzione per valutare l'ordine di 2 elementi dell'array
 */
void quick_sort(void** array, int start, int end, CompareFunc compare);

int partition(void** array, int start, int end, CompareFunc compare);
#endif