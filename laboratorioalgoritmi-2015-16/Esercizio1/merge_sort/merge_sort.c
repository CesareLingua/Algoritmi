#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>

/*
*	Fonde due array derivati dall'array principale.
*	Il primo array va da [left...middle],
*	il secondo array va da [middle...right].
*/

void merge(int array [], int left, int middle, int right){
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	/*creo array d'appoggio per le metà da confrontare*/
	int l_tmp[n1];
	int r_tmp[n2];

	/*inserisco i dati di array negli array d'appoggio*/
	for(i = 0; i < n1; i++)
		l_tmp[i] = array[left +1];
	for(j = 0 ; j < n2; j++)
		r_tmp[j] = array [middle +1 + j];

	/*	
	*	Inserisco gli array d'appoggio nell'array originario
	* 	ordinando gli elementi
	*/
	i = 0;
	j = 0;
	k = left;
	while(i < n1 && j < n2){
		/*caso in cui il contenuto di l_tmp[i] sia minore*/
		if(l_tmp[i] < = r_tmp[j]){
			array[k] = l_tmp[i];
			i++;
		}else{ /*caso in cui il contenuto di r_tmp[j] sia minore*/
			array[k] = r_tmp[j];
			j++;
		}
		k++; 
	}

	/*Copio gli elemnti rimanenti di l_tmp*/
	while( i < n1){
		array[k] = l_tmp[i];
		i++;
		k++;
	}
	/*Copio gli elemnti rimanenti di r_tmp*/
	while( j < n2){
		array[k] = r_tmp[j];
		j++;
		k++;
	}
}


void merge_sort(int array [], int left, int right){
	if (left < right) {				//confronto la coppia di elementi presa in esame
		int middle = (left + right)/2; 

		//ricorsione per dividere l'array in coppie
		mergeSort(array, left, middle);
		mergeSort(array, middle + 1, right);

		//richiamo merge per ordinare le coppie
		merge(array, left, middle, right);
	}else
		printf("WARNING --> wrong array's length.");		
}