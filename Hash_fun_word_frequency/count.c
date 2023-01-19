#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#define MAX_LINE 4096
#define MAX_WORD 1024
#define HASH_MULTIPLIER 65599
enum {OUTSIDE, INSIDE};

unsigned int max_hash_length = 1024;
unsigned int num_elements =0;
int flag=0;
/*a struct to keep track of the key and its frequency as well
as the structs that are used for a linked list in case of collision*/

struct hash_table_data{
    char *key;
    int frequency;
    struct hash_table_data *next;

};
typedef struct hash_table_data hashD;

/*THIS is used to point to the hash table that stores words and their frequencies*/
struct hash_table{
    hashD **table_ptr;
};

typedef struct hash_table *Ht;

/* Return a hash code for pcKey that is between 0,
  inclusive. Adapted from the EE209 lecture notes. */
unsigned int hash_function(const char *pcKey)
{
  int i;
  unsigned int uiHash = 0U;
  for (i = 0; pcKey[i] != '\0'; i++)
    uiHash = uiHash * (unsigned int)HASH_MULTIPLIER
          + (unsigned int)pcKey[i];
  return uiHash;
}
/*This function creates a hash table*/
Ht create_hash_table(void){
    Ht tableptr = (Ht) calloc(1, sizeof(Ht));
    if (tableptr == NULL) {
    fprintf(stderr, "Can't allocate a memory for tableptr\n");
    return NULL;
  }
    tableptr->table_ptr = (hashD **)calloc(max_hash_length,sizeof(hashD *));
    if (tableptr->table_ptr == NULL) {
    fprintf(stderr, "Can't allocate a memory for tableptr->table_ptr\n");
    return NULL;
  }
    return tableptr;
}

void freeTable(hashD *slot){
  while(slot!=NULL){
    free(slot->key);
    slot = slot->next;
  }
}
/*A supporting function that adds nodes to the hash table
used both when rehashing and just normal adding of nodes*/
void add_to_table(Ht HtableR,char *key){
    unsigned int hash_code = hash_function(key);
    unsigned int index = hash_code % max_hash_length;
    hashD *Nodecurr = HtableR->table_ptr[index];
    while(Nodecurr!=NULL){
        if((strcmp(key,Nodecurr->key))==0 ){
            Nodecurr->frequency+=1;
            return;
        }
        Nodecurr = Nodecurr->next;
    }
    hashD *Node = (hashD *) calloc(1,sizeof(hashD));
    if(Node==NULL){
        fprintf(stderr, "Can't allocate a memory Node \n");
    }

    Node->next = HtableR->table_ptr[index];

    Node->key = (char *)malloc(strlen(key)+1);
    if(Node->key==NULL){
        fprintf(stderr,"memroy not allocated to the key\n");
    }
    strcpy(Node->key,key);
    Node->frequency = 1; // how do i know if it's the last,b/c if it's not, then need to make +=1
    if(flag!=1) num_elements+=1; // if we are rehashing, then no need to increment
    HtableR->table_ptr[index] = Node;
}

/*This function doubles the hashTable size when the old hashTable is
75% full. */

