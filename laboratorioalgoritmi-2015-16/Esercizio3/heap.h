#ifndef __HEAP_H_KEIXJ4PDU3__
#define __HEAP_H_KEIXJ4PDU3__

#include "graph.h"

typedef struct sheap{
	int length;
	vertex** array;
}heap;

void print_heap(heap* h);

heap* make_heap(int heap_size);

int parent(int i);

int right(int i);

int left(int i);

void max_heapify(heap* h, int i);

void min_heapify(heap* h, int i);

heap* build_min_heap(vertex** g);

heap* build_max_heap(vertex** g);

vertex* extract_max(heap* h);

vertex* extract_min(heap* h);

#endif