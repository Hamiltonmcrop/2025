#include "list.h"
#include <stdio.h>


static Node node[LIST_MAX_NUM_NODES];
static List list[LIST_MAX_NUM_HEADS];
static int free_node[LIST_MAX_NUM_NODES];
static int free_list[LIST_MAX_NUM_HEADS];
static int node_pool_used = 0;
static int list_pool_used = 0;
static int count = 0;

static  void populate_free_node(){
    int i = 0;
    while(i<LIST_MAX_NUM_NODES){
        free_node[i] = i;
        i++;
    }
    return;
}
static void populate_free_list(){
    int i = 0;
    while(i<LIST_MAX_NUM_HEADS){
        free_list[i] = i;
        i++;
    }
    return;
}


List* List_create(){
    if(count == 0){
        populate_free_node();
        populate_free_list();
        count++;
    }
    if(list_pool_used < LIST_MAX_NUM_HEADS){
        list_pool_used++;
        List* newlist = &list[free_list[0]];
        newlist->pool_index = free_list[0];
        free_list[0] = free_list[LIST_MAX_NUM_HEADS - list_pool_used];
        free_list[LIST_MAX_NUM_HEADS - list_pool_used] = -1;
        newlist->head = NULL;
        newlist->tail = NULL;
        newlist->current = NULL;
        newlist->before_start = true;
        newlist->after_end = false;
        newlist->length = 0;
        return newlist;
    }
    return NULL;
}

