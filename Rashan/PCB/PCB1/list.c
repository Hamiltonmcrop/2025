#include "list.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static PCB arr_node[LIST_MAX_NUM_NODES];	// Array of 100 struct PCB
static Message arr_msg[LIST_MAX_NUM_NODES];	// Array of 100 struct Message
static List arr_list[LIST_MAX_NUM_HEADS];	// Array of 10 struct Lists
static MsgList arr_msglist[LIST_MAX_NUM_HEADS];	// Array of 10 struct MsgLists

static Semaphore arr_sem[5];

static int node_queue[LIST_MAX_NUM_NODES];	// Circular queue to keep track the position of free nodes in the array
static int msg_queue[LIST_MAX_NUM_NODES];	// Circular queue to keep track the position of free msg in the array
static int list_queue[LIST_MAX_NUM_HEADS];	// Circular queue to keep track the position of of free lists in the array
static int msglist_queue[LIST_MAX_NUM_HEADS];	// Circular queue to keep track the position of of free msg lists in the array

static int node_front = 0, list_front = 0, msg_front = 0, msglist_front = 0;
static int node_rear = -1,  msg_rear = -1;
static int free_node = LIST_MAX_NUM_NODES, free_list = LIST_MAX_NUM_HEADS, free_msg = LIST_MAX_NUM_NODES, free_msglist = LIST_MAX_NUM_HEADS;

static bool called_once = false;	// Flag to check if it's the first time the client's calling List_create()
static bool msg_called_once = false;

static int counter;
static int process_count;
static int semaphore_count;

static List* q_high;
static List* q_norm;
static List* q_low;
static List* q_waitingForReply;
static List* q_waitingToReceive;
static List* q_running;
static List* q_all;
static MsgList* q_messages;
static MsgList* q_replies;

static PCB* init_process;

static bool (*compare_ptr)(int, int);	// Function pointer declaration


void List_print(List* pList) {
	PCB * temp = pList->head;

	while(temp != NULL) {
		//printf("%d ", *(int*)temp->pid);
		printf("%d ", temp->pid);
		temp = temp->next;
	}
	printf("\n");
}


void MsgList_print(MsgList* pList) {
	Message * temp = pList->head;

	while(temp != NULL) {
		//printf("%d ", *(int*)temp->pid);
		printf("%d ", temp->pid);
		temp = temp->next;
	}
	printf("\n");
}


// Helper function using circular queue to put a node back to the node pool
static void node_enqueue(int node_pos){

	// If all the nodes are used
	if(free_node == 0){
		node_front = 0;
		node_rear = 0;
		node_queue[node_rear] = node_pos;
		free_node++;

	// If rear is at the last spot in the queue
	} else if(node_rear == LIST_MAX_NUM_NODES-1 && node_front != 0){
		node_rear = 0;
		node_queue[node_rear] = node_pos;
		free_node++;
	
	}else{
		node_rear++;
		node_queue[node_rear] = node_pos;
		free_node++;
	}
}


// Helper function using circular queue to take a node out from the node pool
static void node_dequeue(){

	node_queue[node_front] = -1;

	if(node_front == LIST_MAX_NUM_NODES-1){
		node_front = 0;
	}else{
		node_front++;
	}

	free_node--;
}


static void msg_enqueue(int node_pos){

	// If all the nodes are used
	if(free_msg == 0){
		msg_front = 0;
		msg_rear = 0;
		msg_queue[msg_rear] = node_pos;
		free_msg++;

	// If rear is at the last spot in the queue
	} else if(msg_rear == LIST_MAX_NUM_NODES-1 && msg_front != 0){
		msg_rear = 0;
		msg_queue[msg_rear] = node_pos;
		free_msg++;
	
	}else{
		msg_rear++;
		msg_queue[msg_rear] = node_pos;
		free_msg++;
	}
}


// Helper function using circular queue to take a node out from the node pool
static void msg_dequeue(){

	msg_queue[msg_front] = -1;

	if(msg_front == LIST_MAX_NUM_NODES-1){
		msg_front = 0;
	}else{
		msg_front++;
	}

	free_msg--;
}



List * List_create(){

	// This O(N) initialization is only called once.
	if(!called_once){
		//printf("first time calling list create\n");

		for(int i = 0; i < LIST_MAX_NUM_NODES; i++){
			node_queue[i] = i;
		}

		for(int j = 0; j < LIST_MAX_NUM_HEADS; j++){
			list_queue[j] = j;
		}

		called_once = true;
	}

	// If all the lists are used
	if(free_list < 1){

		//printf("All the lists are used.\n");
		return NULL;

	}else{

		int list_pos = list_queue[list_front];

		arr_list[list_pos].index = list_pos;
		arr_list[list_pos].item_count = 0;
		arr_list[list_pos].head = NULL;
		arr_list[list_pos].tail = NULL;
		arr_list[list_pos].current = arr_list[list_pos].head;
		arr_list[list_pos].list_state = LIST_OOB_START;

		list_queue[list_front] = -1;

		// Take a list out form the list pool
		if(list_front == LIST_MAX_NUM_HEADS-1){
			list_front = 0;
		}else{
			list_front++;
		}

		free_list--;
		
		//printf("list_front: %d   list_rear: %d\n", list_front, list_rear);
		//printf("list index: %d\n", arr_list[list_pos].index);
		//printf("number of lists left: %d\n", free_list);
		return &arr_list[list_pos];
	}

	return NULL;
}



