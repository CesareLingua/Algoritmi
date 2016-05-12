#include "graph.h"

int main(int argc, char*argv[]){
	node** graph;
	

	if(strcmp(argv[1], "--help") == 0){
		print_help();
	}

	graph = make_table();

	//read_records(graph, argv[1]);

	fill(graph);
	
	

}