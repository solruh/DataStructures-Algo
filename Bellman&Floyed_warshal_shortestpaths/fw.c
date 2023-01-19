#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <limits.h>
// #define INIFINITY 276545387
#define INIFINITY INT_MAX

/*A FLoyed Warshal algorithm,which finds shortest 
path from all possible vertices to all other possible
 vertices i.e. it's all points shortest path algorithm.
it takes no parameter*/
void Floyed_warshal(void ){
    int num_ver,num_edge;
    int start_ver,end_ver,edge_weight;
    scanf("%d %d",&num_ver,&num_edge); // should print sth if wrong input is given???
    int adjcency_matrix[num_ver+1][num_ver+1];
    int prev_arr[num_ver+1][num_ver+1];
    for (int i=1;i<=num_ver;i++){
        for(int j=1;j<=num_ver;j++){
            if(i==j){
                adjcency_matrix[i][j]=0;
                prev_arr[i][j] = i;
            }
            else{
                adjcency_matrix[i][j]=INIFINITY;
                prev_arr[i][j] = INIFINITY;  //since there is no path between i and j, we can't trace back!!
            }
        }
    }
    for(int i=0;i<num_edge;i++){
        scanf("%d %d %d",&start_ver, &end_ver,&edge_weight);   // should I print sth if wrong input is given???
        adjcency_matrix[start_ver][end_ver]=edge_weight;
        prev_arr[start_ver][end_ver] = start_ver;
    }
    int flag = 0;
    for(int i=1;i<=num_ver;i++){
        for(int j=1;j<=num_ver;j++){
            for(int k=1;k<=num_ver;k++){
                if((adjcency_matrix[j][i]==INIFINITY || adjcency_matrix[i][k]==INIFINITY)) flag=1;
                if(flag!=1){
                    if((adjcency_matrix[j][k]>adjcency_matrix[j][i]+adjcency_matrix[i][k])){
                    adjcency_matrix[j][k] = adjcency_matrix[j][i]+adjcency_matrix[i][k];
                    prev_arr[j][k]=prev_arr[i][k];
                    }
                }
                flag = 0;
            }
        
        }
    }
    for(int m=1;m<=num_ver;m++){
        if(adjcency_matrix[m][m]<0){
            printf("Error: negative-cost cycle is found\n");
            return;
        }
    }
/*this section is for back tracking the complete path
where path_to_target is the path from start to each 
vertex except the starting index*/
    for(int i=1;i<num_ver+1;i++){
        for(int j=1;j<num_ver+1;j++){
            if(i!=j){
                int start_v = i;
                int dest_v = j;
                int *path_to_target = malloc(sizeof(int) * num_ver-1);
                if(path_to_target==NULL){
                    fprintf(stderr,"Not enough memory for graph g");
                    return;
                }
                int index=0;
                int wanted_vertex = dest_v;
                if(prev_arr[start_v][wanted_vertex]!=INIFINITY){
                    path_to_target[index]=wanted_vertex;
                    while(prev_arr[start_v][wanted_vertex]!=start_v){ //initially my thought is start_v
                        wanted_vertex = prev_arr[start_v][wanted_vertex];
                        path_to_target[++index] = wanted_vertex;
                    }
                    path_to_target[++index]=start_v;
                }
                printf("%d %d length: ",i,j);
                if(adjcency_matrix[i][j]==INIFINITY){
                    printf("inf path:");
                }
                else{
                    printf("%d path:",adjcency_matrix[i][j]);
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
                free(path_to_target);
            }
        }
    }
}
int main(){
    Floyed_warshal();
    return 0;
}