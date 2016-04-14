#ifndef __INSERTION_SORT_H_KEIXJ4PDU3__
#define __INSERTION_SORT_H_KEIXJ4PDU3__

#define N_RECORDS 20000000

typedef int (*CompareFunc)(void*, void*);

/*
 * Implementa l'algoritmo di ordinamento Insertion Sort
 * array: array da ordinare 
 * size: taglia dell'array
 * compare: funzione per valutare l'ordine di 2 elementi dell'arry
 */
void insertion_sort(void** array, int size, CompareFunc compare);

#endif