MsgList * MsgList_create(){

	// This O(N) initialization is only called once.
	if(!msg_called_once){
		//printf("first time calling list create\n");

		for(int i = 0; i < LIST_MAX_NUM_NODES; i++){
			msg_queue[i] = i;
		}

		for(int j = 0; j < LIST_MAX_NUM_HEADS; j++){
			msglist_queue[j] = j;
		}

		msg_called_once = true;
	}

	// If all the lists are used
	if(free_msglist < 1){

		//printf("All the lists are used.\n");
		return NULL;

	}else{

		int msglist_pos = msglist_queue[msglist_front];

		arr_msglist[msglist_pos].index = msglist_pos;
		arr_msglist[msglist_pos].item_count = 0;
		arr_msglist[msglist_pos].head = NULL;
		arr_msglist[msglist_pos].tail = NULL;
		arr_msglist[msglist_pos].current = arr_msglist[msglist_pos].head;
		arr_msglist[msglist_pos].list_state = LIST_OOB_START;

		msglist_queue[msglist_front] = -1;

		// Take a list out form the list pool
		if(msglist_front == LIST_MAX_NUM_HEADS-1){
			msglist_front = 0;
		}else{
			msglist_front++;
		}

		free_msglist--;
		
		//printf("list_front: %d   list_rear: %d\n", msglist_front, msglist_rear);
		//printf("list index: %d\n", arr_msglist[msglist_pos].index);
		//printf("number of lists left: %d\n", free_msglist);
		return &arr_msglist[msglist_pos];
	}

	return NULL;
}


bool compare_test(int x, int y){

	//printf("x: %d  y: %d\n", x, y);

	if(x == y){
		//printf("match found! \n");
		return 1;
	}
	//printf("match not found! \n");
	return 0;
}



int List_count(List* pList){

	assert(pList != NULL);
	return pList->item_count;
}

int MsgList_count(MsgList* pList){

	assert(pList != NULL);
	return pList->item_count;
}


PCB* List_first(List* pList){

	assert(pList != NULL);

	// If the list is empty
	if(pList->item_count == 0){
		//printf("empty list\n");
		pList->current = NULL;
		return NULL;
	}
	
	pList->current = pList->head;	// Make the first item the current item
	pList->list_state = 2;			// Change the list state to inside the list
	//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
	return pList->head;
}


Message* MsgList_first(MsgList* pList){

	assert(pList != NULL);

	// If the list is empty
	if(pList->item_count == 0){
		//printf("empty list\n");
		pList->current = NULL;
		return NULL;
	}
	
	pList->current = pList->head;	// Make the first item the current item
	pList->list_state = 2;			// Change the list state to inside the list
	//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
	return pList->head;
}



void* List_curr(List* pList){

	if(pList->item_count == 0 || pList->list_state == LIST_OOB_START || pList->list_state == LIST_OOB_END){
		return NULL;
	}

	return pList->current;
}


void* MsgList_curr(MsgList* pList){

	if(pList->item_count == 0 || pList->list_state == LIST_OOB_START || pList->list_state == LIST_OOB_END){
		return NULL;
	}

	return pList->current;
}




int List_append(List* pList, PCB* pItem){

	assert(pList != NULL);
	//printf("number of nodes left before inserting: %d\n", free_node);

	// If all the nodes are used
	if(free_node < 1){

		///printf("All the nodes are used.\n");
		return LIST_FAIL;

	}else{

		int node_pos = node_queue[node_front];
		arr_node[node_pos].position = node_pos;
		arr_node[node_pos].pid = pItem->pid;
		arr_node[node_pos].priority = pItem->priority;
		arr_node[node_pos].state = pItem->state;
		arr_node[node_pos].procMsg = pItem->procMsg;

		//printf("Node pos in array: %d     PID: %d\n", arr_node[node_pos].position, *(int*)arr_node[node_pos].pid);
		
		// If the list is empty
		if(pList->item_count == 0){

			pList->head = &arr_node[node_pos];
			pList->tail = &arr_node[node_pos];
			arr_node[node_pos].prev = NULL;
			arr_node[node_pos].next = NULL;
			pList->current = &arr_node[node_pos];

			//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
		
		}else{

			arr_node[node_pos].prev = pList->tail;
			pList->tail->next = &arr_node[node_pos];
			pList->tail = &arr_node[node_pos];
			arr_node[node_pos].next = NULL;
			pList->current = &arr_node[node_pos];
		}

		pList->list_state = 2;		// Change the list state to inside the list
		pList->item_count++;
		node_dequeue();		// Take a node out from the the node pool

		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
		//printf("node_front: %d   node_rear: %d\n", node_front, node_rear);
	
		return LIST_SUCCESS;
	}

	return LIST_FAIL;
}




