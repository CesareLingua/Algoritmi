#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>

/*
*	Fonde due array derivati dall'array principale.
*	Il primo array va da [left...middle],
*	il secondo array va da [middle...right].
*/

void merge(void** array, int left,int middle, int right, CompareFunc compare){
	int i, j, k, z, y;

	i= left;
	j = middle + 1;
	k = 0;

	printf("left: %d - middle: %d - right: %d\n", left, middle, right);

	/*creo array d'appoggio per le metà da confrontare*/
	void** tmp; //malloc
	tmp = malloc (sizeof(void**)*(right - middle));
	for(z=0; z<middle; z++){
		tmp[z]=(void*)malloc(sizeof(char*)*10);
	}

	
	while (i <= middle && j <= right){
		if (compare(array[i], array[j]) <= 0){
			tmp[k]=array[i];
			i++;
		}else{
			tmp[k]=array[j];
			j++;
		}
		k++;
	}

	if (i <= middle){
		for(z = k, y = i; z <= (middle - i) + 1 && y <= middle + 1; z++, i++){
			tmp[z]=array[y];
			
			
		printf("%li\n",(long int) tmp[z]);	
			

		}
	}else{
		for(z = k, y = j; z <= middle - j && y <= right; z++, y++){
			tmp[z] = array[j];
			printf("%li\n",(long int) tmp[z]);
		}
		
	}
	
	/*for(z = 0, j = 0; z <= right && j < right - left; z++, j++){
		array[z] = tmp[j];
	}*/
		
	for(z = 0 ; z < 8; z++){
		printf("%li , ", (long int)tmp[z]);
	}
	printf("\n");
}


void merge_sort(void** array, int left, int right, CompareFunc compare){
	if (left < right) {				//confronto la coppia di elementi presa in esame
		int middle = (left + right)/2; 

		//ricorsione per dividere l'array in coppie
		merge_sort(array, left, middle, compare);
		//printf("RAMO SX left: %d - middle: %d\n", left, middle);
		merge_sort(array, middle + 1, right, compare);
		
		//richiamo merge per ordinare le coppie
		merge(array, left, middle, right, compare);
	
	}
	//	printf("WARNING --> wrong array's length.");		
}