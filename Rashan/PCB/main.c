/**
 * PCB simulator
 * */
#include <stdlib.h>
#include "list.h"
#include <stdio.h>
#include <string.h>

#define MSG_MAX_LEN 41

static List* ready_queue_high;
static List* ready_queue_norm;
static List* ready_queue_low;

static List* sender_blocked_queue;
static List* reciever_blocked_queue;

static int process_count = 0 ;
static int high_cpu_burst = 0 ;
static int norm_cpu_burst = 0 ;
static int low_cpu_burst = 0;
static float high_desired = 50.0;
static float norm_desired = 30.0;

static float terminate = false;


typedef struct Sending_s Sending;
struct Sending_s {
    int sender_PID;
    char msg[MSG_MAX_LEN];
};

typedef struct PCB_s PCB;
struct PCB_s {
    int PID;
    int priority;
    int state;
    bool ready_to_recieve;
    Sending msg_recieved;
    Sending reply_recieved;
};

typedef struct Found_s Found;
struct Found_s {
    PCB* process;
    int count;
};

typedef struct Semaphor_s Semaphor;
struct Semaphor_s {
    int value;
    bool initialized;
    List* blocked_list;
};

static PCB struct_process_init;
static PCB* process_init = &struct_process_init;
static Found found;
static PCB* running;
static Semaphor semaphor1;
static Semaphor semaphor2; 
static Semaphor semaphor3; 
static Semaphor semaphor4; 
static Semaphor semaphor5; 

void free_process(void *process)
{
	free(process);
}

static void processX(){
    terminate = true;
    List_free(ready_queue_high, free_process);
    List_free(ready_queue_norm, free_process);
    List_free(ready_queue_low, free_process);
    return;
}

static bool process_equals(void *pItem, void *pArg)
{
    PCB* process_item = pItem;
    int* x =pArg;
    return (process_item->PID == *x);
}


static void schedule_cpu(){
    if(List_count(ready_queue_high)<=0 && List_count(ready_queue_norm)<=0 && List_count(ready_queue_low)<=0 && (running == process_init)){
        process_init->PID = 0;
        process_init->priority = -1;
        process_init->state = 0;
        running = process_init;
        printf("Now running process_init\n");
        
        if(strcmp(running->msg_recieved.msg,"") != 0 && running->ready_to_recieve){
            printf("Message Recieved = %s\n", running->msg_recieved.msg);
            printf("From Sender PID = %d\n", running->msg_recieved.sender_PID);
            strcpy(running->msg_recieved.msg, "");
            running->ready_to_recieve = false;
        }
        if(strcmp(running->reply_recieved.msg,"") != 0 ){
            printf("Reply Recieved = %s\n", running->reply_recieved.msg);
            printf("Replier PID = %d\n", running->reply_recieved.sender_PID);
            strcpy(running->reply_recieved.msg, "");
        }
        return;
    }
    if(List_count(ready_queue_high)>0 || List_count(ready_queue_norm)>0 || List_count(ready_queue_low)>0){
        int count = 1;
        float total_run =  high_cpu_burst + norm_cpu_burst + low_cpu_burst;
        float high_cpu_percent;
        float norm_cpu_percent;
        float low_cpu_percent;
        if(high_cpu_burst==0 && norm_cpu_burst==0 && low_cpu_burst==0){printf("total Cpu run %f\n",total_run);printf("All Queue get 0 percent CPU\n");}
        else{
            high_cpu_percent = high_cpu_burst*100/total_run;
            norm_cpu_percent = norm_cpu_burst*100/total_run;
            low_cpu_percent = low_cpu_burst*100/total_run;
            printf("total Cpu run until last scheduling %f\n",total_run);
            printf("High priority Queue got %f percent CPU until last scheduling\n",high_cpu_percent);
            printf("Norm priority Queue got %fpercent CPU until last scheduling\n",norm_cpu_percent);
            printf("Low priority Queue got %f percent CPU until last scheduling\n",low_cpu_percent);
        }

        while(1){
            if((List_count(ready_queue_high)>0 && high_cpu_percent<=high_desired) || (count == 5 && List_count(ready_queue_high)>0)){
                high_cpu_burst++;
                PCB* next_process = List_trim(ready_queue_high);
                if(running != process_init){
                    running->state = 1;
                    if(running->priority == 0){List_prepend(ready_queue_high,running);}
                    if(running->priority == 1){List_prepend(ready_queue_norm,running);}
                    if(running->priority == 2){List_prepend(ready_queue_low,running);}
                }
                process_init->state = 1;
                next_process->state = 0;
                running = next_process;
                break;
            }

            if((List_count(ready_queue_norm)>0 && norm_cpu_percent<=norm_desired) || (count == 4 && List_count(ready_queue_norm)>0)){
                norm_cpu_burst++;
                PCB* next_process = List_trim(ready_queue_norm);
                if(running != process_init){
                    running->state =1;
                    if(running->priority == 0){List_prepend(ready_queue_high,running);}
                    if(running->priority == 1){List_prepend(ready_queue_norm,running);}
                    if(running->priority == 2){List_prepend(ready_queue_low,running);}
                }
                process_init->state = 1;
                next_process->state = 0;
                running = next_process;
                break;
            }

            if(List_count(ready_queue_low)>0){
                low_cpu_burst++;
                PCB* next_process = List_trim(ready_queue_low);
                if(running != process_init){
                    running->state =1;
                    if(running->priority == 0){List_prepend(ready_queue_high,running);}
                    if(running->priority == 1){List_prepend(ready_queue_norm,running);}
                    if(running->priority == 2){List_prepend(ready_queue_low,running);}
                }
                process_init->state = 1;
                next_process->state = 0;
                running = next_process;
                break;
            }
            count++;
        }
        printf("newly scheduled running PID = %d\n",running->PID);
        printf("newly scheduled running priority = %d\n",running->priority);

        if(strcmp(running->msg_recieved.msg,"") != 0 && running->ready_to_recieve){
            printf("Message Recieved = %s\n", running->msg_recieved.msg);
            printf("From Sender PID = %d\n", running->msg_recieved.sender_PID);
            strcpy(running->msg_recieved.msg, "");
            running->ready_to_recieve = false;
        }
        if(strcmp(running->reply_recieved.msg,"") != 0 ){
            printf("Reply Recieved = %s\n", running->reply_recieved.msg);
            printf("Replier PID = %d\n", running->reply_recieved.sender_PID);
            strcpy(running->reply_recieved.msg, "");
        }
        return;
    }
    printf("cannot reschedule since no other process ready\n");
    return;
}

