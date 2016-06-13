#include <stdlib.h>
#include <stdio.h>
#include "merge_sort.h"


void merge(void **array, int left, int middle, int right, CompareFunc compare){
  int ileft = left;
  int iright = middle + 1;
  int itmp = 0;

  // creo l'array tmp di dimensione esatta (il numero di elementi tra left e right COMPRESI)
  void** tmpArray = (void**) malloc(sizeof(void*) * (right-left+1)); // +1 era qui l'errore!!
  
  while ((ileft <= middle) && (iright <= right)){
    if (compare(array[ileft], array[iright]) <= 0){
      tmpArray[itmp] = array[ileft]; // sinistro piu piccolo, inserisco in tmp
      ileft++;
    } else {
      tmpArray[itmp] = array[iright]; // destro piu piccolo, inserisco in tmp
      iright++;
    }
    itmp++;
  }

  // copio i rimanenti dell'array sinistro
  while (ileft <= middle){
    tmpArray[itmp] = array[ileft];
    ileft++;
    itmp++;
  }

  // copio i rimanenti dell'array destro
  while (iright <= right){
    tmpArray[itmp] = array[iright];
    iright++;
    itmp++;
  }

  // copio tutto l'array tmp nell'array originario
  for(itmp = left; itmp <= right; itmp++){
    array[itmp] = tmpArray[itmp - left];
  }

  // distruggo l'array tmp
  free(tmpArray);

}

void merge_sort(void **array, int left, int right, CompareFunc compare){

  if (left < right){
    int middle = (left+right) / 2;
    merge_sort(array, left, middle, compare);
    merge_sort(array, middle+1, right, compare);
    merge(array, left, middle, right, compare);
  }

}