void resize(int new_array_size,int old_array_size,Ht HashTable){
    // printf("inside of resize at very begginning \n");
    int jj=0;
    hashD ** old_table;
    old_table = HashTable->table_ptr;
    HashTable->table_ptr = (hashD **)calloc(new_array_size,sizeof(hashD *));
    if (HashTable->table_ptr == NULL) {
    fprintf(stderr, "Can't allocate a memory for the new hash table\n");
  }
    flag=1;
    hashD *start;
    // printf("right before looping old array at resize\n");
    for(int i=0;i<old_array_size;i++){
        start = old_table[i];
        // printf("inside the for loop \n");
        while(start!=NULL){
            // printf("inside the while loop 3******************** \n");
            // add_to_table(HashTable,start->key);

            unsigned int hash_code = hash_function(start->key);
            unsigned int index = hash_code % max_hash_length;
            hashD *Nodecurr = HashTable->table_ptr[index];
            while(Nodecurr!=NULL){
                if((strcmp(start->key,Nodecurr->key))==0 ){
                    Nodecurr->frequency+=1;
                    jj=1;
                    break;
                    // return;
                }
                Nodecurr = Nodecurr->next;
            }
            if(jj==0){
                hashD *Node = (hashD *) calloc(1,sizeof(hashD));
            if(Node==NULL){
                fprintf(stderr, "Can't allocate a memory Node \n");
            }

            Node->next = HashTable->table_ptr[index];

            Node->key = (char *)malloc(strlen(start->key)+1);
            if(Node->key==NULL){
                fprintf(stderr,"memroy not allocated to the key\n");
            }
            strcpy(Node->key,start->key);
            
            Node->frequency = start->frequency; // how do i know if it's the last,b/c if it's not, then need to make +=1

    
    // Node->frequency = 1; // how do i know if it's the last,b/c if it's not, then need to make +=1
    // if(flag!=1) 
    // num_elements+=1; // if we are rehashing, then no need to increment
    HashTable->table_ptr[index] = Node;
    
    }
    start = start->next;
            




            
        }
        freeTable(old_table[i]);
    }
    // printf("right before freeing the old array size");
    free(old_table);
}
/*inserts a key and its frequency to the given hash Table Htable*/
void insert_tableT(Ht Htable,char *key){
    // printf("IN side of an insert table at very beggining and num_elem and max hsash lngth: %d %d\n",num_elements,max_hash_length);
    if(num_elements >= 0.75*max_hash_length){
        unsigned old_max_hash_length = max_hash_length;
        max_hash_length = 2* max_hash_length;
        // printf("right before resize\n");
        resize(max_hash_length,old_max_hash_length,Htable);
        // printf("It has passed the resizeding function \n");
    }
    flag=0;
    add_to_table(Htable,key);
}




/*prints the elements of the array that was populated from a hashtable*/
void printa(hashD **node_array){
    for(unsigned int i=0;i<num_elements;i++){
        printf("%d %s\n",node_array[i]->frequency,node_array[i]->key);
    }
}

/*This function copies elements of the hash table to an array array_elements that can be passed 
to a quick sort algorithm*/
hashD **array_elements;
void copy_hashData_array(Ht hashTable_Ptr){
    array_elements = (hashD **)malloc(sizeof(hashD *)*num_elements);
    if(array_elements==NULL){
        fprintf(stderr, "not enough memory is allocated!!! \n");
    }
    int indx =0;
    for(unsigned int i=0;i<max_hash_length;i++){
        hashD *ptrTr = hashTable_Ptr->table_ptr[i];  // not sure if this is the right way tho???
        while (ptrTr!=NULL)
        { 
            array_elements[indx]= ptrTr;
            indx++;
            ptrTr = ptrTr->next;
        }
        
    }

}

/*used for comparision*/
int compare(const void *a, const void *b){
        return (*(hashD **)b)->frequency - (*(hashD **)a)->frequency;

}

int main()
{
    double time_spent = 0.0;
    clock_t begin = clock();

	char buf[MAX_LINE], *temp;
	int  i, in_word = OUTSIDE;
	char str[MAX_WORD];
    
    
    Ht hal = create_hash_table();
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		for (temp = buf; *temp; temp++) {
			if (isalpha(*temp)) {
				if (in_word == OUTSIDE) {
					in_word = INSIDE;
					i = 0;
				}
				str[i++] = *temp;
			} else {
				if (in_word == INSIDE) {
					str[i] = 0;
					// printf("%s\n", str);
                    insert_tableT(hal,str);
				}
				in_word = OUTSIDE;
			}
		}
	}
	if (in_word == INSIDE) {
		str[i] = 0;
		// printf("%s\n", str);
        // insert_tableT(hal,str);
	}
    copy_hashData_array(hal);
    qsort(array_elements,num_elements,sizeof(hashD *),compare);
    printa(array_elements);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds \n", time_spent);

	return 0;
}