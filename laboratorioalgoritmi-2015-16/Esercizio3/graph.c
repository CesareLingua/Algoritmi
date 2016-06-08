#include "graph.h"
#include "heap.h"

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
	node->org_v = NULL;
	return node;
}

vertex* make_dfs(vertex** graph, vertex* g){
	visit* d = (visit*)malloc(sizeof(visit));
	g->dfs = d;
	g->dfs->color = white;
	g->dfs->d = INF;
	g->dfs->f = INF;
	g->dfs->v_pi = NULL;
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
	printf("\n\n*****************************************************************\n");
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
	if(g->first == NULL){
		g->first = node;
		g->first->next = NULL;
		g->last = node;
	}else{
	   g->last->next = node;
	   g->last = node;
	}
}
	
char* read_city(FILE* fp){
	char c;
	char* city;
	int i;

	city = (char*)malloc(sizeof(char)*50);
	c = fgetc(fp);
  for(i = 0; i < 50; i++){
  	city[i] = '\0';
  	if(c != ','){
    	city[i] = c;
    	c = fgetc(fp);
  	} 
  }
  return city;
}

double read_km(FILE* fp){
	double km;

	if(fscanf(fp, "%lf", &km) == EOF && errno != 0 )
 		perror("No number read\n");	
	fgetc(fp);
	return km;
}

void read_record(vertex** g, FILE* fp){
	char* c1, *c2, *c3, *c4;
	int i;
	extern int n_vertex;
	double km;
	adj* edge;
	n_vertex = 0;

	c1 = read_city(fp);
  c2 = read_city(fp);
  km = read_km(fp);

	edge = make_adj(c2, km);
 	g[n_vertex] = make_vertex(c1, edge, edge);
 	free(c2);
 	i = 0;
 	while(i < MAX_VERTEX && !feof(fp)){
		c3 = read_city(fp);
		c4 = read_city(fp);
		km = read_km(fp);
		edge = make_adj(c4, km);
			
 		if(strcmp(c1, c3) == 0){
 			enqueue(g[n_vertex], edge);
 		}else{
 			n_vertex++;
			g[n_vertex] = make_vertex(c3, edge, edge);
		}
 		c1 = c3;
 		i++;
 	}
}

double fill(vertex** g){
	FILE* fp;   
	clock_t start, end;
	double t;
	int i;
	extern int n_vertex;

	if((fp = fopen("debug.csv", "r")) == NULL) { //italian_dist_graph
		perror("File MANCANTE\n");
		exit(EXIT_FAILURE);
	}
	start = clock();
	read_record(g, fp);
	add_blind_vertex(g);
	for(i = 0; i < n_vertex; i++){
		adj_org_vertex(g, g[i]);
	}
	end = clock();
	t = (double) (end - start)/CLOCKS_PER_SEC;
	
	g = (vertex**)realloc(g, sizeof(vertex*)*n_vertex);
	fclose(fp);
	return t;
}

void add_blind_vertex(vertex** g){
	int i;
	for(i = 0; i < n_vertex; i++){
		adj* v = g[i]->first;
		while(v != NULL){
			if(search_vertex(g, v->city) < 0){
				
				g[n_vertex] = make_vertex(v->city, NULL, NULL);
				n_vertex++;
			}
			v = v->next;
		}
	}
}

void adj_org_vertex(vertex** graph, vertex* g){
	int p_vertex = 0;
	adj* v = g->first;
	while(v != NULL){
		if((p_vertex = search_vertex(graph, v->city)) >= 0)
			v->org_v = graph[p_vertex];
		v = v->next;
	}
}

int search_vertex(vertex** g, char* city){
	int i;
	extern int n_vertex;
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
			v->org_v->dfs->v_pi = u;
			visit_t = dfs_visit(g, v->org_v, visit_t);
		}
		v = v->next;
	}
	u->dfs->color = black;
	visit_t++;
	u->dfs->f = visit_t;
	return visit_t;
}