static void processC(){
    int priority;
    printf("Please input the priority of the process you like to create\n");
    int valid = scanf("%d", &priority);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    process_count++;
    int status = -2;
    if(priority>=0 && priority<=2){
        PCB* process = (PCB *)malloc(sizeof(PCB));  // malloc here remeber to free dynamic
        process->PID = process_count;
        process->priority = priority;
        process->state = 1;
        process->ready_to_recieve = false;
        strcpy(process->msg_recieved.msg,"");
        strcpy(process->reply_recieved.msg,"");

        if(priority == 0){status = List_prepend(ready_queue_high, process);}
        else if(priority == 1){status = List_prepend(ready_queue_norm, process);}
        else if(priority == 2){status = List_prepend(ready_queue_low, process);}
    }

    if(status == -1){printf("Sorry process creation failed no available space to accomodate new process \n");}
    if(status == -2){printf("Sorry process creation failed you provide an invalid priority \n");}
    else if(status == 0){
        printf("Process succesfully created with process id %d\n",process_count);
        int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
        printf("total ready %d\n",total_ready);
        if(total_ready == 1 && running == process_init){schedule_cpu();}
    }
    return;
}

static void printQueue(List* pList){
    pList->current = pList->tail;
    printf("NULL\n");
    if(pList->current == NULL){
        printf("empty\n");
    }
    while (pList->current != NULL){
        PCB* process = pList->current->item;
        printf("PID = %d\n", process->PID);
        printf("Pstate = %d\n", process->state);
        printf("Priority = %d\n", process->priority);
        printf("|\n");
        printf("V\n");
        pList->current = pList->current->previous;
    }
    printf("NULL\n");
    return;
}

