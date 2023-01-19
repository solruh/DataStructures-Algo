#include<stdlib.h>
#include<stdio.h>
#include<string.h>
// #define INIFINITY 276545387
#include <limits.h>
#define INIFINITY INT_MAX
int negative_cycle = 0;
int num_ver,num_edge;
int start_ver,end_ver,edge_weight;
/*An edge struct to define a given edge
with startving vertex,ending vertex and 
the edge's weight*/
struct Edge{
    int starting_ver;
    int ending_ver;
    int weight;
};
typedef struct Edge Edge;
/*A graph struct that defines number of 
vertices and edges of a graph and a pointer
to array of edges*/
struct Graph{
    Edge *edge_arr;
    int num_vertices;
    int num_edges;
};
typedef struct Graph graph;

void updater(int start,graph *g,int **distance_arr,int **previous_array){
    *distance_arr = (int *)malloc(sizeof(int)*num_ver+1);
    *previous_array = (int *)malloc(sizeof(int)*num_ver+1);
    if(*distance_arr==NULL || *previous_array==NULL){
        fprintf(stderr,"Not enough memory for the arrays!");
        return;
    }
    for(int i=1;i<=num_ver;i++){
        (*distance_arr)[i] = INIFINITY;
        (*previous_array)[i] = 0;
    }
    (*distance_arr)[start] = 0;

    for(int j=0;j<num_ver-1;j++){
        for(int k=0;k<num_edge;k++){
            int start_v = g->edge_arr[k].starting_ver;
            int end_v = g->edge_arr[k].ending_ver;
            int weight = g->edge_arr[k].weight;
            if((*distance_arr)[start_v]!=INIFINITY && 
            (*distance_arr)[start_v]+weight<(*distance_arr)[end_v])
            {
                (*distance_arr)[end_v] = (*distance_arr)[start_v]+weight;
                (*previous_array)[end_v] = start_v;
            }

        }
    }
    for(int m=0;m<num_edge;m++){
        int start_v = g->edge_arr[m].starting_ver;
        int end_v = g->edge_arr[m].ending_ver;
        int weight = g->edge_arr[m].weight;
        if((*distance_arr)[start_v]!=INIFINITY && 
        (*distance_arr)[start_v]+weight<(*distance_arr)[end_v])
        {
            negative_cycle = 1;
            return;
        }
    }
}
/*this section is for back tracking the complete path
where path_to_target is the path from start to each 
vertex except the starting index*/
void back_tracking(int start,int *dist_arr,int *prev_arr){
    int *path_to_target = malloc(sizeof(int) * num_ver-1);
    if(path_to_target==NULL){
        fprintf(stderr,"Not enough memory for graph g");
        return;
    }
    for(int path_s = 1;path_s<=num_ver;path_s++){
        int index=0;
        if(start!=path_s){
            int wanted_vertex = path_s;
            if(prev_arr[wanted_vertex]!=0){
                path_to_target[index]=wanted_vertex;
                while(prev_arr[wanted_vertex]!=start){
                    wanted_vertex = prev_arr[wanted_vertex];
                    path_to_target[++index] = wanted_vertex;
                }
                path_to_target[++index]=start;
            }
            printf("%d %d length: ",start,path_s);
            if(dist_arr[path_s]==INIFINITY){
                printf("inf path:");
            }
            else{
                printf("%d path:",dist_arr[path_s]);
            }
            if(index>0){
                for(int mm=index;mm>-1;mm--){
                    printf(" %d",path_to_target[mm]);
                    }
            }
            else{
                printf(" none");
            }
            printf("\n");
        }

    }
    free(path_to_target);
}

/*Bellman ford algorithm to find the shortest
path from a starting vertex to all other vertices
which has a path from starting vertex*/
void Bellman_ford(graph *g,int start,int flag){
    int *dist_arr;
    int *prev_arr;
    
    // In case of not passing argument from command line, it should be handled here
    if(flag==2){
        for(int j=1;j<=num_ver;j++){
            int star_v = j;
            updater(star_v,g,&dist_arr,&prev_arr);
            if(negative_cycle==1){
                printf("Error: negative-cost cycle is found\n");
                return;
            }
            back_tracking(star_v,dist_arr,prev_arr);
            free(dist_arr);
            free(prev_arr);
        }
    }
    else{
        updater(start,g,&dist_arr,&prev_arr);
        if(negative_cycle==1){
            printf("Error: negative-cost cycle is found\n");
            return;
        }
        back_tracking(start,dist_arr,prev_arr);
        free(dist_arr);
        free(prev_arr);
    }
}

    
int main(int argc, char *argv[]){
    graph *g = (graph *)malloc(sizeof(graph));
    if(g==NULL){
        fprintf(stderr,"Not enough memory for graph g");
        return 0;
    }
    scanf("%d %d",&num_ver,&num_edge); // should print sth if wrong input is given???
    g->edge_arr = (Edge *)malloc(sizeof(Edge)*num_edge);
    if(g->edge_arr==NULL){
        fprintf(stderr,"Not enough memory for graph g");
        return 0;
    }
    for(int i=0;i<num_edge;i++){
        scanf("%d %d %d",&start_ver, &end_ver,&edge_weight);   // should print sth if wrong input is given???
        g->edge_arr[i].starting_ver = start_ver;
        g->edge_arr[i].ending_ver = end_ver;
        g->edge_arr[i].weight = edge_weight;
    }
    if(argc==2){
        //calculate shortest path from  starting vertext to all other vertices
        int startV_id;
        startV_id = atoi(argv[1]);
        
        Bellman_ford(g,startV_id,1);
    }
    else{
        //calculate shortest path from all vertext to all other verteices
        // the last two 2s are just random;first 2 is not really used,but the
        //second 2 is used to flag that we need to find all points shortest path
        Bellman_ford(g,2,2);
    }

    return 0;
}