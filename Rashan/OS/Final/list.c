
#include<stdbool.h>
#include<stdio.h>
#include <assert.h>
#include "list.h"

static List ListArray[LIST_MAX_NUM_HEADS];
static Node NodeArray[LIST_MAX_NUM_NODES];
static int TotalListCount=0;
static int TotalNodeCount=0;

List* List_create(){
 // check the number of the list 
 if(TotalListCount < LIST_MAX_NUM_HEADS-1){   
   List* list = &ListArray[TotalListCount];
   list->head = NULL;
   list->tail = NULL;
   TotalListCount ++;	 
   return list; 
  } 
  else {
    return NULL;
  }
} 

void* List_first(List* pList){
 if(pList->head == NULL){
   pList-> current = NULL;
 }else{
  pList -> current = pList -> head;
 }
  pList -> checkBounds =0;
  return pList -> current -> data;
}

void* List_last(List* pList){
  pList -> checkBounds = 0;
  if(pList->head == NULL){
     pList -> current = NULL;
  }else{
    pList -> current = pList-> tail;
  }
 return pList -> current -> data;
}

int List_count(List* pList){
 assert(pList != NULL);
 return pList->count;
}

void* List_next(List* pList){
  if(pList->tail == pList->current){
    pList->current = NULL;
    pList->checkBounds = 1;
    return NULL;
  }
  pList->checkBounds = 0;
  pList->current = pList->current->next;
  void* returndata = pList->current->data;
  return returndata;
}

void* List_prev(List* pList){
  if(pList->head == pList->current){
    pList->current = NULL;
    pList->checkBounds = -1;
    return NULL;
  }
  pList->checkBounds = 0;
  pList->current = pList->current->prev;
  void* returndata = pList->current->data;
  return returndata;
}

void* List_curr(List* pList){
  if(pList->current == NULL){
    return NULL;
  }
  return pList->current->data;
}

int List_add(List* pList, void* pItem){

  if(TotalNodeCount >= LIST_MAX_NUM_NODES){
     return -1;
  }
  Node* newNode = &NodeArray[TotalNodeCount];
  if(pList-> head == NULL){
  	pList -> head = newNode;
    pList -> tail = newNode;
    pList -> head -> data = pItem;
    pList -> head -> prev = NULL;
    pList -> head -> next = NULL;
    pList -> current = newNode;
    pList->count++;
    TotalNodeCount++;
    return 0;
   }
  else{
    if(pList->checkBounds == -1 ){
      pList->head-> prev = newNode;
      newNode->next = pList-> head;
      newNode->prev = NULL;
      newNode->data = pItem;
      pList -> current = newNode;
      pList -> head = newNode;
      pList->count++;
      TotalNodeCount++; 
      return 0; 
    }else if(pList->checkBounds == 1){
      pList -> tail -> next = newNode;
      newNode -> prev = pList-> tail;
      newNode -> next = NULL;
      newNode -> data = pItem;
      pList -> current = newNode;
      pList -> tail = newNode;
      pList->count++;
      TotalNodeCount++;
      return 0;
    }else{
      if(pList-> tail == pList -> current)
      { pList -> tail = newNode; }
      else{
        pList -> current -> next -> prev = newNode;
      }
      newNode -> data = pItem; 
      newNode -> next = pList -> current-> next;
      newNode -> prev = pList -> current;
      pList -> current -> next = newNode;
      pList -> current = newNode;
      pList->count++;
      TotalNodeCount++;
      return 0;
    } 
  } 
  return -1;
}

int List_insert(List* pList, void* pItem){
  Node* newNode = &NodeArray[TotalNodeCount];
  if(pList-> head == NULL){
    pList -> head = newNode;
    pList -> tail = newNode;
    pList -> head -> data = pItem;
    pList -> head -> prev = NULL;
    pList -> head -> next = NULL;
    pList -> current = newNode;
    pList->count++;
    TotalNodeCount++;
    return 0;
   }else{
    if(pList->checkBounds == -1 ){
      pList->head-> prev = newNode;
      newNode->next = pList-> head;
      newNode->prev = NULL;
      newNode->data = pItem;
      pList -> current = newNode;
      pList -> head = newNode;
      pList->count++;
      TotalNodeCount++;  
      return 0;
    }else if(pList->checkBounds == 1){
      pList -> tail -> next = newNode;
      newNode -> prev = pList-> tail;
      newNode -> next = NULL;
      newNode -> data = pItem;
      pList -> current = newNode;
      pList -> tail = newNode;
      pList->count++;
      TotalNodeCount++;
      return 0;
    }else{
      if(pList-> head == pList -> current) {
          pList -> head = newNode;
      }
      else{
        pList -> current -> prev -> next = newNode;
      }
      newNode -> data = pItem; 
      newNode -> next = pList -> current;
      newNode -> prev = pList -> current-> prev;
      pList -> current -> prev = newNode;
      pList -> current = newNode;
      pList->count++;
      TotalNodeCount++;
      return 0;
    } 
   }
  return -1;
}

