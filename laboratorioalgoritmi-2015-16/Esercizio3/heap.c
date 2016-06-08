#include "graph.h"
#include "heap.h"

void print_heap(heap* h){
	int i;
	printf("\n\n------------------- HEAP -------------------\n\n");
	for(i = 0; i < h->length; i++)
		printf("|%d", h->array[i]->dfs->f);
	printf("|\n");
}

heap* make_heap(int heap_size){
	heap* h = (heap*)malloc(sizeof(heap));
	h->length = heap_size;
	h->array = (vertex**)malloc(sizeof(vertex)*heap_size);
	return h;
}

int parent(int i){
	return (i-1)/2;
}

int left(int i){
	return 2*i+1;
}

int right(int i){
	return 2*i+2;
}

void max_heapify(heap* h, int i){
	int l = left(i);
	int r = right(i);
	int max;
	vertex* tmp;
	if(l < h->length && h->array[l]->dfs->f > h->array[i]->dfs->f)
		max = l;
	else
		max = i;
	if(r < h->length && h->array[r]->dfs->f > h->array[max]->dfs->f)
		max = r;

	if(max != i){
		tmp = h->array[i];
		h->array[i] = h->array[max];
		h->array[max] = tmp;
		max_heapify(h, max);
	}
}

void min_heapify(heap* h, int i){
	int l = left(i);
	int r = right(i);
	int min;
	vertex* tmp;
	if(l < h->length && h->array[l]->dfs->f < h->array[i]->dfs->f)
		min = l;
	else
		min = i;
	if(r < h->length && h->array[r]->dfs->f < h->array[min]->dfs->f)
		min = r;

	if(min != i){
		tmp = h->array[i];
		h->array[i] = h->array[min];
		h->array[min] = tmp;
		min_heapify(h, min);
	}
}

heap* build_min_heap(vertex** g){
	extern int n_vertex;
	int i;
	heap* h = make_heap(n_vertex);

	for(i = 0; i <= n_vertex; i++){
		h->array[i] = g[i];
	}
	for(i = h->length/2; i >= 0; i--)
		min_heapify(h, i);

	return h;
}

heap* build_max_heap(vertex** g){
	extern int n_vertex;
	int i;
	heap* h = make_heap(n_vertex);

	for(i = 0; i <= n_vertex; i++){
		h->array[i] = g[i];
	}
	for(i = h->length/2; i >= 0; i--)
		max_heapify(h, i);

	return h;
}

vertex* extract_max(heap* h){
	vertex* max = (vertex*)malloc(sizeof(vertex));

	max = h->array[0];
	h->array[0]= h->array[h->length-1];
	h->length--;
	max_heapify(h, 0);
	
	return max;
}

vertex* extract_min(heap* h){
	vertex* min = (vertex*)malloc(sizeof(vertex));

	min = h->array[0];
	h->array[0]= h->array[h->length-1];
	h->length--;
	min_heapify(h, 0);
	
	return min;
}
