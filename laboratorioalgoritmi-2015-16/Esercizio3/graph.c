#include "graph.h"

vertex** make_graph(){
	vertex** g = (vertex**)malloc(sizeof(vertex*)*MAX_VERTEX);
	return g;
}

vertex* make_vertex(char* c, adj* f, adj* l){
	vertex* v = (vertex*)malloc(sizeof(vertex));
	v->city = c;
	v->first = f;
	v->last = l;
	v->dfs = NULL;
	return v;
}

adj* make_adj(char* c, double km){
	adj* node = (adj*)malloc(sizeof(adj));
	node->city = c;
	node->km = km;
	node->next = NULL;
	node->prev = NULL;
	node->dfs = NULL;
	node->v_pi = NULL;
	node->org_v = NULL;
	return node;
}

void print_list(adj* adj){
  while(adj != NULL){
  	printf("  -- %lf -->  ", adj->km);
  	printf("|%s|", adj->city);
  	adj = adj->next;
	}
	printf("\n");
}

void print_graph(vertex** g){
	int i;
	extern int n_vertex;
	printf("*****************************************************************\n");
	for(i = 0; i < n_vertex; i++){
		if(g[i]->city != NULL ){
			printf("%s |", g[i]->city);
			if(g[i]->dfs != NULL)
				printf("%d/%d|",g[i]->dfs->d,g[i]->dfs->f );
			print_list(g[i]->first);
			printf("*****************************************************************\n");
		}
	}
}

void enqueue(vertex* g, adj* node){
   g->last->next = node;
   g->last = node;
   node->v_pi = g;
}
	
char* read_city(FILE* fp){
	char c;
	char* city;
	int i;

	city = (char*)malloc(sizeof(char)*30);
	c = fgetc(fp);
  for(i = 0; i < 30; i++){
  	city[i] = '\0';
  	if(c != ','){
    	city[i] = c;
    	c = fgetc(fp);
  	} 
  }
  return city;
}

void read_record(vertex** g, FILE* fp){
	char* c1, *c2, *c3, *c4;;
	int i;
	extern int n_vertex;
	double km;
	adj* node;
	n_vertex = 0;
	c1 = read_city(fp);
  c2 = read_city(fp);

  if(fscanf(fp, "%lf", &km) == EOF && errno != 0 )
 		perror("No number read\n");	
	fgetc(fp);
	node = make_adj(c2, km);
 	g[n_vertex] = make_vertex(c1, node, node);
 	
 	i = 0;
 	while(i < MAX_VERTEX && !feof(fp)){
 		
 		c3 = read_city(fp);
 		c4 = read_city(fp);

 		if(fscanf(fp, "%lf", &km) == EOF && errno != 0 )
 			perror("No number read\n");
 		fgetc(fp);

 		node = make_adj(c4, km);
 		
 		if(strcmp(c1, c3) == 0){
 			enqueue(g[n_vertex], node);
 		}else{
 			n_vertex++;
			g[n_vertex] = make_vertex(c3, node, node);
 		}
 		c1 = c3;
 		i++;
 	}
}

double fill(vertex** g){
	FILE* fp;
	clock_t start, end;
	double t;
	int i, tmp_vertex;

	if((fp = fopen("debug.csv", "r")) == NULL) {
		perror("italian_dist_graph.csv MANCANTE\n");
		exit(EXIT_FAILURE);
	}
	start = clock();
	read_record(g, fp);
	tmp_vertex = n_vertex;
	for(i = 0; i < tmp_vertex; i++){
		adj_org_vertex(g, g[i]);
	}
	
	end = clock();
	t = (double) (end - start)/CLOCKS_PER_SEC;
	
	g = (vertex**)realloc(g, sizeof(vertex*)*n_vertex);
	fclose(fp);
	return t;
}

void adj_org_vertex(vertex** graph, vertex* g){
	int p_vertex = 0;
	extern int n_vertex;
	adj* v = g->first;
	while(v != NULL){
		if((p_vertex = search_vertex(graph, v->city)) >= 0){
			v->org_v = graph[p_vertex];
		}else{
			graph[n_vertex] = make_vertex(v->city, NULL, NULL);
			v->org_v = graph[n_vertex];
			n_vertex++;
		}
		v = v->next;
	}
}

vertex* make_dfs(vertex** graph, vertex* g){
	visit* d = (visit*)malloc(sizeof(visit));
	g->dfs = d;
	g->dfs->color = white;
	g->dfs->d = INF;
	g->dfs->f = INF;
	make_adj_dfs(g->first);
	return g;
}

void make_adj_dfs(adj* n){
	while(n != NULL){
		visit* v = (visit*)malloc(sizeof(visit));
		n->dfs = v;
		n->dfs->color = white;
		n->dfs->d = INF;
		n->dfs->f = INF;
		n = n->next;
	}
}

int search_vertex(vertex** g, char* city){
	int i;
	for(i = 0; i < n_vertex; i++){
		if(strcmp(g[i]->city, city) == 0){
			return i;
		}
	}
	return -1;
}

int dfs_visit(vertex** g, vertex* u, int visit_t){
	adj* v = u->first;
	visit_t++;
	u->dfs->d = visit_t;
	u->dfs->color = gray;
	while(v != NULL){
		if(v->org_v->dfs->color == white){
			visit_t = dfs_visit(g, v->org_v, visit_t);
		}
		v = v->next;
	}
	u->dfs->color = black;
	visit_t++;
	u->dfs->f = visit_t;
	return visit_t;
}

void dfs(vertex** g){
	int i;
	int visit_t;
	for(i = 0 ; i < n_vertex; i++){
		g[i] = make_dfs(g, g[i]);
	}
	visit_t = 0;
	for(i = 0; i < n_vertex; i++){
		if(g[i]->dfs->color == white){	
			visit_t = dfs_visit(g, g[i], visit_t);
		}
	}
}