int MsgList_append(MsgList* pList, Message* pItem){

	assert(pList != NULL);
	//printf("number of nodes left before inserting: %d\n", free_node);

	// If all the nodes are used
	if(free_msg < 1){

		///printf("All the nodes are used.\n");
		return LIST_FAIL;

	}else{

		int msg_pos = msg_queue[msg_front];
		arr_msg[msg_pos].position = msg_pos;
		arr_msg[msg_pos].pid = pItem->pid;
		arr_msg[msg_pos].from = pItem->from;
		arr_msg[msg_pos].msg = pItem->msg;
		arr_msg[msg_pos].type = pItem->type;

		//printf("Node pos in array: %d     PID: %d\n", arr_node[node_pos].position, *(int*)arr_node[node_pos].pid);
		
		// If the list is empty
		if(pList->item_count == 0){

			pList->head = &arr_msg[msg_pos];
			pList->tail = &arr_msg[msg_pos];
			arr_msg[msg_pos].prev = NULL;
			arr_msg[msg_pos].next = NULL;
			pList->current = &arr_msg[msg_pos];

			//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
		
		}else{

			arr_msg[msg_pos].prev = pList->tail;
			pList->tail->next = &arr_msg[msg_pos];
			pList->tail = &arr_msg[msg_pos];
			arr_msg[msg_pos].next = NULL;
			pList->current = &arr_msg[msg_pos];
		}

		pList->list_state = 2;		// Change the list state to inside the list
		pList->item_count++;
		msg_dequeue();		// Take a node out from the the node pool

		//printf("current: %d  head: %d  tail: %d\n", pList->current->pid, pList->head->pid, pList->tail->pid);
		//printf("node_front: %d   node_rear: %d\n", msg_front, msg_rear);
	
		return LIST_SUCCESS;
	}

	return LIST_FAIL;
}



PCB* List_remove(List* pList){

	assert(pList != NULL);

	// If the list is empty or no nodes are being used
	if(pList->item_count == 0 || free_node == LIST_MAX_NUM_NODES){
		//printf("the list is empty or no nodes are used, nothing to remove\n");
		pList->list_state = LIST_OOB_START;
		return NULL;
	}

	// If the state of the list is before or beyond the list
	if(pList->list_state == LIST_OOB_START || pList->list_state == LIST_OOB_END){
		return NULL;
	}

	int node_pos = pList->current->position;

	// If there is only one item in the list
	if(pList->head == pList->tail){
	
		pList->head = NULL;
		pList->tail = NULL;
		pList->list_state = LIST_OOB_END;

	// If the current item is the head of the list
	}else if(pList->current == pList->head){
		
		//printf("current node to remove: %d\n",  *(int*)pList->current->pid);
		pList->current = pList->head;
		pList->head = pList->head->next;
		pList->head->prev = NULL;

		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);

	// If the current item is the last item in the list
	}else if(pList->current == pList->tail){
		
		//printf("current node to remove: %d \n",  *(int*)pList->current->pid);
		pList->tail = pList->tail->prev;
		pList->tail->next = NULL;
		pList->list_state = LIST_OOB_END;
		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);

	}else{
		PCB * temp = pList->current;
		
		//printf("current node to remove: %d\n",  *(int*)pList->current->pid);
		pList->current->prev->next = pList->current->next;
		pList->current->next->prev = pList->current->prev;
		pList->current = pList->current->next;
		pList->item_count--;
		node_enqueue(node_pos);
		return temp;
		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
	}

	pList->item_count--;
	node_enqueue(node_pos);		// Put the node back to the node pool

	//printf("number of nodes left after removing: %d\n", free_node);
	return pList->current;
}



Message* MsgList_remove(MsgList* pList){

	assert(pList != NULL);

	// If the list is empty or no nodes are being used
	if(pList->item_count == 0 || free_msg == LIST_MAX_NUM_NODES){
		//printf("the list is empty or no nodes are used, nothing to remove\n");
		pList->list_state = LIST_OOB_START;
		return NULL;
	}

	// If the state of the list is before or beyond the list
	if(pList->list_state == LIST_OOB_START || pList->list_state == LIST_OOB_END){
		return NULL;
	}

	int node_pos = pList->current->position;

	// If there is only one item in the list
	if(pList->head == pList->tail){
	
		pList->head = NULL;
		pList->tail = NULL;
		pList->list_state = LIST_OOB_END;

	// If the current item is the head of the list
	}else if(pList->current == pList->head){
		
		//printf("current node to remove: %d\n",  *(int*)pList->current->pid);
		pList->current = pList->head;
		pList->head = pList->head->next;
		pList->head->prev = NULL;

		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);

	// If the current item is the last item in the list
	}else if(pList->current == pList->tail){
		
		//printf("current node to remove: %d \n",  *(int*)pList->current->pid);
		pList->tail = pList->tail->prev;
		pList->tail->next = NULL;
		pList->list_state = LIST_OOB_END;
		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);

	}else{
		Message * temp = pList->current;
		
		//printf("current node to remove: %d\n",  *(int*)pList->current->pid);
		pList->current->prev->next = pList->current->next;
		pList->current->next->prev = pList->current->prev;
		pList->current = pList->current->next;
		pList->item_count--;
		msg_enqueue(node_pos);
		return temp;
		//printf("current: %d  head: %d  tail: %d\n", *(int*)pList->current->pid, *(int*)return temp->pid, *(int*)pList->tail->item);
	}

	pList->item_count--;
	msg_enqueue(node_pos);		// Put the node back to the node pool

	//printf("number of nodes left after removing: %d\n", free_node);
	return pList->current;
}




