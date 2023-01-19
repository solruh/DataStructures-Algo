#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_INPUT 10000000
int compar (const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
/*global integers that are used to track the number of comparisions
made for each type of quick sorting, all are intitialized to zero*/
long long int first_comparision=0,last_comparision=0,random_comparision=0,median_comparision=0;

/*This function is used to exchange the values in the memory postions pointed 
  by pointers ptr1 and ptr2*/
void swap(void *ptr1, void *ptr2,size_t size){
    char *ptr11 = (char *)ptr1;
    char *ptr22 = (char *)ptr2;
    while(size>0){
        char temp = *ptr11;
        *ptr11++=*ptr22;
        *ptr22++=temp;
        size--;
    }
}
/* A recursive function used to sort a given base_array by choosing the first element
   of the given base_arr as a pivot of partioning for each recursive call*/
void q_sort_first(void *base_arr,size_t nitems,size_t size, int (*compar)(const void *, const void*)){
    if(nitems<=1){
        return;
    }
    first_comparision+=(nitems-1);
    size_t left=1,right;
    for(right=left;right<nitems;right++){
        if((compar((char *)base_arr+(right*size),(char *)base_arr))<0){
            swap((char *)base_arr+(right*size),(char *)base_arr + (left*size),size);
            left++;
        }
    }
    swap((char *)base_arr,(char *)base_arr + (size*(left-1)),size);
    void *left_half = base_arr;
    void *right_half = (char *)base_arr + (size*left);
    q_sort_first(left_half,left-1,size,compar);
    q_sort_first(right_half,right-left,size,compar);
    

}
/* A recursive function used to sort a given base_array by choosing the last element
   of the array as a pivot of partioning for each recursive call*/
void q_sort_last(void *base_arr,size_t nitems,size_t size, int (*compar)(const void *, const void*)){
    if(nitems<=1){
        return ;
    }
    int pivot_index = nitems-1;
    swap((char *)base_arr + (size*pivot_index),base_arr,size);
    size_t temp=nitems-1;
    last_comparision+=temp;
    size_t left=1,right;
    for(right=left;right<nitems;right++){
        if((compar((char *)base_arr+(right*size),(char *)base_arr))<0){
            swap((char *)base_arr+(right*size),(char *)base_arr + (left*size),size);
            left++;
        }
    }
    swap((char *)base_arr,(char *)base_arr + (size*(left-1)),size);
    void *left_half = base_arr;
    void *right_half = (char *)base_arr + (size*left);
    q_sort_last(left_half,left-1,size,compar);
    q_sort_last(right_half,right-left,size,compar);
}
/* A recursive function used to sort a given base_array by choosing a random element
   of the array as a pivot of partioning for each recursive call*/
void q_sort_random(void *base_arr,size_t nitems,size_t size, int (*compar)(const void *, const void*)){
    if(nitems<=1){
        return ;
    }
    size_t temp=nitems-1;
    random_comparision+=temp;
    int pivot_index = rand()%nitems;
    swap((char *)base_arr + (size*pivot_index),base_arr,size);
    size_t left=1,right;
    for(right=left;right<nitems;right++){
        if((compar((char *)base_arr+(right*size),base_arr))<0){
            swap((char *)base_arr+(right*size),(char *)base_arr + (left*size),size);
            left++;
        }
    }
    swap(base_arr,(char *)base_arr + (size*(left-1)),size);
    void *left_half = base_arr;
    void *right_half = (char *)base_arr + (size*left);
    q_sort_random(left_half,left-1,size,compar);
    q_sort_random(right_half,right-left,size,compar);
}
/*This function finds the number of comparisions it takes to 
find the median of three elements*/
int ternary_median(void *base_arr,size_t nitems,size_t size){
    if(nitems>2){
        int num_comps = 0;
        void *first = (char *)base_arr+(0*size);
        int mid;
        void *laste = (char *)base_arr+((nitems-1)*size);
        if(nitems%2==0){
            mid = (nitems/2)-1;
        }
        else{
            mid=nitems/2;
        }
        void *middle = (char *)base_arr+ (mid*size);
        int a = *(int *)(first);
        int b = *(int *)(middle);
        int c = *(int *)(laste);
        if(a>b){
            if(b>c){
                swap((char *)base_arr + (size*mid),base_arr,size);
                num_comps=2;
            }
            else{
                if(a>c){
                    swap((char *)base_arr+((nitems-1)*size),base_arr,size);
                    num_comps=3;
                }
                else{
                    num_comps=3;
                } 
            }
        }
        else{
            if(a>c)
                {
                    num_comps=2;
                }
                else{
                    if(b<c){
                    swap((char *)base_arr+(mid*size),base_arr,size); //middle element
                    num_comps=3;
                }
                else{
                    swap((char *)base_arr+((nitems-1)*size),base_arr,size);
                    num_comps=3;
                    }
                } 
    }
    return num_comps;
    } 
    return 0;
}

/* A recursive function used to sort a given base_array by choosing the median
of the first, middle and last elements of the given base_arr as a pivot of
 partioning for each recursive call*/
void q_sort_median(void *base_arr,size_t nitems,size_t size, int (*compar)(const void *, const void*)){
    if(nitems<=1){
        return ;
    }
    
    int num_compar;
    num_compar = ternary_median(base_arr,nitems,size);
    median_comparision+=( num_compar + nitems-1);
    size_t left=1,right;
     
    for(right=left;right<nitems;right++){
        if((compar((char *)base_arr+(right*size),(char *)base_arr))<0){
            swap((char *)base_arr+(right*size),(char *)base_arr + (left*size),size);
            left++;
        }
    }
    swap((char *)base_arr,(char *)base_arr + (size*(left-1)),size);
    void *left_half = (char *)base_arr;
    void *right_half = (char *)base_arr + (size*left);
    q_sort_median(left_half,left-1,size,compar);
    q_sort_median(right_half,right-left,size,compar);
}

int main()
{   
    srand(time(NULL));
    int num_elements=0;
    int array_element; 
    int * input_array,*source_array;
    source_array = malloc (sizeof(int) * MAX_INPUT);
    if(source_array==NULL){
        fprintf(stderr, "memory allocation failed\n");
        return -1;
    }
    
    while (num_elements < MAX_INPUT) {
        if (scanf("%d", &array_element) != 1)
            break; 
        source_array[num_elements]=array_element;
        num_elements++;
    }
    
    if(num_elements>10000000){
        printf("The input is too big\n");
        return 0;
    }

    for(int i=0;i<4;i++){
        input_array = malloc (sizeof(int) * MAX_INPUT);
        if(input_array==NULL){
            fprintf(stderr, "memory allocation failed\n");
            return -1;
        }
        memcpy(input_array,source_array,num_elements*sizeof(int));
        if(i==0){
            q_sort_first(input_array, num_elements,sizeof(int), compar);
            printf("First: %lld \n",first_comparision);
            free(input_array);
        }
        else if(i==1){
            q_sort_last(input_array, num_elements,sizeof(int), compar);
            printf("Last: %lld \n",last_comparision);
            free(input_array);
        }
        
        else if(i==2){
            //this is for running random sorting 10 times.
            long long int total_comp_rand=0;
            for(int i=0;i<10;i++)
            {
                memcpy(input_array,source_array,num_elements*sizeof(int));
                q_sort_random(input_array,num_elements,sizeof(int),compar);
                total_comp_rand+=random_comparision;
                random_comparision=0;
            }
            free(input_array);
            long long int average_rand = total_comp_rand/10;
            printf("Random: %lld\n",average_rand);
        }
        else{
            q_sort_median(input_array, num_elements,sizeof(int), compar);
            printf("Median-of-three: %lld \n",median_comparision);
            free(input_array);
        }
    }
    
    return 0;
}