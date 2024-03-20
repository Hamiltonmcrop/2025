// List data type
// You may modify this file as needed; however,
// you may *NOT* modify the function prototypes or constant names.

#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>

#define LIST_SUCCESS 0
#define LIST_FAIL -1

#define PCB_SUCCESS 0
#define PCB_FAIL -1

extern int end;

enum ProcessPriority {
    HIGH,
    NORM,
    LOW
};

enum ProcessState {
    RUNNING,
    READY,
    BLOCKED
};

enum MsgType {
    SEND,
    REPLY,
};

typedef struct PCB_s PCB;
struct PCB_s {
    
    int pid;
    int position;
    PCB *prev;
    PCB *next;
    int priority;
    //enum ProcessPriority priority;
    enum ProcessState state;
    char * procMsg;
};


typedef struct Message_s Message;
struct Message_s {
    int position;
    int pid;
    int from;
    char * msg;
    //char msg[100];
    enum MsgType type;
    Message *prev;
    Message *next;
};


enum ListOutOfBounds {
    LIST_OOB_START,
    LIST_OOB_END
};
typedef struct List_s List;
struct List_s{
    // TODO: You should change this!
    int index;
    int item_count;
    PCB *head;
    PCB *tail;
    PCB *current;
    enum ListOutOfBounds list_state;
};


typedef struct Msg_List_s MsgList;
struct Msg_List_s{
    // TODO: You should change this!
    int index;
    int item_count;
    Message *head;
    Message *tail;
    Message *current;
    enum ListOutOfBounds list_state;
};


typedef struct Semaphore_s Semaphore;
struct Semaphore_s {
    
    int value;
    int sid;
    List* blocked_processes;
};


/*
typedef struct Node_s Node;
struct Node_s {
    // TODO: You should change this
    void* item;
    int position;
    Node *prev;
    Node *next;
};*/



// Maximum number of unique lists the system can support
// (You may modify for your needs) should be 10
#define LIST_MAX_NUM_HEADS 100

// Maximum total number of nodes (statically allocated) to be shared across all lists
// (You may modify for your needs)
#define LIST_MAX_NUM_NODES 1000

// General Error Handling:
// Client code is assumed never to call these functions with a NULL List pointer, or 
// bad List pointer. If it does, any behaviour is permitted (such as crashing).
// HINT: Use assert(pList != NULL); just to add a nice check, but not required.

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure. O(N)
List* List_create();
MsgList* MsgList_create();

// Returns the number of items in pList.
int List_count(List* pList);
int MsgList_count(MsgList* pList);

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
PCB* List_first(List* pList);
Message* MsgList_first(MsgList* pList);

// Returns a pointer to the current item in pList.
void* List_curr(List* pList);
void* MsgList_curr(MsgList* pList);

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_add(List* pList, int pItem);

int List_append(List* pList, PCB* pItem);
int MsgList_append(MsgList* pList, Message* pItem);


// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the  of the pList,
// then do not change the pList and return NULL.
PCB* List_remove(List* pList);
Message* MsgList_remove(MsgList* pList);


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
// the first node in the list (if any). O(N)
typedef bool (*COMPARATOR_FN)(int pItem, int pComparisonArg);
PCB* List_search(List* pList, COMPARATOR_FN pComparator, int pComparisonArg);
Message* MsgList_search(MsgList* pList, COMPARATOR_FN pComparator, int pComparisonArg);


PCB* initial_create(void);

// Create a PCB (process)
int PCB_create(int priority);

bool compare_test(int x, int y);

void cpu_schudule(PCB* process);

void cpu_schudule_priority();

void cpu_print();

void getMessageAndPrint();

void removeMessageAndReply(int pid);

int PCB_fork(void);

int PCB_kill(int pid); // Use ptr_compare

int PCB_exit(void);

int PCB_quantum(void);

int PCB_send(int pid, char * msg);

int PCB_receive();

int PCB_reply(int pid, char * msg);

int SEM_new(int sid, int value);

int P(int sid);

int V(int sid);

void display_message(int pid);

int PCB_Procinfo(int pid);

void Totalinfo();

void List_print(List* pList);
void MsgList_print(MsgList* pList);

#endif
