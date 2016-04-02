#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>

/*
*	Fonde due array derivati dall'array principale.
*	Il primo array va da [left...middle],
*	il secondo array va da [middle...right].
*/

void merge(void ** array, int left, int middle, int right){
	int i, j, k,z; 
	int n1 = middle - left +1;
	int n2 = right - middle;

	void** tmp_left; 
	tmp_left = malloc (sizeof(void**)*(n1));
	void ** tmp_right;
	tmp_right = malloc (sizeof(void**)*(n2));

	for(i = 0; i < n1; i++)
		tmp_left = array[left + i];

	for(j = 0; j < n2; j++)
		tmp_right = array[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2){
		if(tmp_left[i] <= tmp_right[j]){
			array[k] = tmp_left[i];
			i++;
		}else{
			array[k] = tmp_right[j];
			j++;
		}
		k++;
	}

	while ( i < n1){
		array[k] = tmp_left[i];
		i++;
		k++;
	}

	while (j < n2){
		array[k] = tmp_right[j];
		j++;
		k++;
	} 

	for(z = 0 ; z < 8; z++){
		printf("%li , ", (long int)array[z]);
	}
	printf("\n");

	free(tmp_left);
	free(tmp_right);
}

int min (int n1, int n2){
	if (n1 < n2)
		return n1;
	else
		return n2;
}

void merge_sort(void ** array, int n, CompareFunc compare){
	
	int i, left, right;

	for(i = 1; i = n-1; i =2*i){
		
		for (left = 0; left < n-1; left += 2 * i){

			int middle = left + i-1;

			/*if(compare(left + 2*i-1, n-1) <= 0)
				right = left + 2*i-1;
			else*/
			right = min(left + 2*i-1, n-1);

			merge(array, left, middle, right); 
		}
	}
}