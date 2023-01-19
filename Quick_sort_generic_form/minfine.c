#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*a struct to keep track of the job infromations such as fine */
struct fine_ratio_val{
        int index_job; 
        int days_long;
        int fine;
    };
/*A comaring function that returns 1 if the second element is larger
else it returns 0(used for sorring in reverse order)*/
int compar_fine (const void *a, const void *b){
    const struct fine_ratio_val *fa = (struct fine_ratio_val *)a;
    const struct fine_ratio_val *fb = (struct fine_ratio_val *)b;
    if(fb->days_long*fa->fine>fb->fine*fa->days_long){
        return -1;
    }
    else if(fb->days_long*fa->fine<fb->fine*fa->days_long){
        return 1;
    }
    else{
        if(fa->index_job<fb->index_job){
            return -1;
        }
        else{
            return 1;
        }
    }
}
/*Calculates the total fine that the worker has to pay given that
   there are c number of jobs pointed by void pointer a */
int fine_calculate(void *a,int c){
    const struct fine_ratio_val *fa = (struct fine_ratio_val *)a;
    int sum=0;
    int total_days=fa[0].days_long;
    for(int i=1;i<c;i++){
        sum+=total_days*fa[i].fine;
        total_days+=fa[i].days_long;
    }
    return sum;
}

/*This program finds the sequence of jobs that minimizes the total 
  fine that has to be paid*/
void minfine(){
    int number_orders;
    scanf("%d",&number_orders);
    struct fine_ratio_val example[number_orders];
    int job_index=1;
    for(int i=0;i<number_orders;i++){
        scanf("%d %d",&example[i].days_long, &example[i].fine);
        example[i].index_job=job_index;
        job_index++;
    }
    qsort(example,number_orders,sizeof(struct fine_ratio_val),compar_fine);
    int total_fine = fine_calculate(example, number_orders);
    for(int i=0;i<number_orders;i++){
        printf("%d ",example[i].index_job);
    }
    printf("\nTotal fine: %d\n",total_fine);
}
int main(){
    minfine();
    return 0;
}