#include <stdlib.h>
#include "Grafo.h"

node_t *new_node(type_t value){
    node_t *node = malloc(sizeof(node_t));
    
    node->value = value;
    node->next = NULL;
    
    return node;
}

list_t *new_list(){
    list_t *list = malloc(sizeof(list_t));

    list->head = NULL;
    list->size_list = 0;

    return list;
}

void free_list(list_t *list){
    
    while(list->head != NULL){
        node_t *aux;
        aux = list->head;
        list->head = aux->next;
        free(aux);
    }

    free(list);
}

node_t *list_at(list_t *list, int position){
    node_t *aux = list->head;

    for(int i=0; i < position && aux != NULL; i++){
        aux = aux->next;
    }
    return aux;
}

void list_set(list_t *list, int position, type_t value){
    list_at(list, position)->value = value;
}

type_t list_size(list_t *list){
    node_t *aux = list->head;
    int i = 0;

    while(aux != NULL){
        i++;
        aux = aux->next;
    }
    list->size_list = i;
    return (type_t) i;
}

void print_list(list_t *list){
    node_t *aux = list->head;
    while(aux != NULL){
        printf("%d", aux->value);
        if(aux->next != NULL){
            printf("->");
        }
        aux = aux->next;
    }
    printf("\n");
}

void list_insert(list_t *l, type_t value, int position){
    node_t *node = new_node(value);

    if(position == 0){
        node->next = l->head;
        l->head = node;
    } else{
        node_t *aux = list_at(l, position-1);
        node->next = aux->next;
        aux->next = node;
    }
    l->size_list++;
}

void list_push_front(list_t *l, type_t value){
    list_insert(l, value, 0);
}

void list_push_back(list_t *l, type_t value){
    list_insert(l, value, l->size_list);
}

type_t list_erase(list_t *l, int position){
    node_t *aux, *ptr;
    type_t value;
    if(position == 0){
        ptr = l->head;
        l->head = ptr->next;
        value = ptr->value;
    } else{
        aux = list_at(l, position-1);
        ptr = aux->next;
        value = ptr->value;
        aux->next = ptr->next;
    }
    free(ptr);
    l->size_list--;
    return value;
}

type_t list_pop_front(list_t *l){
    return list_erase(l, 0);
}

type_t list_pop_back(list_t *l){
    return list_erase(l, l->size_list-1);
}

//Grafos com listas de adjacência
vertex_t *new_vertex(type_t value){
    vertex_t *vertex = malloc(sizeof(vertex_t));

    vertex->adj = new_list();
    vertex->value = value;

    return vertex;
}

graph_t *new_graph(){
    graph_t *graph = malloc(sizeof(graph_t));

    graph->size = 0;
    scanf("%d", &graph->capacity);
    graph->arr_vert = malloc(sizeof(vertex_t*)*graph->capacity);

    return graph;
}

void free_vertex(vertex_t *vert){
    free_list(vert->adj);
    free(vert);
}
void free_graph(graph_t *graph){
    for(int i=0; i < graph->capacity; i++){
        free_vertex(graph->arr_vert[i]);
    }
}
/*
char verify_vertex_exists(graph_t *graph, type_t value);
char verify_edge_exist(graph_t *graph, type_t vertex1, type_t vertex2);*/

void insert_vertex(graph_t *graph, type_t value){
    graph->arr_vert[graph->size++] = new_vertex(value);
}

void print_vertex(vertex_t *vertex){
    printf("%d: ", vertex->value);
    print_list(vertex->adj);
}

void print_graph(graph_t *graph){
    for(int i=0; i < graph->size; i++){
        print_vertex(graph->arr_vert[i]);
    }
}