PCB* List_search(List* pList, COMPARATOR_FN pComparator, int pComparisonArg){

	// If the list is not empty, start searching
	if(pList->item_count != 0){

		pList->current = pList->head;
		pList->list_state = 2;

		//printf("pList->head %d   pList->current %d\n", pList->head->pid, pList->current->pid);

		while(pList->current != NULL){

			if(pComparator(pList->current->pid, pComparisonArg) == 1){

				//printf("state: %d   current: %d\n", pList->list_state, *(int*)pList->current->pid);
				return pList->current;
			}

			pList->current = pList->current->next;
		}
	}

	pList->list_state = LIST_OOB_END;
	//printf("state: %d\n", pList->list_state);
	return 0;
}



Message* MsgList_search(MsgList* pList, COMPARATOR_FN pComparator, int pComparisonArg){

	// If the list is not empty, start searching
	if(pList->item_count != 0){

		pList->current = pList->head;
		pList->list_state = 2;

		//printf("pList->head %d   pList->current %d\n", pList->head->pid, pList->current->pid);

		while(pList->current != NULL){

			if(pComparator(pList->current->pid, pComparisonArg) == 1){

				//printf("state: %d   current: %d\n", pList->list_state, *(int*)pList->current->pid);
				return pList->current;
			}

			pList->current = pList->current->next;
		}
	}

	pList->list_state = LIST_OOB_END;
	//printf("state: %d\n", pList->list_state);
	return 0;
}



PCB* initial_create(void){

	counter = 0;
	process_count = 0;
	for(int i = 0; i < 5; i++){
		arr_sem[i].sid = -1;
	}
	init_process = malloc(sizeof(PCB));

	if(init_process){

		init_process->pid = counter;
		init_process->state = RUNNING;
		init_process->procMsg = NULL;

		q_high = List_create();
		q_norm = List_create();
		q_low = List_create();
		q_waitingForReply = List_create();
		q_waitingToReceive = List_create();
		q_running = List_create();
		q_all = List_create();
		q_messages = MsgList_create();
		q_replies = MsgList_create();

		compare_ptr = &compare_test;	// Assign function address to pointer

		printf("Init Process PID: %d, Result: Success\n", init_process->pid);
		return init_process;
	}

	//printf("Action: Create process, Result: Success, Process ID: %ld\n", init_process->pid);
	return NULL;
}



void cpu_schudule(PCB* process){

	if(process->priority == 0){
		List_append(q_high, process);

	}else if(process->priority == 1){
		List_append(q_norm, process);

	}else{
		List_append(q_low, process);
	}
}



void cpu_schudule_priority(){

	PCB* temp = NULL;

	if(List_count(q_high) > 0){

		temp = List_first(q_high);
		temp->state = RUNNING;
		List_append(q_running, temp);
		List_remove(q_high);

	}else if(List_count(q_high) == 0 && List_count(q_norm) > 0){

		temp = List_first(q_norm);
		temp->state = RUNNING;
		List_append(q_running, temp);
		List_remove(q_norm);
	
	}else if(List_count(q_high) == 0 && List_count(q_norm) == 0 && List_count(q_low) > 0){
		
		temp = List_first(q_low);
		temp->state = RUNNING;
		List_append(q_running, temp);
		List_remove(q_low);
	}else{
		// No process ready
		init_process->state = RUNNING;
		//printf("init_state = %d\n", init_process->state);
	}
}



void cpu_print(){

	printf("\n=================== CPU scheduling ===================\n");
	//printf("Total # of process in system: %d\n", process_count);

	if(List_count(q_running) != 0){
		PCB* running = List_first(q_running);
		printf("Running process PID: %d, Priority (0 = High, 1 = Normal, 2 = Low): %d\n", running->pid, running->priority);
	}

	printf("Ready processes high priority: ");
	List_print(q_high);
	printf("Ready processes normal priority: ");
	List_print(q_norm);
	printf("Ready processes low priority: ");
	List_print(q_low);
	printf("======================================================\n");
}



void getMessageAndPrint(){

	//printf("\n=================== CPU scheduling ===================\n");

	if(List_count(q_running) != 0){

		PCB* running = List_first(q_running);

		//printf("Running process: %d\n", running->pid);

		if(MsgList_search(q_replies, compare_ptr, running->pid) != NULL){

			Message * temp = MsgList_remove(q_replies);

			running->procMsg = temp->msg;
			printf("Process %d did a reply() to this process and the reply is now received.\n", temp->from);
			printf("Message: %s\n", running->procMsg);
			running->procMsg = NULL;
			printf("********************************************************\n");
			//printf("======================================================\n");
		
		}
	}
}



void removeMessageAndReply(int pid){

	if(MsgList_search(q_messages, compare_ptr, pid) != NULL){

		MsgList_remove(q_messages);
	}

	if(MsgList_search(q_replies, compare_ptr, pid) != NULL){

		MsgList_remove(q_replies);
	}
}



