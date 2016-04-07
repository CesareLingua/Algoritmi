#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>
#define N_CHARACTER 10

/*
*	Fonde due array derivati dall'array principale.
*	Il primo array va da [left...middle],
*	il secondo array va da [middle...right].
*/

void merge(void ** array, int left, int middle, int right, CompareFunc compare){
	int i, j, k, z;
	 
	int n1 = middle - left +1;
	int n2 = right - middle;

	void** tmp_left; 
	tmp_left = malloc (sizeof(void**)*(n1));
	for(z=0; z < n1; z++){
		tmp_left[z]=(void*)malloc(sizeof(char*)*N_CHARACTER);
	}
	void ** tmp_right;
	tmp_right = malloc (sizeof(void**)*(n2));
	for(z=0; z < n2; z++){
		tmp_right[z]=(void*)malloc(sizeof(char*)*N_CHARACTER);
	}

		
	for(i = 0; i < n1; i++)
		tmp_left[i] = array[left + i];

	for(j = 0; j < n2; j++)
		tmp_right[j] = array[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;
	
	while (i < n1 && j < n2){

		if (compare(tmp_left[i], tmp_right[j]) < 0){
		array[k] = tmp_left[i];
			i++;
		}else{
			array[k] = tmp_right[j];
			j++;
		}
		k++;
	}


	while (i < n1){
		//printf("While parte sx");
		array[k] = tmp_left[i];
		i++;
		k++;
	}

	while (j < n2){
		//printf("While parte dx");
		array[k] = tmp_right[j];
		j++;
		k++;
	} 

	free(tmp_left);
	free(tmp_right);
}



void merge_sort(void ** array, int left, int right, CompareFunc compare){
	
	if (left < right){
		int middle = left + (right - left) / 2;
		merge_sort(array, left, middle, compare);
		merge_sort(array, middle + 1, right, compare);
		merge(array, left, middle, right, compare);
	}
}