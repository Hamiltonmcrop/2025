#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void ShowLinkedList(List* pList) {
  printf("first node->");
  Node* node = pList->head;
  while (node != NULL) {
    if (node == pList->current) {
      printf("node: %d \n", *(int*)node->data);
    }
    else {
      printf("node: %d \n", *(int*)node->data);
    }
    node = node->next;
  }
  printf(" <-last node\n");
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
    List* test3 = List_create();
    List* test4 = List_create();
    List* test5 = List_create();
    List* test6 = List_create();

    // Empty List
    if(test1 != NULL){
        if(test2 != NULL){
            if(test3 != NULL){
                if(test4 != NULL){
                    if(test5 != NULL){
                        if(test6 != NULL){
                            printf("EMPTY LIST IS CREATED \n");
                        }
                    }
                }
            }
        }
    }
     // Add 
    int add1 = 3;
    int add2 = 45;
    int add3 = 23;
    int add4 = 9;
    int add5 = 0;
        if(List_add(test1, &add1) == 0){
            if(List_add(test1, &add2) == 0){
                if(List_add(test1, &add3) == 0){
                    if(List_add(test1, &add4) == 0){
                        //if(List_add(test1,&add5) == -1){
                        printf("List_add WORKED \n");
                        ShowLinkedList(test1);
                       // }
                    
                }
            }
        }
    }
    
    // INSERT
    int insert1 = 3;
    int insert2 = 45;
    int insert3 = 23;
    int insert4 = 9;
    int insert5 = 0;
    if(List_insert(test2, &insert1) == 0){
        if(List_insert(test2, &insert2) == 0){
            if(List_insert(test2, &insert3) == 0){
                if(List_insert(test2, &insert4) == 0){
                    printf("List_insert WORKED \n");
                    ShowLinkedList(test2);
                }
            }
        }
    }

    // APPEND
    int append1 = 3;
    int append2 = 45;
    int append3 = 23;
    int append4 = 9;
    //int append5 = 0;
    if(List_append(test3, &append1) == 0){
        if(List_append(test3, &append2) == 0){
            if(List_append(test3, &append3) == 0){
                if(List_append(test3, &append4) == 0){
                        printf("List_append WORKED \n");
                        ShowLinkedList(test3);
                }
            }
        }
    }

    //printf("list remove %p",List_remove(test3));

    // int a = 3;
    // List* list = List_create();
    // List_add(list,&a);
    // if(List_remove(test3) == &append4){
    //     printf("SUUCCC\n");
    // }else{
    //     printf("append add %p",&append4);
    //     printf("remove add %p",List_remove(test3));
    //     printf("fail");
    // }

    // PREPEND
    int prepend1 = 3;
    int prepend2 = 45;
    int prepend3 = 23;
    int prepend4 = 9;
    if(List_prepend(test4, &prepend1) == 0){
        if(List_prepend(test4, &prepend2) == 0){
            if(List_prepend(test4, &prepend3) == 0){
                if(List_prepend(test4, &prepend4) == 0){
                        printf("List_prepend WORKED \n");
                        ShowLinkedList(test4);
                }
            }
        }
    }

    //NEXT and PREV
    // int t1 = 3;
    // int t2 = 45;
    // List* list = List_create();
    // List_add(list,&t1);
    // printf("LIST FIRST %p",List_first(list));
    // printf("LIST t1 %p",&t1);
    // if(List_first(list) == &t1){
    //      printf("List_first WORKED %p",List_first(list));
    // }
   

    // if(List_first(test6) == &a){
    //     printf("first");
    //     if(List_next(test6) == &b){
    //             if(List_prev(test6) == &a){
    //                 printf("List_fist,List_next,List_prev WORKED \n");  
    //                 ShowLinkedList(test6);    
    //         }
    //     }
    // }

    //REMOVE 
    if(List_remove(test3) == &append4){
        printf("List_remove WORKED \n");
        ShowLinkedList(test3);
    }


//    //Trim 
//    int c = 4;
//    int d =7;
//    List_add(test6,&c);
//    List_append(test6,&d);
//    if(List_trim(test6)==&d){
//        printf("List_trim WORKED \n");
//        ShowLinkedList(test6);
//    }

//    //CONCAT
   int n1 = 1;
   int n2 = 2;
   int n3 = 3;
   int n4 = 4;
   List* concat_list1 = List_create();
   List_add(concat_list1,&n1);
   List_append(concat_list1, &n2);
   List* concat_list2 = List_create();
   List_add(concat_list2,&n3);
   //List_append(concat_list2,&n4);
   List_concat(concat_list1,concat_list2);
   if(List_count(concat_list1)==4){
       if(List_last(concat_list1) == &n4){
           printf("List_concat WORKED \n");
           ShowLinkedList(concat_list1);
       }
   }
   

   //SEARCH
   //When current is pointing to the data that tail is pointin
   if(List_search(test1,pComparator,&add4) == &add4){
      printf("List_search Success\n");
   }else{
     printf("List_search Fail\n");
   }

    printf("ALL THE TESTS ARE PASSED \n");
}

int main(){
    List_test();
}