// Create a new process and add it to appropriate READY queue.
int PCB_create(int priority){


	PCB* process;
	process = malloc(sizeof(PCB));
	//printf("%p\n", process);
	//process->pid = (int*)malloc(sizeof(int));

	if(process){

		counter++;
		semaphore_count = 0;
		process_count++;
		process->pid = counter;
		process->priority = priority;
		process->state = READY;
		process->procMsg = NULL;

		//printf("Action: Create process, Priority: High, Result: Success, Process ID: %p\n", process->pid);

		printf("=================== Create ===================\n");

		if(List_count(q_running) == 0 && List_count(q_high) == 0 && process->priority == 0){
			process->state = RUNNING;
			List_append(q_running, process);
			printf("Process ID: %d, State: %d, Priority: High, Result: Success.\n", process->pid, process->state);
			printf("Running process PID: %d, Priority: High\n", process->pid);
			//printf("# of running process: %d   PID of the running process: %d\n", List_count(q_running), process->pid);
			return PCB_SUCCESS;

		}else if(List_count(q_running) == 0 && List_count(q_high) == 0 && List_count(q_norm) == 0 && process->priority == 1){
			process->state = RUNNING;
			List_append(q_running, process);
			printf("Process ID: %d, State: %d, Priority: Norm, Result: Success.\n", process->pid, process->state);
			printf("Running process PID: %d, Priority: Norm\n", process->pid);
			//printf("# of running process: %d   PID of the running process: %d\n", List_count(q_running), process->pid);
			return PCB_SUCCESS;
		
		}else if(List_count(q_running) == 0 && List_count(q_high) == 0 && List_count(q_norm) == 0 && List_count(q_low) == 0 && process->priority == 2){
			process->state = RUNNING;
			List_append(q_running, process);
			printf("Process ID: %d, State: %d, Priority: Low, Result: Success.\n", process->pid, process->state);
			printf("Running process PID: %d, Priority: Low\n", process->pid);
			//printf("# of running process: %d   PID of the running process: %d\n", List_count(q_running), process->pid);
			return PCB_SUCCESS;
		}

		cpu_schudule(process);

		if(process->priority == 0){
			printf("Process ID: %d, State: %d, Priority: High, Result: Success.\n", process->pid, process->state);
		}else if(process->priority == 1){
			printf("Process ID: %d, State: %d, Priority: Normal, Result: Success.\n", process->pid, process->state);
		}else{
			printf("Process ID: %d, State: %d, Priority: Low, Result: Success.\n", process->pid, process->state);
		}

		if(process_count > 0){
			init_process->state = READY;
		}else{
			init_process->state = RUNNING;
		}

		//PCB* p = List_first(q_running);
		//cpu_print();
		return PCB_SUCCESS;
	}


	printf("Action: Create process, Result: Failure.\n");
	return PCB_FAIL;
}



int PCB_fork(void){

	PCB* new_process;
	new_process = malloc(sizeof(PCB));

	if(List_count(q_running) == 0){
		printf("Action: Fork, Result: Failure, no running process available.\n");
		return PCB_FAIL;
	}

	if(new_process){

		printf("=================== Fork ===================\n");

		PCB* running = List_first(q_running);
		process_count++;
		counter++;
		new_process->pid = counter;
		new_process->priority = running->priority;
		new_process->state = READY;
		new_process->procMsg = running->procMsg;

		if(MsgList_search(q_messages, compare_ptr, running->pid) != NULL){

			Message* childMsg = malloc(sizeof(Message));
			Message* parentMsg = MsgList_curr(q_messages);
			childMsg->pid = new_process->pid;
			childMsg->from = running->pid;
			childMsg->msg = parentMsg->msg;
			childMsg->type = parentMsg->type;
			MsgList_append(q_messages, childMsg);
		}

		cpu_schudule(new_process);
		//getMessageAndPrint();
		//cpu_print();
		printf("New process PID: %d, Result: Success.\n", new_process->pid);
		return PCB_SUCCESS;
	}

	printf("Action: Fork, Result: Failure.\n");
	return PCB_FAIL;
}



int PCB_kill(int pid){

	if(process_count == 0){
		printf("=================== Kill ===================\n");
		printf("Result: Success, init_process is the last process in the system, it has been killed. Program terminates.\n");
		end =1;
		free(init_process);
		return PCB_SUCCESS;
	}
	
	// Kill the running process
	if(List_search(q_running, compare_ptr, pid) != NULL){

		List_remove(q_running);
		removeMessageAndReply(pid);
		
		cpu_schudule_priority();

		process_count--;
		printf("=================== Kill ===================\n");
		printf("Process PID: %d, Action: Kill, Result: Success.\n", pid);
		getMessageAndPrint();
		cpu_print();
		return PCB_SUCCESS;
	}
	
	if(List_search(q_high, compare_ptr, pid) != NULL){
		process_count--;
		List_remove(q_high);
		removeMessageAndReply(pid);
		printf("=================== Kill ===================\n");
		printf("Process PID: %d, Result: Success.\n", pid);
		cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_norm, compare_ptr, pid) != NULL){
		process_count--;
		List_remove(q_norm);
		removeMessageAndReply(pid);
		printf("=================== Kill ===================\n");
		printf("Process PID: %d, Result: Success.\n", pid);
		cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_low, compare_ptr, pid) != NULL){
		process_count--;
		List_remove(q_low);
		removeMessageAndReply(pid);
		printf("=================== Kill ===================\n");
		printf("Process PID: %d, Result: Success.\n", pid);
		cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_waitingToReceive, compare_ptr, pid) != NULL){
		process_count--;
		List_remove(q_waitingToReceive);
		removeMessageAndReply(pid);
		printf("=================== Kill ===================\n");
		printf("Process PID: %d, Result: Success.\n", pid);
		cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_waitingForReply, compare_ptr, pid) != NULL){
		process_count--;
		List_remove(q_waitingForReply);
		removeMessageAndReply(pid);
		printf("=================== Kill ===================\n");
		printf("Process PID: %d, Result: Success.\n", pid);
		cpu_print();
		return PCB_SUCCESS;
	}else{

		for(int i = 0; i < 5; i++){
			if(List_count(arr_sem[i].blocked_processes) > 0){
				if(List_search(arr_sem[i].blocked_processes, compare_ptr, pid) != NULL){
					process_count--;
					List_remove(arr_sem[i].blocked_processes);
					removeMessageAndReply(pid);

					printf("=================== Kill ===================\n");
					printf("Process PID: %d, Result: Success.\n", pid);
					cpu_print();
					printf("Blocked process PIDs on this semaphore: ");
					List_print(arr_sem[i].blocked_processes);
					return PCB_SUCCESS;
				}
			}	
		}
	}
	
	printf("Process PID: %d, Action: Kill, Result: Failure, process does not exist.\n", pid);
	return PCB_FAIL;
}



