#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "msort.h"
int compare (const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
/* This function computes the median of an array of customer's addresses and 
sums the distance from this median address to all other address, which minimizes
the total distance */
long int minimize_sums(int *customers,int n){
    long int sum=0;
    msort(customers,n,sizeof(int),compare);
    int half_len = n/2;
    int median = customers[half_len];
    for(int m=0;m<n;m++){
        sum+=abs(customers[m]-median);
    }
    return sum;
}
int main(void)
{
    int i, n;
    int *customers;
    long int sum = 0;
    
    if (scanf("%d ", &n) != 1) {
        fprintf(stderr, "wrong input\n");
        return -1;
    }

    customers = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        if (scanf("%d", &customers[i]) != 1) {
            fprintf(stderr, "wrong input at %dth customer\n", i+1);
            return -1;
        }
    }
    if (i != n) {
        fprintf(stderr, "input is too short\n");
        free(customers);
        return -1;
    }
    sum = minimize_sums(customers,n);
    printf("%ld\n", sum);
    return 0;
}