double dfs(vertex** g){
	int i, visit_t;
	clock_t start, end;
	double t;
	extern int n_vertex;
	start = clock();
	for(i = 0 ; i < n_vertex; i++){
		g[i] = make_dfs(g, g[i]);
	}
	visit_t = 0;
	for(i = 0; i < n_vertex; i++){
		if(g[i]->dfs->color == white){	
			visit_t = dfs_visit(g, g[i], visit_t);
		}
	}
	end = clock();
	t = (double) (end-start)/CLOCKS_PER_SEC;
	return t;
}

void read_t_record(vertex** g, FILE* fp){
	char *c1, *c2;
	double km;
	int p_vertex;
	adj* edge;

	c1 = read_city(fp);
	c2 = read_city(fp);
	km = read_km(fp);
	while(!feof(fp)){
		
		if((p_vertex = search_vertex(g, c2)) >= 0){
			edge = make_adj(c1, km);
			enqueue(g[p_vertex], edge);
		}else{
			printf("Vertex not found: %s\n", c2);
			exit(EXIT_FAILURE);
		}
		c1 = read_city(fp);
		c2 = read_city(fp);
		km = read_km(fp);
	}	
}

double t_graph(vertex** graph, vertex** tgraph){
	FILE* fp;
	clock_t start, end;
	double t;
	int i;
	extern int n_vertex;
	heap* h;
	vertex* max;
	
	if((fp = fopen("debug.csv", "r")) == NULL) {
		perror("File MANCANTE\n");
		exit(EXIT_FAILURE);
	}

	start = clock();

	h = build_max_heap(graph);
	for(i = 0; i < n_vertex; i++){
		max = extract_max(h);
		tgraph[i] = make_vertex(max->city, NULL, NULL);
		tgraph[i]->dfs = NULL;
	}
	read_t_record(tgraph, fp);

	for(i = 0; i < n_vertex; i++){
		adj_org_vertex(tgraph, tgraph[i]);
	}
	end = clock();
	t = (double) (end - start)/CLOCKS_PER_SEC;
	tgraph = (vertex**)realloc(tgraph, sizeof(vertex*)*n_vertex);
	
	fclose(fp);
	return t;
}

/*void count_scc(vertex** tg){
	int n_scc, n_vrt, i;
	extern int n_vertex;
	vertex* v_pi;
	n_scc = 0;
	i = 0;
	while(i < n_vertex){
		v_pi = tg[i]->dfs->v_pi;
		n_vrt = 0;
		printf("tg[%d]->city = %s\n", i, tg[i]->city);
		if(v_pi == NULL){
			printf("Il suo v_pi = NULL\n");
		}else
			printf("Il suo v_pi = %s\n",v_pi->city );

		while(v_pi != NULL){
			n_vrt++;
			printf("tg[%d]->city = %s\n", i, tg[i]->city);
			printf(" v_pi = %s\n",v_pi->city);
			v_pi = v_pi->dfs->v_pi;

		}
		if(n_vrt != 0){
			n_scc++;
			printf("Parte fortemente connessa n. %d\n",n_scc);
			printf("    -Composta da %d vertici: \n", n_vrt);
		}
		i++;
	}
}*/

void strongly_connected_components(vertex** g){
	double t;
	vertex** tg;
	//heap* h;
	//vertex* min;
	printf("Faccio dfs...");
	t = dfs(g);
	printf("  %lf sec\n",t);
	/*h = build_min_heap(g);
	print_heap(h);
	min = extract_min(h);
	print_heap(h);*/
	printf("Costruisco grafo trasposto...");
	tg = make_graph();
	t = t_graph(g, tg);
	printf("   %lf sec\n",t);
	printf("Calcolo parti fortemente connesse...");
	t = dfs(tg);
	printf("   %lf sec\n",t);
	//count_scc(tg);
	//print_graph(tg);
}