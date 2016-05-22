#include "graph.h"

int main(int argc, char*argv[]){
	vertex** graph;
	double t;
	
	/*if(strcmp(argv[1], "--help") == 0){
		print_help();
	}*/

	graph = make_graph();
	t = fill(graph);
	printf("Tempo costruzione grafo: %lf\n",t);

	dfs(graph);
	print_graph(graph);
}