int PCB_exit(void){

	if(process_count == 0){
		printf("=================== Kill ===================\n");
		printf("Result: Success, init_process is the last process in the system, it has been killed. Program terminates.\n");
		end = 1;
		return PCB_SUCCESS;
	}

	if(List_count(q_running) == 0){
		printf("Result: Failure, no running process available.\n");
		return PCB_FAIL;
	}

	PCB* removed = List_remove(q_running);
	process_count--;
	removeMessageAndReply(removed->pid);
	cpu_schudule_priority();

	printf("=================== Exit ===================\n");
	printf("Result: Success.\n");
	getMessageAndPrint();
	cpu_print();

	return PCB_SUCCESS;
}



int PCB_quantum(void){

	if(List_count(q_running) == 0){
		return PCB_SUCCESS;
	}
	
	PCB* removed_process = List_remove(q_running);
	removed_process->state = READY;
	
	cpu_schudule(removed_process);
	cpu_schudule_priority();

	printf("=================== Quantum ===================\n");
	printf("Result: Success.\n");
	getMessageAndPrint();
	cpu_print();

	return PCB_SUCCESS;
}



int PCB_send(int pid, char * msg){

	for(int i = 0; i < semaphore_count; i++){

		if(List_search(arr_sem[i].blocked_processes, compare_ptr, pid) != NULL){

			break;
		}

		if(List_search(q_high, compare_ptr, pid) == NULL &&
			List_search(q_norm, compare_ptr, pid) == NULL &&
			List_search(q_low, compare_ptr, pid) == NULL &&
			List_search(q_waitingToReceive, compare_ptr, pid) == NULL &&
			List_search(q_waitingForReply, compare_ptr, pid) == NULL &&
			pid != 0) {

			if(i == semaphore_count - 1){
				printf("Result: Failure, process does not exist.\n");
				return PCB_FAIL;
			}
		}
	}


	Message* message = malloc(sizeof(Message));

	if(List_count(q_running) > 0){
		PCB* running = List_first(q_running);

		message->pid = pid;
		message->from = running->pid;
		message->msg = malloc(strlen(msg) + 1);
		strcpy(message->msg, msg);
		message->type = SEND;
		//printf("Send to pid: %d.  From: %d.  Message:  %s\n", message->pid, message->from, message->msg);
	}else{

		message->pid = pid;
		message->from = 0;
		message->msg = malloc(strlen(msg) + 1);
		strcpy(message->msg, msg);

		message->type = SEND;
		//printf("Send to pid: %d.  From: %d.  Message:  %s\n", message->pid, message->from, message->msg);
	}

	if(MsgList_search(q_messages, compare_ptr, pid) != NULL){

		Message* oldMsg = MsgList_curr(q_messages);
		oldMsg->msg = message->msg;

	}else{
		MsgList_append(q_messages, message);
		//printf("first msg: %s\n", a->msg);
	}


	// Wakes it up
	if(List_search(q_waitingToReceive, compare_ptr, pid) != NULL){
		PCB* unblocked = List_remove(q_waitingToReceive);
		unblocked->state = READY;
		init_process->state = READY;
		cpu_schudule(unblocked);
	}

	if(List_count(q_running) > 0){
		PCB* running = List_first(q_running);
		List_remove(q_running);
		running->state = BLOCKED;
		List_append(q_waitingForReply, running);
	}

	cpu_schudule_priority();

	printf("=================== Send ===================\n");
	printf("Process PID: %d, Result: Success, message has been sent.\n", pid);
	//printf("Message: %s\n", message->msg);

	getMessageAndPrint();
	cpu_print();

	return PCB_SUCCESS;
}



int PCB_receive(){

	if(List_count(q_running) == 0){
		if(MsgList_search(q_messages, compare_ptr, init_process->pid) != NULL){

		Message * temp = MsgList_remove(q_messages);

		printf("=================== Receive ===================\n");
		printf("Process PID: %d, Result: Success, process has received a message from %d.\n", temp->pid, temp->from);
		printf("Message: %s\n", temp->msg);

		printf("********************************************************\n");
		getMessageAndPrint();
		cpu_print();
		return PCB_SUCCESS;
		}

		printf("=================== Receive ===================\n");
		printf("Process PID: %d, No message available.\n", init_process->pid);
		return PCB_FAIL;
	}

	PCB* running = List_first(q_running);
	
	if(MsgList_search(q_messages, compare_ptr, running->pid) != NULL){

		Message * temp = MsgList_remove(q_messages);

		printf("=================== Receive ===================\n");
		printf("Process PID: %d, Result: Success, process has received a message from %d.\n", temp->pid, temp->from);
		printf("Message: %s\n", temp->msg);

		printf("********************************************************\n");
		getMessageAndPrint();
		cpu_print();
		return PCB_SUCCESS;
	}


	List_remove(q_running);
	running->state = BLOCKED;
	List_append(q_waitingToReceive, running);
	
	cpu_schudule_priority();

	printf("=================== Receive ===================\n");
	printf("Process PID: %d, No message available, process is waiting to receive a message.\n", running->pid);
	getMessageAndPrint();
	cpu_print();

	return PCB_SUCCESS;
}