void* List_remove(List* pList){
 if(pList-> checkBounds == -1 || pList -> checkBounds == 1){
    return NULL;
 }else{
  Node* removedItem = pList -> current -> data;
  //check if there is one node
  pList -> current = pList -> tail;
  if(pList -> current == pList -> head){
    pList -> head = pList -> current -> next;
    pList -> current -> next -> prev = NULL;
    pList -> count--; // main CHECK
    pList -> current -> data = NULL;
    pList -> current = pList -> head;
    return removedItem;    
  }else if(pList -> current == pList -> tail){
    pList -> tail = pList -> current -> prev;
    pList -> current -> prev -> next = NULL;
    pList -> count--;
    pList -> current -> data = NULL;
    pList -> current = pList -> tail;
    return removedItem;
  }else{
    pList -> current -> prev -> next = pList -> current -> next;
    pList -> current -> next -> prev = pList -> current -> prev;
    pList -> count--;
    pList -> current -> data = NULL;
    pList -> current = pList -> current -> next;
    return removedItem;
    }   
    return removedItem;
  }
}

int List_append(List* pList, void* pItem){
    Node* newNode = &NodeArray[TotalNodeCount];
    if(pList->head==NULL){
    pList->head = newNode;
    pList->tail = newNode;
    pList->current = newNode;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = pItem;
    pList->count++;
    TotalNodeCount++;  
    return 0;
  }
  else{
   // Node* newNode = &NodeArray[TotalNodeCount];
    newNode->next = pList->current->next;
    pList->current->next = newNode;
    newNode->prev = pList->current;
    newNode->data = pItem;
    pList->tail = newNode;
    pList->current = newNode;
    pList->count++;
    TotalNodeCount++;
    return 0;
  }
  return -1;
}     

int List_prepend(List* pList, void* pItem){
 Node* newNode = &NodeArray[TotalNodeCount]; 
 if(pList->head==NULL){
    //Node* newNode = &NodeArray[0];
    pList->head = newNode;
    pList->tail = newNode;
    pList->current = newNode;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = pItem;
    pList->count++;
    TotalNodeCount++;
    return 0;
  }
  else{
    //Node* newNode = &NodeArray[TotalNodeCount];
    newNode->prev = pList->current->prev;
    pList->current->prev = newNode;
    newNode->next = pList->current;
    newNode->data = pItem;
    pList->current = newNode;
    pList->head = newNode;
    pList->count++;
    TotalNodeCount++;
    return 0;
  }
  return -1;
} 

void List_free(List* pList, FREE_FN pItemFreeFn){
  assert(pList != NULL);
  List_first(pList);
  if(pList->current->data != NULL){
    void* item = pList->current->data;
    List_remove(pList);
    pItemFreeFn(item);
  }
  pList->head = NULL;
  pList->tail = NULL;
  pList->current = NULL;
  pList->checkBounds = 0;
  pList->count = 0;
}

void* List_trim(List* pList){
  assert(pList != NULL);
  List_last(pList);
  void* item = List_remove(pList);
  //List_prev(pList);
  return item;
}

void List_concat(List* pList1, List* pList2){
  int cnt1 = pList1 -> count;
  int cnt2 = pList2 -> count;
  if(cnt1+cnt2 <= LIST_MAX_NUM_NODES){
     if(pList1 -> head == NULL){
       pList1 -> head = pList2 -> head;
       pList1 -> tail = pList2 -> tail;
     }
     else{ 
      pList1 -> tail -> next = pList2 -> head;
      pList1 -> tail -> next -> prev = pList1 -> tail;
      pList1 -> tail = pList2 -> tail;
    }
      pList2 -> head = NULL;
      pList2 -> tail = NULL;
      pList2 -> current = NULL;
      pList2 -> checkBounds = 0;
      pList1 -> count = cnt1 + cnt2;
  }  
}

void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
  if(pList-> checkBounds == 1 || pList -> checkBounds == -1){
    pList -> current = pList -> head;
    }
  if(pComparator(List_curr(pList), pComparisonArg) == 1){
    return pList -> current-> data;
  }else{
    while(List_next(pList) != NULL){
      if(pComparator(List_next(pList), pComparisonArg) == 1){
          pList -> current = List_next(pList);
          return pList -> current-> data;
      }
    } 
  pList -> checkBounds = 1;
  return NULL; 
  }
} 