static void processT(){
    printf("\n");
    printf("Ready queue high\n");
    printf("|\n");
    printf("V\n");
    printQueue(ready_queue_high);
    printf("\n");

    printf("Ready queue norm\n");
    printf("|\n");
    printf("V\n");
    printQueue(ready_queue_norm);
    printf("\n");

    printf("Ready queue low\n");
    printf("|\n");
    printf("V\n");
    printQueue(ready_queue_low);
    printf("\n");

    printf("Sender blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(sender_blocked_queue);
    printf("\n");

    printf("Reciever blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(reciever_blocked_queue);
    printf("\n");

    printf("Semaphor1 blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(semaphor1.blocked_list);
    printf("\n");

    printf("Semaphor2 blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(semaphor2.blocked_list);
    printf("\n");

    printf("Semaphor3 blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(semaphor3.blocked_list);
    printf("\n");

    printf("Semaphor4 blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(semaphor4.blocked_list);
    printf("\n");

    printf("Semaphor5 blocked queue\n");
    printf("|\n");
    printf("V\n");
    printQueue(semaphor5.blocked_list);
    printf("\n");

    return;
}

static void processQ(){
    schedule_cpu();
    return;
}

static bool all_queue_empty(){
    bool result = List_count(ready_queue_high)<=0 && List_count(ready_queue_norm)<=0 
                     && List_count(ready_queue_low)<=0 && List_count(sender_blocked_queue)<=0 
                     && List_count(reciever_blocked_queue)<=0; // remember to add semaphor blocked list
    return result;
}

static void free_all_dynamic(){
    List_free(ready_queue_high, free_process);
    List_free(ready_queue_norm, free_process);
    List_free(ready_queue_low, free_process);
    List_free(sender_blocked_queue, free_process);
    List_free(reciever_blocked_queue, free_process);
    return;
}

static void processE(){
    if(running == process_init){
        if(all_queue_empty()){
            terminate = true;
            free_all_dynamic();
            printf("Successfully killed running process_init therefore simulation is terminating\n");
        }
        else{printf("Sorry you cannot kill or exit process_init because you have some other process waiting for execution\n");}
        return;
    }
    int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
    if(total_ready == 0){free(running);running = process_init;schedule_cpu();}
    else{
        int priority = running->priority;
        schedule_cpu();
        PCB* kill_process = NULL;
        if(priority == 0){kill_process = List_first(ready_queue_high);List_remove(ready_queue_high);}
        else if(priority == 1){kill_process = List_first(ready_queue_norm);List_remove(ready_queue_norm);}
        else if(priority == 2){kill_process = List_first(ready_queue_low);List_remove(ready_queue_low);}
        free(kill_process);

    } //PROBLEM
    printf("Successfully killed running process\n");
    return;
}

static void search_all_Queue(int PID){
    List_first(ready_queue_high);
    PCB* kill_process = List_search(ready_queue_high, process_equals, &PID);
    int count = 0;
    while(kill_process == NULL){
        count++;
        if(count == 1){List_first(ready_queue_norm); kill_process = List_search(ready_queue_norm, process_equals, &PID);}
        else if(count == 2){List_first(ready_queue_low); kill_process = List_search(ready_queue_low, process_equals, &PID);}
        else if(count == 3){List_first(sender_blocked_queue); kill_process = List_search(sender_blocked_queue, process_equals, &PID);}
        else if(count == 4){List_first(reciever_blocked_queue); kill_process = List_search(reciever_blocked_queue, process_equals, &PID);}
        else if(count == 5){List_first(semaphor1.blocked_list); kill_process = List_search(semaphor1.blocked_list, process_equals, &PID);}
        else if(count == 6){List_first(semaphor2.blocked_list); kill_process = List_search(semaphor2.blocked_list, process_equals, &PID);}
        else if(count == 7){List_first(semaphor3.blocked_list); kill_process = List_search(semaphor3.blocked_list, process_equals, &PID);}
        else if(count == 8){List_first(semaphor4.blocked_list); kill_process = List_search(semaphor4.blocked_list, process_equals, &PID);}
        else if(count == 9){List_first(semaphor5.blocked_list); kill_process = List_search(semaphor5.blocked_list, process_equals, &PID);}
        else{break;} 
    }
    found.count = count; 
    found.process = kill_process; 
    return;
}

static void processK(){
    int PID;
    printf("Please input the PID of the process you wish to Kill\n");
    int valid = scanf("%d", &PID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    if(PID == running->PID){
        processE();
        return;
    }

    search_all_Queue(PID);
    PCB* kill_process = found.process;
    if(found.count == 0){List_remove(ready_queue_high); free(kill_process); printf("Succesfully killed from ready_queue_high\n");}
    else if(found.count == 1){List_remove(ready_queue_norm); free(kill_process); printf("Succesfully killed from ready_queue_norm\n");}
    else if(found.count == 2){List_remove(ready_queue_low); free(kill_process); printf("Succesfully killed from ready_queue_low\n");}
    else if(found.count == 3){List_remove(sender_blocked_queue); free(kill_process); printf("Succesfully killed from sender_blocked_queue\n");}
    else if(found.count == 4){List_remove(reciever_blocked_queue); free(kill_process); printf("Succesfully killed from reciever_blocked_queue\n");}
    else if(found.count == 5){List_remove(semaphor1.blocked_list); free(kill_process); printf("Succesfully killed from semaphor1_blocked_queue\n");}
    else if(found.count == 6){List_remove(semaphor2.blocked_list); free(kill_process); printf("Succesfully killed from semaphor2_blocked_queue\n");}
    else if(found.count == 7){List_remove(semaphor3.blocked_list); free(kill_process); printf("Succesfully killed from semaphor3_blocked_queue\n");}
    else if(found.count == 8){List_remove(semaphor4.blocked_list); free(kill_process); printf("Succesfully killed from semaphor4_blocked_queue\n");}
    else if(found.count == 9){List_remove(semaphor5.blocked_list); free(kill_process); printf("Succesfully killed from semaphor5blocked_queue\n");}
    else{printf("There is no existing process in the system with the PID you provided. Help: may be you are referring to a process that used to exist\n");}
    return;
}

static void processS(){
    char messageRx[MSG_MAX_LEN + 1];
    printf("Please remember only 40 character long message will be included extra character after 40 will not be sent\n");
    printf("Please enter the message you wish to send\n");
    char str[1024]; 
    scanf("%[^\n]%*c", str);
    for(int i =0;i<MSG_MAX_LEN && i<=strlen(str);i++){ messageRx[i] = str[i];} 
    messageRx[strlen(messageRx)+1] = '\0';
    int PID;
    printf("Please input the PID of the process you wish to send message\n");
    int valid = scanf("%d", &PID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    if(PID==0 && running == process_init){printf("Failed you are trying to send a message to process_init itself\n");return;}
    if(running == process_init){process_init->msg_recieved.sender_PID = running->PID;strcpy(process_init->msg_recieved.msg, messageRx);printf("Send Succesfull not blocked since process_init\n");return;}
    if(PID == running->PID){printf("Failed you are trying to send a message to the process itself\n");return;}
    
    search_all_Queue(PID);
    PCB* exist = found.process;
    if(PID==0){process_init->msg_recieved.sender_PID = running->PID;strcpy(process_init->msg_recieved.msg, messageRx);}
    else if(found.count == 10){printf("Failed there is no existing process in the system with the PID you provided. Help: may be you are referring to a process that used to exist\n");return;}
    else if(found.count == 4){
        printf("Reciever with PID %d unblocked\n",exist->PID);
        exist->msg_recieved.sender_PID = running->PID;
        strcpy(exist->msg_recieved.msg, messageRx);
        List_remove(reciever_blocked_queue);

        exist->state = 1;
        if(exist->priority == 0){List_prepend(ready_queue_high,exist);}
        if(exist->priority == 1){List_prepend(ready_queue_norm,exist);}
        if(exist->priority == 2){List_prepend(ready_queue_low,exist);}
    }
    else{
        exist->msg_recieved.sender_PID = running->PID;
        strcpy(exist->msg_recieved.msg, messageRx);
    }

    running->state = 2;
    printf("Running process with PID %d blocked on send\n",running->PID);
    List_prepend(sender_blocked_queue,running);

    int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
    if(total_ready == 0){running = process_init;schedule_cpu();}
    else{
        int priority = running->priority;
        schedule_cpu();
        PCB* process = running;
        printf("running priority %d",process->priority);
        if(priority == 0){process = List_first(ready_queue_high);List_remove(ready_queue_high);}
        else if(priority == 1){process = List_first(ready_queue_norm);List_remove(ready_queue_norm);}
        else if(priority == 2){process = List_first(ready_queue_low);List_remove(ready_queue_low);}

    }   //FIX HERE AFTER SUBMISSION PROBLEM
    return;
}

static void processR(){
    if(strcmp(running->msg_recieved.msg,"") != 0){
        printf("Message Recieved = %s\n", running->msg_recieved.msg);
        printf("From Sender PID = %d\n", running->msg_recieved.sender_PID);
        strcpy(running->msg_recieved.msg, "");
        return;
    }
    running->ready_to_recieve = true;
    if(running->PID==0){printf("Success Waiting to recieve and not blocked since process_init\n");return;}
    printf("Running process with PID %d blocked for recieve\n",running->PID);
    running->state = 2;
    List_prepend(reciever_blocked_queue,running);
    int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
    if(total_ready == 0){running = process_init;schedule_cpu();}
    else{
        int priority = running->priority;
        schedule_cpu();
        PCB* process = running;
        printf("running priority %d",process->priority);
        if(priority == 0){process = List_first(ready_queue_high);List_remove(ready_queue_high);}
        else if(priority == 1){process = List_first(ready_queue_norm);List_remove(ready_queue_norm);}
        else if(priority == 2){process = List_first(ready_queue_low);List_remove(ready_queue_low);}

    }  
    return;
}

static void processY(){
    char messageRx[MSG_MAX_LEN];
    printf("Please remember only 40 character long message will be included extra character after 40 will not be repliedt\n");
    printf("Please enter the message you wish to reply\n");
    memset(messageRx, '\0', MSG_MAX_LEN); // Clean everytime you enter message to messageRx
    fgets(messageRx, MSG_MAX_LEN, stdin);
    messageRx[strlen(messageRx) - 1] = '\0';

    int PID;
    printf("Please input the PID of the process you wish to send the reply\n");
    int valid = scanf("%d", &PID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    PCB* sender_exist = NULL;
    List_first(sender_blocked_queue);
    sender_exist = List_search(sender_blocked_queue, process_equals, &PID);
    if(sender_exist == NULL){printf("Failed There is no blocked sender process in the system with the PID you provided. Help: may be you are referring to a process that used to exist\n");return;}
    
    printf("Success Sender with PID %d unblocked\n",sender_exist->PID);
    sender_exist->reply_recieved.sender_PID = running->PID;
    strcpy(sender_exist->reply_recieved.msg, messageRx);
    List_remove(sender_blocked_queue);
    sender_exist->state = 1;
    if(sender_exist->priority == 0){List_prepend(ready_queue_high,sender_exist);}
    if(sender_exist->priority == 1){List_prepend(ready_queue_norm,sender_exist);}
    if(sender_exist->priority == 2){List_prepend(ready_queue_low,sender_exist);}

    int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
    printf("total ready %d\n",total_ready);
    if(total_ready == 1 && running == process_init){schedule_cpu();}

    return;
}

static void processN(){
    int SID;
    printf("Please input the SemaphorID of the semaphor you wish to create\n");
    int valid = scanf("%d", &SID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    while(!(SID>=0 && SID<=4)){
        printf("Please input valid SemaphorID of the semaphor you wish to create\n");
        valid = scanf("%d", &SID);
        getchar();
        if(valid != 1){printf("Invalid Input\n");processX();return;}
    }

    int value;
    printf("Please input the Semaphor value of the semaphor you wish to create\n");
    valid = scanf("%d", &value);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    while(value<0){
        printf("Please input valid Semaphor value of the semaphor you wish to create\n");
        valid = scanf("%d", &value);
        getchar();
        if(valid != 1){printf("Invalid Input\n");processX();return;}
    }

    if(SID == 0){if(semaphor1.initialized){printf("Cannot process the request Semaphor1 already created\n"); return;} semaphor1.initialized = true; semaphor1.value = value;}
    else if(SID == 1){if(semaphor2.initialized){printf("Cannot process the request Semaphor2 already created\n"); return;} semaphor2.initialized = true; semaphor2.value = value;}
    else if(SID == 2){if(semaphor3.initialized){printf("Cannot process the request Semaphor3 already created\n"); return;} semaphor3.initialized = true; semaphor3.value = value;}
    else if(SID == 3){if(semaphor4.initialized){printf("Cannot process the request Semaphor4 already created\n"); return;} semaphor4.initialized = true; semaphor4.value = value;}
    else if(SID == 4){if(semaphor5.initialized){printf("Cannot process the request Semaphor5 already created\n"); return;} semaphor5.initialized = true; semaphor5.value = value;}
    printf("Succesfully created Semaphor%d\n",SID+1);
    return;
}
static void block_semaphor(List* block_list){
        if(running == process_init){printf("Failed cannot process request, you cannot block process_init on Semaphor\n");}
        else{
            running->state = 2;
            List_prepend(block_list,running);
            printf("Succesfully blocked running process in the semaphor\n");
            int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
            if(total_ready == 0){running = process_init;schedule_cpu();}
            else{
                int priority = running->priority;
                schedule_cpu();
                PCB* process = running;
                printf("running priority %d",process->priority);
                if(priority == 0){process = List_first(ready_queue_high);List_remove(ready_queue_high);}
                else if(priority == 1){process = List_first(ready_queue_norm);List_remove(ready_queue_norm);}
                else if(priority == 2){process = List_first(ready_queue_low);List_remove(ready_queue_low);}

             }
        }
        return;
}
static void processP(){
    int SID;
    printf("Please input the SemaphorID of the semaphor you wish to do P operation\n");
    int valid = scanf("%d", &SID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    while(!(SID>=0 && SID<=4)){
        printf("Please input valid SemaphorID of the semaphor you wish to do P operation\n");
        valid = scanf("%d", &SID);
        getchar();
        if(valid != 1){printf("Invalid Input\n");processX();return;}
    }

    if(SID == 0 && semaphor1.initialized){semaphor1.value--; if(semaphor1.value<0){block_semaphor(semaphor1.blocked_list);}}
    else if(SID == 1 && semaphor2.initialized){semaphor2.value--; if(semaphor2.value<0){block_semaphor(semaphor2.blocked_list);}}
    else if(SID == 2 && semaphor3.initialized){semaphor3.value--; if(semaphor3.value<0){block_semaphor(semaphor3.blocked_list);}}
    else if(SID == 3 && semaphor4.initialized){semaphor4.value--; if(semaphor4.value<0){block_semaphor(semaphor4.blocked_list);}}
    else if(SID == 4 && semaphor5.initialized){semaphor5.value--; if(semaphor5.value<0){block_semaphor(semaphor5.blocked_list);}}
    return;
}

static void unblock_semaphor(List* blocked_list){
    if(List_count(blocked_list)<=0){printf("Failed to process request No process to unblock in this semaphor\n");}
    else{
        PCB* unblock = List_trim(blocked_list);
        unblock->state = 1;
        if(unblock->priority == 0){List_prepend(ready_queue_high,unblock);}
        if(unblock->priority == 1){List_prepend(ready_queue_norm,unblock);}
        if(unblock->priority == 2){List_prepend(ready_queue_low,unblock);}
        int total_ready = List_count(ready_queue_high) + List_count(ready_queue_norm) + List_count(ready_queue_low);
        printf("Succesfully unblocked process from the Semaphor\n");
        printf("total ready %d\n",total_ready);
        if(total_ready == 1 && running == process_init){schedule_cpu();}
        printf("Succesfully unblocked process from the Semaphor\n");
    }
    return;
}
static void processV(){
    int SID;
    printf("Please input the SemaphorID of the semaphor you wish to do V operation\n");
    int valid = scanf("%d", &SID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}
    while(!(SID>=0 && SID<=4)){
        printf("Please input valid SemaphorID of the semaphor you wish to do V operation\n");
        valid = scanf("%d", &SID);
        getchar();
        if(valid != 1){printf("Invalid Input\n");processX();return;}
    }

    if(SID == 0){semaphor1.value++;if(semaphor1.value<=0){unblock_semaphor(semaphor1.blocked_list);}}
    else if(SID == 1){semaphor2.value++;if(semaphor2.value<=0){unblock_semaphor(semaphor2.blocked_list);}}
    else if(SID == 2){semaphor3.value++;if(semaphor3.value<=0){unblock_semaphor(semaphor3.blocked_list);}}
    else if(SID == 3){semaphor4.value++;if(semaphor4.value<=0){unblock_semaphor(semaphor4.blocked_list);}}
    else if(SID == 4){semaphor4.value++;if(semaphor5.value<=0){unblock_semaphor(semaphor5.blocked_list);}}
    return;
}

static void processI(){
    int PID;
    printf("Please input the PID of the process you wish to get info\n");
    int valid = scanf("%d", &PID);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}

    search_all_Queue(PID);
    PCB* exist = found.process;
    if(PID == running->PID){exist = running;}
    else if(PID == 0){exist = process_init;}
    else if(found.count == 10){printf("There is no existing process in the system with the PID you provided. Help: may be you are referring to a process that used to exist\n"); return;}
    printf("Process PID = %d\n",exist->PID);
    printf("Process state = %d\n",exist->state);
    printf("Process priority = %d\n",exist->priority);
    return;
}

static void processL(){
    printf("High priority process total run = %d\n",high_cpu_burst);
    printf("Norm priority process total run = %d\n",norm_cpu_burst);
    printf("Low priority process total run = %d\n",low_cpu_burst);
    printf("Out of total CPU run %d\n",low_cpu_burst + high_cpu_burst + norm_cpu_burst);
    return;
}

static void processH(){
    printf("Enter the percentage of CPU you like for high priority process\n");
    int valid = scanf("%f", &high_desired);
    getchar();
    if(valid != 1){printf("Invalid  Input\n");processX();return;}

    printf("Please input the percentage of CPU you like for norm priority process\n");
    valid = scanf("%f", &norm_desired);
    getchar();
    if(valid != 1){printf("Invalid Input\n");processX();return;}

    printf("The percentage of CPU for low priority process will be %f\n", 100.0 - (high_desired+norm_desired));
    return;
}

static void processF(){
    if(running == process_init){printf("Failed sorry you cannot copy process_init\n");return;}
    process_count++;
    int status;
    PCB* process = (PCB *)malloc(sizeof(PCB)); 
    process->PID = process_count;
    process->priority = running->priority;
    process->state = 1;
    process->ready_to_recieve = running->ready_to_recieve;
    process->msg_recieved.sender_PID = running->msg_recieved.sender_PID;
    strcpy(process->msg_recieved.msg,running->msg_recieved.msg);
    process->reply_recieved.sender_PID = running->reply_recieved.sender_PID;
    strcpy(process->reply_recieved.msg,running->reply_recieved.msg);

    if(running->priority == 0){status = List_prepend(ready_queue_high, process);}
    else if(running->priority == 1){status = List_prepend(ready_queue_norm, process);}
    else if(running->priority == 2){status = List_prepend(ready_queue_low, process);}


    if(status == -1){printf("Sorry process creation failed no available space to accomodate new process \n");}
    else if(status == 0){
        printf("Process succesfully forked to new process with process id %d\n",process_count);
    }
    return;
}


int main(int argc, char **args)
{
    printf("---------------------------------------------------------------- Welcome to Interactive OS Simulation of this machine----------------------------------------------------------------\n");
    
    running = process_init;
    ready_queue_high = List_create();
    ready_queue_norm = List_create();
    ready_queue_low = List_create();

    sender_blocked_queue = List_create();
    reciever_blocked_queue = List_create();

    semaphor1.blocked_list = List_create();
    semaphor2.blocked_list = List_create();
    semaphor3.blocked_list = List_create();
    semaphor4.blocked_list = List_create();
    semaphor5.blocked_list = List_create();

    semaphor1.initialized = false;
    semaphor2.initialized = false;
    semaphor3.initialized = false;
    semaphor4.initialized = false;
    semaphor5.initialized = false;
    
    process_init->ready_to_recieve = false;
    strcpy(process_init->msg_recieved.msg,"");

    if(ready_queue_high == NULL || ready_queue_norm == NULL || ready_queue_low == NULL || sender_blocked_queue == NULL || reciever_blocked_queue == NULL ){
        perror("List Creation Failed!\n");
        exit(EXIT_FAILURE);
    }

    schedule_cpu();
    char command;
    while(!terminate){
        printf("Give your command\n");
        scanf("%c", &command);
        getchar();
        printf("your command %c\n",command);
	if(command == 'K'){processK();}
        if(command == 'C'){processC();}
        if(command == 'X'){processX();}
        if(command == 'T'){processT();}
        if(command == 'Q'){processQ();}
        if(command == 'E'){processE();}
        if(command == 'S'){processS();}
        if(command == 'R'){processR();}
        if(command == 'Y'){processY();}
        if(command == 'N'){processN();}
        if(command == 'P'){processP();}
        if(command == 'V'){processV();}
        if(command == 'I'){processI();}
        if(command == 'L'){processL();}
        if(command == 'H'){processH();}
        if(command == 'F'){processF();}
    }
    printf("High priority process total run = %d\n",high_cpu_burst);
    printf("Norm priority process total run = %d\n",norm_cpu_burst);
    printf("Low priority process total run = %d\n",low_cpu_burst);
    printf("Out of total CPU run %d\n",low_cpu_burst + high_cpu_burst + norm_cpu_burst);
    printf("\n---------------------------------------------------------------- ");
    printf("----------------------------------------------------------------\n");
    printf("\n");
    return 0;
}
