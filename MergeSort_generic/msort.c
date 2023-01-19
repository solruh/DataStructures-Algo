#include <stdlib.h> // you can remove this if your code doesn't use it
#include <string.h> // you can remove this if your code doesn't use it
#include <stdio.h>

#define MAX_INPUT 1000000
/* casts the paramets to integer type and compares them returning 1 if the first argument is greater
than the second, -1 if it's the reverse and 0 if both parametes are equal */
int compar (const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
/* compares each elements of the left_half and right_half arrays and sorts them and assigns the sorted 
elements to arr(the new sorted array to be) */
void merger(void* arr,void * left_half, void *right_half,unsigned int left_size,unsigned int right_size,size_t size){
     unsigned int i=0;
     unsigned int j=0;
     unsigned int k=0;
    while(i<left_size && j<right_size){
        if((compar((char *)left_half+(i*size),(char *)right_half+(j*size)))<=0){
            memcpy((char *) arr+(k*size),(char *)left_half+(i*size),size);
            i++;
        }
        else{
            memcpy((char *)arr+(k*size),(char *)right_half+(j*size),size);
            j++;
        }
        k++;
    }
    while (i<left_size){
        memcpy((char *)arr+(k*size),(char *)left_half+(i*size),size);
        i++;
        k++;
    }
    while (j<right_size){
        memcpy((char *)arr+(k*size),(char *)right_half+(j*size),size);
        j++;
        k++;
    }
    free(left_half);
    free(right_half);  
    
}

/* The function msort divides the base array into two halves, left-half and right-half
 and recursively calls itself on each halves */
void msort(void* base ,size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    // default implementation is using qsort()
    // replace the following body with yours!
    void *left_half,*right_half;
    left_half = malloc (size * MAX_INPUT);
    right_half = malloc (size * MAX_INPUT);
    if(nmemb>=2){
         unsigned int middle_index = nmemb/2;
         unsigned int left_size = 0;
         unsigned int right_size = 0;

        if (left_half == NULL|| right_half == NULL) {
            fprintf(stderr, "memory allocation failed\n");
            return ;
        }
        for( unsigned int i=0;i<middle_index;i++){
            memcpy((char *) left_half+(i*size),(char *)base+(i*size),size);
            left_size++;
        }
        unsigned int ll=0;
        for( unsigned int j=middle_index;j<nmemb;j++){
            memcpy((char *)right_half+(ll*size),(char *)base+(j*size),size);
            right_size++;
            ll++;
        }
        msort(left_half,left_size,size, compar);
        msort(right_half, right_size,size,compar);
        return merger(base,left_half,right_half, left_size, right_size,size);

    }
    
    // qsort(base, nmemb, size, compar);    
}


