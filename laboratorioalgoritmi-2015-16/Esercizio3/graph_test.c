#include "graph.h"
#include "heap.h"

int main(int argc, char*argv[]){
	vertex** graph;
	double t;

	printf("Costruisco grafo...");
	graph = make_graph();
	t = fill(graph);
	printf("    %lf sec\n",t);
	
	strongly_connected_components(graph);


	//print_graph(graph);
	//print_graph(tgraph);	
}