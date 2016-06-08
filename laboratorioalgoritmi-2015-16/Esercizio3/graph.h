#ifndef __GRAPH_H_KEIXJ4PDU3__
#define __GRAPH_H_KEIXJ4PDU3__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define MAX_VERTEX 60000
#define INF INT_MAX/2;

int n_vertex;

typedef enum ecolor{white, gray, black}color;

typedef struct svisit{
	color color;
	struct svertex* v_pi;
	int d;
	int f;
}visit;

typedef struct sadj { 		
 	char* city;
 	double km;	
 	visit* dfs;
 	struct svertex* org_v; //puntatore al vertice originale nell'array 			
	struct sadj* next;	
	struct sadj* prev;	
}adj;


typedef struct svertex{
	visit* dfs;
	char* city;
	adj* first;
	adj* last;
}vertex;

vertex** make_graph();

double fill(vertex** g);

void read_record(vertex** g, FILE* fp);

char* read_city(FILE* fp);

double read_km(FILE* fp);

adj* make_adj(char* c, double km);

void enqueue(vertex* g, adj* a);

void print_list(adj* adj);

void print_graph(vertex** g);

void add_blind_vertex(vertex** g);

void adj_org_vertex(vertex** graph, vertex* g);

double dfs(vertex** g);

int dfs_visit(vertex** g, vertex* u, int visit_t);

void make_adj_dfs(adj* n);

vertex* make_dfs(vertex** graph, vertex* g);

int search_vertex(vertex** g, char* city);

double t_graph(vertex** graph, vertex** tgraph);

void read_t_record(vertex** g, FILE* fp);

void count_scc(vertex** tg);

void strongly_connected_components(vertex** g);


#endif

