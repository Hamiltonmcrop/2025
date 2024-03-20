#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "list.h"


int main(int argc, char **argv){

	initial_create();
	end = 0;

	while(1){

		int priority;
		int pid;
		int sid;
		int value;
		char * msg = malloc(40*sizeof(char));
		char command;
		char state = '\0';

		if(end == 0){
		
			printf("Enter a command (C, F, K, E, Q, S, R, Y, N, P, V, I, T): ");
			scanf(" %c", &command);
			//printf("command is: %c\n", command);

			if(command == 'C'){
				state = 'C';
			}else if(command == 'F'){
				state = 'F';
			}else if(command == 'K'){
				state = 'K';
			}else if(command == 'E'){
				state = 'E';
			}else if(command == 'Q'){
				state = 'Q';
			}else if(command == 'S'){
				state = 'S';
			}else if(command == 'R'){
				state = 'R';
			}else if(command == 'Y'){
				state = 'Y';
			}else if(command == 'N'){
				state = 'N';
			}else if(command == 'P'){
				state = 'P';
			}else if(command == 'V'){
				state = 'V';
			}else if(command == 'I'){
				state = 'I';
			}else if(command == 'T'){
				state = 'T';
			}else if(command == '\n'){
				continue;
			}else{
				printf("Error! Command is not correct! Please re-enter a command!\n");
			}
			
			

		    if(state == 'C'){

		    	printf("Enter the priority (0=high, 1=normal, 2=lwo): ");
		    	scanf("%d", &priority);

		    	while(1){

		    		fflush(stdin);

					if(priority == 0){
						//printf("In 0\n");
			         	PCB_create(0);
			         	break;
		         	}else if(priority == 1){
		         		//printf("In 1\n");
		         		PCB_create(1);
		         		break;
		         	}else if(priority == 2){
		         		//printf("In 2\n");
		         		PCB_create(2);
		         		break;
		         	}else{
		         		printf("Error! Invalid priority! Re-enter:\n");
		         		scanf("%d", &priority);
		         	}	 
		    	}
		    
		    }else if(state == 'F'){

		    	PCB_fork();
		    
		    }else if(state == 'K'){

		    	printf("Enter the pid of process to be killed: ");
		    	scanf(" %d", &pid);

		    	while(1){

		    		if(pid > 0){	// 0 is the init_process
		    			PCB_kill(pid);
		    			break;
		    		}else{
		    			printf("Error! Invalid pid! Re-enter pid:\n");
		         		scanf(" %d", &pid);
		    		}

		    	}
		    	
		    }else if(state == 'E'){

		    	PCB_exit();

		    }else if(state == 'Q'){

		    	PCB_quantum();

		    }else if(state == 'S'){

		    	printf("Enter the pid of process to send the message to: ");
		    	scanf(" %d", &pid);
		    	getchar();

		    	while(1){

		    	
		    		if(pid >= 0){	// 0 is the init_process
		    			printf("Enter the message (limited to 40 char): ");
		    			//scanf("%[^\n]s", msg);
		    			fgets(msg, 40, stdin);
		    			//printf("%s\n", msg);
		    			PCB_send(pid, msg);
		    			break;
		    		}else{
		    			printf("Error! Invalid pid! Re-enter pid:\n");
		         		scanf(" %d", &pid);
		    		}

		    	}	
		    	
		    }else if(state == 'R'){
		    	PCB_receive();
		   
		    }else if(state == 'Y'){

		    	printf("Enter the pid of process to reply the message to: ");
		    	scanf(" %d", &pid);
		    	getchar();

		    	while(1){

		    		fflush(stdin);

		    		if(pid > 0){	// 0 is the init_process
		    			printf("Enter the reply (limited to 40 char): ");
		    			fgets(msg, 40, stdin);
		    			PCB_reply(pid, msg);
		    			break;
		    		}else{
		    			printf("Error! Invalid pid! Re-enter pid:\n");
		         		scanf(" %d", &pid);
		    		}

		    	}	
		    
		    }else if(state == 'N'){

		    	printf("Enter the ID of the new semaphore (from 0 to 4): ");
		    	scanf(" %d", &sid);

		    	while(1){

		    		fflush(stdin);
		    		if(sid >= 0 && sid <= 4){
		    			printf("Enter a value to initialize the new semaphore (0 or higher): \n");
		    			scanf(" %d", &value);
		    			SEM_new(sid, value);
		    			break;
		    		}else{
		    			printf("Error! Invalid ID! Re-enter a new semaphore ID:\n");
		    			scanf(" %d", &sid);
		    		}
		    	}
		    
		    }else if(state == 'P'){

		    	printf("Enter the ID of the semaphore (from 0 to 4): ");
		    	scanf(" %d", &sid);

		    	while(1){

		    		fflush(stdin);
		    		if(sid >= 0 && sid <= 4){
		    			P(sid);
		    			break;
		    		}else{
		    			printf("Error! Invalid ID! Re-enter a new semaphore ID:\n");
		    			scanf(" %d", &sid);
		    		}
		    	}

		    }else if(state == 'V'){

		    	printf("Enter the ID of the semaphore (from 0 to 4): ");
		    	scanf(" %d", &sid);

		    	while(1){

		    		fflush(stdin);
		    		if(sid >= 0 && sid <= 4){
		    			V(sid);
		    			break;
		    		}else{
		    			printf("Error! Invalid ID! Re-enter a new semaphore ID:\n");
		    			scanf(" %d", &sid);
		    		}
		    	}
		    }else if(state == 'I'){

		    	printf("Enter the pid of process to see its information: ");
		    	scanf(" %d", &pid);

		    	while(1){

		    		if(pid > 0){	// 0 is the init_process
		    			PCB_Procinfo(pid);
		    			break;
		    		}else{
		    			printf("Error! Invalid pid! Re-enter pid:\n");
		         		scanf(" %d", &pid);
		    		}

		    	}
		    	
		    }else if(state == 'T'){
		    	Totalinfo();
		    }


		    free(msg);

		}else{
			free(msg);
			exit(0);
		}
	}

}