int PCB_reply(int pid, char * msg){


	if(List_search(q_waitingForReply, compare_ptr, pid) == NULL){
		printf("Action: Reply, Result: Failure, process has not done send.\n");
		return PCB_FAIL;
	}

	if(List_search(q_high, compare_ptr, pid) == NULL &&
		List_search(q_norm, compare_ptr, pid) == NULL &&
		List_search(q_low, compare_ptr, pid) == NULL &&
		List_search(q_waitingToReceive, compare_ptr, pid) == NULL &&
		List_search(q_waitingForReply, compare_ptr, pid) == NULL){
		printf("Action: Reply, Result: Failure, process does not exist.\n");
		return PCB_FAIL;
	}

	Message* message = malloc(sizeof(Message));

	if(List_count(q_running) > 0){
		PCB* running = List_first(q_running);

		message->pid = pid;
		message->from = running->pid;
		message->msg = malloc(strlen(msg) + 1);
		strcpy(message->msg, msg);
		message->type = SEND;
		//printf("Send to pid: %d.  From: %d.  Message:  %s\n", message->pid, message->from, message->msg);
	}else{

		message->pid = pid;
		message->from = 0;
		message->msg = malloc(strlen(msg) + 1);
		strcpy(message->msg, msg);

		message->type = SEND;
		//printf("Send to pid: %d.  From: %d.  Message:  %s\n", message->pid, message->from, message->msg);
	}

	// If PID has done send
	if(List_search(q_waitingForReply, compare_ptr, pid) != NULL){
		PCB* unblocked = List_remove(q_waitingForReply);
		unblocked->state = READY;
		cpu_schudule(unblocked);
		MsgList_append(q_replies, message);

		printf("=================== Reply ===================\n");
		printf("Process PID: %d, Result: Success, reply has been sent.\n", pid);
		//printf("Message: %s\n", message->msg);
		init_process->state = READY;
		cpu_schudule_priority();
		getMessageAndPrint();
		//cpu_print();
		return PCB_SUCCESS;
	}

	printf("Action: Reply, Result: Failure, process has not done send.\n");
	return PCB_FAIL;
}



int SEM_new(int sid, int value){

	for(int i = 0; i < 5; i++){
		if(arr_sem[i].sid == sid){
			printf("=================== New Semaphore ===================\n");
			printf("Result: Failure, Semaphore ID %d already exists.\n", arr_sem[i].sid);
			return PCB_FAIL;
		}
	}

	arr_sem[semaphore_count].sid = sid;
	arr_sem[semaphore_count].value = value;
	arr_sem[semaphore_count].blocked_processes = List_create();
	printf("=================== New Semaphore ===================\n");
	printf("Semaphore ID: %d, Value: %d, Result: Success.\n", arr_sem[semaphore_count].sid, arr_sem[semaphore_count].value);
	
	semaphore_count++;
	return PCB_SUCCESS;
}



int P(int sid){

	if(List_count(q_running) == 0){
		return PCB_SUCCESS;
	}


	for(int i = 0; i < 5; i++){
		if(arr_sem[i].sid == sid){
			arr_sem[i].value = arr_sem[i].value - 1;

			if(arr_sem[i].value < 0 && init_process != RUNNING){

				PCB* running = List_remove(q_running);
				running->state = BLOCKED;
				List_append(arr_sem[i].blocked_processes, running);

				cpu_schudule_priority();
				printf("=================== Semaphore P ===================\n");
				printf("Semaphore ID: %d, Value %d, Result: Success, process is blocked on this semaphore.\n", sid, arr_sem[i].value);
				printf("Blocked process PIDs on this semaphore: ");
				List_print(arr_sem[i].blocked_processes);
				getMessageAndPrint();
				cpu_print();
				return PCB_SUCCESS;
			}

			printf("=================== Semaphore P ===================\n");
			printf("Semaphore ID: %d, Value %d, Result: Success, process is NOT blocked on this semaphore.\n", sid, arr_sem[i].value);

			cpu_print();
			return PCB_SUCCESS;
		}
	}

	printf("=================== Semaphore P ===================\n");
	printf("Result: Failure, semaphore does not exist.\n");
	return PCB_FAIL;
}