static void List_reuse(List* list){
    if(list == NULL){
        return;
    }
    if(list->length == 0){
        free_list[LIST_MAX_NUM_HEADS - list_pool_used] = list->pool_index;
        list_pool_used--;
        return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->before_start = true;
    list->after_end = false;
    list->length = 0;
    free_list[LIST_MAX_NUM_HEADS - list_pool_used] = list->pool_index;
    list_pool_used--;
    return;
}

static Node* Node_create(){
    if(node_pool_used < LIST_MAX_NUM_NODES){
        node_pool_used++;
        Node* newnode = &node[free_node[0]];
        newnode->pool_index = free_node[0];
        free_node[0] = free_node[LIST_MAX_NUM_NODES - node_pool_used];
        free_node[LIST_MAX_NUM_NODES - node_pool_used] = -1;
        newnode->item = NULL;
        newnode->next = NULL;
        newnode->previous = NULL;
        return newnode;
    }
    return NULL;
}

static void Node_reuse(Node* node){
    if(node == NULL){
        return;
    }
    node->item = NULL;
    node->next = NULL;
    node->previous = NULL;
    free_node[LIST_MAX_NUM_NODES - node_pool_used] = node->pool_index;
    node_pool_used--;

}

int List_count(List* pList){
    return pList->length;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(pList->length <= 0){
        return NULL;
    }
    pList->current = pList->head;
    pList->after_end = false;
    pList->before_start = false;
    return pList->current->item;
}

void* List_last(List* pList){
    if(pList->length <= 0){
        return NULL;
    }
    pList->current = pList->tail;
    pList->after_end = false;
    pList->before_start = false;
    return pList->current->item;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){

    if(pList->length <= 0){
        return NULL;
    }

    if(pList->before_start){
        pList->current = pList->head;
        pList->before_start = false;
        return pList->current->item;
    }

    if(pList->current == pList->tail || pList->after_end){
        pList->current = NULL;
        pList->after_end = true;
        return NULL;
    }

    pList->current = pList->current->next; 
    return pList->current->item;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    //printf("hello");
    if(pList->length <= 0){
        //printf("hello1");
        return NULL;
    }

    if(pList->after_end){
        //printf("hello2");
        pList->current = pList->tail;
        pList->after_end = false;
        return pList->current->item;
    }

    if(pList->current == pList->head || pList->before_start){
        //printf("hello3");
        pList->current = NULL;
        pList->before_start = true;
        return NULL;
    }
    //printf("hello4");
    pList->current = pList->current->previous;
    return pList->current->item;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){

    if(pList->length <= 0 || pList->current == NULL){
        return NULL;
    }

    return pList->current->item;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.

int List_add(List* pList, void* pItem){

    if(pList == NULL || pItem == NULL){
        return LIST_FAIL;
    }

    Node* newnode = Node_create();
    if(newnode == NULL){
        return LIST_FAIL;
    }
    newnode->item = pItem;
    if(pList->length <= 0){
        newnode->next = NULL;
        newnode->previous = NULL;
        pList->length++;
        pList->head = newnode;
        pList->tail = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }

    if(pList->before_start){
        pList->length++;
        newnode->previous = NULL;
        newnode->next = pList->head;
        newnode->next->previous = newnode;
        pList->head = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }

    if(pList->after_end || pList->current == pList->tail){
        pList->length++;
        newnode->previous = pList->tail;
        newnode->next = NULL;
        newnode->previous->next = newnode;
        pList->tail = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }

    newnode->next = pList->current->next;
    newnode->previous = pList->current;
    pList->length++;
    pList->current->next = newnode;
    newnode->next->previous = newnode;
    pList->current = newnode;
    pList->before_start = false;
    pList->after_end = false;
    return LIST_SUCCESS;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem){
    if(pList == NULL || pItem == NULL){
        return LIST_FAIL;
    }

    Node* newnode = Node_create();
    if(newnode == NULL){
        return LIST_FAIL;
    }
    newnode->item = pItem;
    if(pList->length <= 0){
        newnode->next = NULL;
        newnode->previous = NULL;
        pList->length++;
        pList->head = newnode;
        pList->tail = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }

    if(pList->before_start || pList->current == pList->head){
        pList->length++;
        newnode->previous = NULL;
        newnode->next = pList->head;
        newnode->next->previous = newnode;
        pList->head = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }

    if(pList->after_end){
        pList->length++;
        newnode->previous = pList->tail;
        newnode->next = NULL;
        newnode->previous->next = newnode;
        pList->tail = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }

    newnode->previous = pList->current->previous;
    newnode->next = pList->current;
    pList->length++;
    pList->current->previous = newnode;
    newnode->previous->next = newnode;
    pList->current = newnode;
    pList->before_start = false;
    pList->after_end = false;
    return LIST_SUCCESS;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    if(pList == NULL || pItem == NULL){
        return LIST_FAIL;
    }

    Node* newnode = Node_create();
    if(newnode == NULL){
        return LIST_FAIL;
    }
    newnode->item = pItem;
    if(pList->length <= 0){
        newnode->next = NULL;
        newnode->previous = NULL;
        pList->length++;
        pList->head = newnode;
        pList->tail = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }
    pList->length++;
    newnode->previous = pList->tail;
    newnode->next = NULL;
    newnode->previous->next = newnode;
    pList->tail = newnode;
    pList->current = newnode;
    pList->before_start = false;
    pList->after_end = false;
    return LIST_SUCCESS;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    if(pList == NULL || pItem == NULL){
        return LIST_FAIL;
    }

    Node* newnode = Node_create();
    if(newnode == NULL){
        return LIST_FAIL;
    }
    newnode->item = pItem;
    if(pList->length <= 0){
        newnode->next = NULL;
        newnode->previous = NULL;
        pList->length++;
        pList->head = newnode;
        pList->tail = newnode;
        pList->current = newnode;
        pList->before_start = false;
        pList->after_end = false;
        return LIST_SUCCESS;
    }
    pList->length++;
    newnode->previous = NULL;
    newnode->next = pList->head;
    newnode->next->previous = newnode;
    pList->head = newnode;
    pList->current = newnode;
    pList->before_start = false;
    pList->after_end = false;
    return LIST_SUCCESS;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    if(pList == NULL){
        return NULL;
    }
    if(pList->current == NULL){
        return NULL;
    }
    if(pList->length == 1){
        Node* remove = pList->current;
        void* result = remove->item;
        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
        pList->after_end = true;
        pList->length--;
        Node_reuse(remove);
        return result;
    }
    if(pList->current == pList->tail){
        Node* remove = pList->current;
        remove->previous->next = NULL;
        pList->current = NULL;
        pList->after_end = true;
        pList->tail = remove->previous;
        pList->length--;
        void* result = remove->item;
        Node_reuse(remove);
        return result;
    }
    if(pList->current == pList->head){
        Node* remove = pList->current;
        remove->next->previous = NULL;
        pList->head  = remove->next;
        pList->current = remove->next;
        pList->length--;
        void* result = remove->item;
        Node_reuse(remove);
        return result;
    }

    Node* remove = pList->current;
    remove->previous->next = remove->next;
    remove->next->previous = remove->previous;
    pList->current = remove->next;
    pList->length--;
    void* result = remove->item;
    Node_reuse(remove);
    return result;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if(pList == NULL){
        return NULL;
    }
    if(pList->length <= 0){
        return NULL;
    }
    if(pList->length == 1){
        Node* remove = pList->tail;
        void* result = remove->item;
        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
        pList->before_start = true;
        pList->length--;
        Node_reuse(remove);
        return result;
    }
    
    Node* remove = pList->tail;
    remove->previous->next = NULL;
    pList->current = remove->previous;
    pList->tail = remove->previous;
    pList->length--;
    void* result = remove->item;
    Node_reuse(remove);
    return result;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    if(pList1 == NULL || pList2 == NULL){
        return;
    }
    if(pList2->length == 0){
        List_reuse(pList2);
        pList2 = NULL;
        return;
    }
    if(pList1->length == 0){
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
        pList1->length = pList2->length;
        List_reuse(pList2);
        pList2 = NULL;
        return;
    }
    pList1->tail->next = pList2->head;
    pList2->head->previous = pList1->tail;
    pList1->tail = pList2->tail;
    pList1->length = pList1->length + pList2->length;
    List_reuse(pList2);
    pList2 = NULL;
    return;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn){
    if (pList == NULL)
    {
        return;
    }

    if(pList->length == 0){
        List_reuse(pList);
        pList = NULL;
        return;
    }

    pList->current = pList->head;
    while (pList->current != NULL){
        (*pItemFreeFn)(pList->current->item);
        List_remove(pList);
    }
    List_reuse(pList);
    pList = NULL;
    return;
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    if(pList == NULL || pList->after_end){
        return NULL;
    }
    if(pList->before_start){
        pList->current = pList->head;
    }
    while (pList->current != NULL){
        if(pComparator(pList->current->item, pComparisonArg)){
            return pList->current->item;
        }
        pList->current = pList->current->next;
    }
    pList->after_end = true;
    return NULL;
}