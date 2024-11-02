#include <stdio.h>
#include <stdlib.h>

typedef int type_t;

typedef struct _node_t{
    struct _node_t *next;
    type_t value;
}node_t;

typedef struct _list_t{
    node_t *head;
    int size_list;
}list_t;

node_t *new_node(type_t value);
list_t *new_list();
void free_list(list_t *l);

node_t *list_at(list_t *l, int position);
void list_set(list_t *l, int position, type_t value);
type_t list_size(list_t *l);
void print_list(list_t *l);

void list_insert(list_t *l, type_t value, int position);
void list_push_front(list_t *l, type_t value);
void list_push_back(list_t *l, type_t value);

type_t list_erase(list_t *l, int position);
type_t list_pop_front(list_t *l);
type_t list_pop_back(list_t *l);

//Grafos com lista de adjacência

typedef struct _vertex_t{
    list_t *adj; //Vértices adjacentes
    type_t value;
    //type_t color;
}vertex_t;

typedef struct _graph_t{
    vertex_t **arr_vert; //Array de vértices
    int size;   //Número de vértices atual do grafo
    int capacity; //Número máximo de vértices permitido atualmente
}graph_t;

vertex_t *new_vertex(type_t value);
graph_t *new_graph();
void free_vertex(vertex_t *vert);
void free_graph(graph_t *graph);

/*char verify_vertex_exists(graph_t *graph, type_t value);
char verify_edge_exist(graph_t *graph, type_t vertex1, type_t vertex2);*/

void insert_vertex(graph_t *graph, type_t value);
void insert_edge(graph_t *graph, type_t id_vertex1, type_t id_vertex2);

void edge_remove(graph_t *graph, type_t id_vertex1, type_t id_vertex2);
void vertex_remove(graph_t *graph, type_t id_vertex);

void print_vertex(vertex_t *vertex);
void print_graph(graph_t *graph);
int find_vertex_position(graph_t *graph, type_t id_vertex);