int V(int sid){


	if(List_count(q_running) == 0){


		for(int i = 0; i < 5; i++){
			if(arr_sem[i].sid == sid){

				arr_sem[i].value = arr_sem[i].value + 1;

				if(arr_sem[i].value <= 0){

					if(List_count(arr_sem[i].blocked_processes) > 0){

						List_first(arr_sem[i].blocked_processes);
						PCB* unblocked = List_remove(arr_sem[i].blocked_processes);
						unblocked->state = READY;
						init_process->state = READY;
						cpu_schudule(unblocked);
						cpu_schudule_priority();

						printf("=================== Semaphore V ===================\n");
						printf("Semaphore ID: %d, Value %d, Result: Success.\n", sid, arr_sem[i].value);
						getMessageAndPrint();
						cpu_print();
						printf("Blocked process PIDs on this semaphore: ");
						List_print(arr_sem[i].blocked_processes);
						return PCB_SUCCESS;
					}
				}

				printf("=================== Semaphore V ===================\n");
				printf("Semaphore ID: %d, Value %d, Result: Failure, no process to be woken up.\n", sid, arr_sem[i].value);
				return PCB_FAIL;
			}
		}

	}



	for(int i = 0; i < 5; i++){
		if(arr_sem[i].sid == sid){

			arr_sem[i].value = arr_sem[i].value + 1;

			if(arr_sem[i].value <= 0){

				if(List_count(arr_sem[i].blocked_processes) > 0){

					List_first(arr_sem[i].blocked_processes);
					PCB* unblocked = List_remove(arr_sem[i].blocked_processes);
					unblocked->state = READY;
					cpu_schudule(unblocked);

					printf("=================== Semaphore V ===================\n");
					printf("Semaphore ID: %d, Value %d, Result: Success.\n", sid, arr_sem[i].value);
					getMessageAndPrint();
					cpu_print();
					printf("Blocked process PIDs on this semaphore: ");
					List_print(arr_sem[i].blocked_processes);
					return PCB_SUCCESS;
				}
			}

			printf("=================== Semaphore V ===================\n");
			printf("Semaphore ID: %d, Value %d, Result: Failure, no process to be woken up.\n", sid, arr_sem[i].value);
			return PCB_FAIL;
		}
	}

	printf("=================== Semaphore V ===================\n");
	printf("Result: Failure, semaphore does not exist.\n");
	return PCB_FAIL;
}



void display_message(int pid){

	if(MsgList_search(q_messages, compare_ptr, pid) != NULL){
		Message* temp = MsgList_curr(q_messages);
		printf("Message received: %s\n", temp->msg);
	}

	if(MsgList_search(q_replies, compare_ptr, pid) != NULL){
		Message* temp = MsgList_curr(q_replies);
		printf("Reply received: %s\n", temp->msg);
	}
}



int PCB_Procinfo(int pid){

	PCB* temp = NULL;

	if(List_search(q_running, compare_ptr, pid) != NULL){
		temp = List_curr(q_running);
		printf("=================== Procinfo ===================\n");
		printf("Process PID: %d\n", pid);
		printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
		printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
		display_message(pid);
		//cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_high, compare_ptr, pid) != NULL){
		temp = List_curr(q_high);
		printf("=================== Procinfo ===================\n");
		printf("Process PID: %d\n", pid);
		printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
		printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
		display_message(pid);
		//cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_norm, compare_ptr, pid) != NULL){
		temp = List_curr(q_norm);
		printf("=================== Procinfo ===================\n");
		printf("Process PID: %d\n", pid);
		printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
		printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
		display_message(pid);
		//cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_low, compare_ptr, pid) != NULL){
		temp = List_curr(q_low);
		printf("=================== Procinfo ===================\n");
		printf("Process PID: %d\n", pid);
		printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
		printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
		display_message(pid);
		//cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_waitingToReceive, compare_ptr, pid) != NULL){
		temp = List_curr(q_waitingToReceive);
		printf("=================== Procinfo ===================\n");
		printf("Process PID: %d\n", pid);
		printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
		printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
		display_message(pid);
		//cpu_print();
		return PCB_SUCCESS;
	}else if(List_search(q_waitingForReply, compare_ptr, pid) != NULL){
		temp = List_curr(q_waitingForReply);
		printf("=================== Procinfo ===================\n");
		printf("Process PID: %d\n", pid);
		printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
		printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
		display_message(pid);
		//cpu_print();
		return PCB_SUCCESS;
	}else{

		for(int i = 0; i < 5; i++){
			if(List_count(arr_sem[i].blocked_processes) > 0){
				if(List_search(arr_sem[i].blocked_processes, compare_ptr, pid) != NULL){
					temp = List_curr(arr_sem[i].blocked_processes);
					printf("=================== Procinfo ===================\n");
					printf("Process PID: %d\n", pid);
					printf("Priority (0 = High, 1 = Normal, 2 = Low): %d\n", temp->priority);
					printf("State (0 = Running, 1 = Ready, 2 = Blocked): %d\n", temp->state);
					display_message(pid);
					//cpu_print();
					return PCB_SUCCESS;
				}
			}	
		}
	}

	printf("=================== Procinfo ===================\n");
	printf("Result: Failure, process does not exist.\n");
	return PCB_FAIL;
}



void Totalinfo(){

	cpu_print();	
	printf("Sender waiting for reply: ");
	List_print(q_waitingForReply);
	printf("Receiver waiting for message: ");
	List_print(q_waitingToReceive);
	printf("Messages to be received by: ");
	MsgList_print(q_messages);
	printf("Replies to be received by: ");
	MsgList_print(q_replies);

	for(int i = 0; i < semaphore_count; i++){
		if(List_count(arr_sem[i].blocked_processes) > 0){
				printf("Processes blocked on Semaphore %d: ", arr_sem[i].sid);
				List_print(arr_sem[i].blocked_processes);
		}else{
			printf("Processes blocked on Semaphore: None.\n");
		}	
	}

}













