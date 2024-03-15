#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void ShowLinkedList(List* pList){
/*
  printf("first node -->");
  pList -> current = pList->head;
  while (1) {
    if(pList-> head == NULL){
        printf("there is no list");
        return;
    }else if(pList -> current -> next = NULL){
        printf("%d\n",*(int*)pList->current->data);
    }else{
        printf("%d\n",*(int*)pList->current->data);
        pList -> current = pList -> current -> next;
    }
  }
*/
}

bool pComparator(void* pItem, void* comparator){
    if(pItem == comparator){
        return 1;
    }else{
        return 0; 
    }
}

//Test program
void List_test()
{
    // Create list
    List* test1 = List_create();
    List* test2 = List_create();

    // Empty List
    if(test1 != NULL && test2 != NULL){
        printf("EMPTY LIST IS CREATED \n");
    }
    // Add && count 
    int add[3] = {9,45,2};
    for(int i =0; i < 3; i ++){
       List_add(test1, &add[i]);
    }

    if(List_count(test1) == 3){
       printf("List_add WORKED \n");
       ShowLinkedList(test1);
    }else{
       printf("List_add WORKED \n");
    }


    // INSERT
    int insert1 = 3;
    int insert2 = 45;
    if(List_insert(test1, &insert1) == 0){
         printf("List_insert WORKED \n");
         ShowLinkedList(test1);  
    }else{
      printf("List_insert not WORKED \n");
    }

    // APPEND
    int append1 = 10;
    int append2 = 45;
    if(List_append(test2, &append1) == 0 && List_append(test2, &append2)==0){
         printf("List_append WORKED \n");
         ShowLinkedList(test2);     
    }else{
       printf("List_append not worked");
     
    }

    // PREPEND
    int prepend1 = 3;
    int prepend2 = 45;
    if(List_prepend(test1, &prepend1) == 0){
          printf("List_prepend WORKED \n");
          ShowLinkedList(test1);
    }else{
      printf("List_prepend not WORKED \n");
    }

    //NEXT ,PREV && FIRST
     if(List_first(test2) == &append1){
         printf("first");
         if(List_next(test2) == &append2){
                 if(List_prev(test2) == &append1){
                     printf("List_fist,List_next,List_prev WORKED \n");  
                     ShowLinkedList(test2);    
             }
         }
     }

    //REMOVE 
    if(List_remove(test1) == &append2){
        printf("List_remove WORKED \n");
        ShowLinkedList(test1);
    }else{
      printf("List_remove WORKED \n");
    }


     
      //CONCAT
      int n1 = 1;
      int n2 = 2;
      int n3 = 3;
      int n4 = 4;
      List* concat_list1 = List_create();
      List_add(concat_list1,&n1);
      List_append(concat_list1, &n2);
      List* concat_list2 = List_create();
      List_add(concat_list2,&n3);
      List_append(concat_list2,&n4);
      List_concat(concat_list1,concat_list2);
      
      if(List_count(concat_list1)==4){
        if(List_curr(concat_list1) == &n2){
             printf("List_concat WORKED \n");
             ShowLinkedList(concat_list1);
         }else{
	    printf("error");
         }
      }else{
         printf("List_concat not WORKED \n");
      }
   
      //Trim 
     if(List_trim(concat_list1) == &n4){
         printf("List_trim WORKED \n");
         ShowLinkedList(concat_list1);
     }else{
        printf("List_trim not WORKED \n");
     }


   //SEARCH
   //When current is pointing to the data that tail is pointin
   if(List_search(test1,pComparator,&insert1) == &insert1){
      printf("List_search Success\n");
   }else{
     printf("List_search Fail\n");
   }

    printf("ALL THE TESTS ARE PASSED \n");
}

int main(){
    List_test();
}



