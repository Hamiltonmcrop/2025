 
#include "shell.h"
 
//Learning objectives:
 
//1. Functionality of pipe, close, read, and write syscalls for IPC
 
//2. Functionality of  fork, exec*, and wait syscalls for creating a child process
 
/*shell program:
 
**    1. It receives the name and CLAs of a program/executable
 
****    1.1. The only optional flag is -i meaning that child gets input from parent
 
**    2. It forks a child process
 
**    3. If -i exists, it passes the user's input (from stdin) to the child process
 
**    4. It waits for child to run the program
 
**    5. It prints the child's output on stdout and exits
 
*/
 
int main(int argc, char** argv){
 
    if(argc < 2)
 
        error("shell: Fatal error. Usage: ./shell [-i] my_executble [CLAs]", 1);
 
    int child_input = !strcmp(argv[1], "-i");
 
    if(child_input)
 
        argv++;
 
    int nbytes;
 
    char* ipc_buf;//used to store data received from child!
 
    int link_to_child[2];//two FDs, will use second one to send data
 
    if (pipe(link_to_child) < 0)
 
        error("shell: Fatal error. Unable to make a pipe to send data to child!", 2);
 
    int link_from_child[2];//two FDs, will use first one to receive data
 
    if (pipe(link_from_child) < 0)
 
        error("shell: Fatal error. Unable to make a pipe to receive data from child!", 3);
 
    pid_t pid;//define a process id to identify the child process
 
    if ((pid = fork()) == -1)
 
        error("shell: Fatal error. Cannot fork a child process!", 4);
 
    if(pid){//parent process!
 
        close(link_to_child[0]);//Close first FD as it won't be used by parent.
 
        close(link_from_child[1]);//Close second FD as it won't be used by parent.
 
        char* input = (char*)malloc(MAX_INPUT_SIZE);
 
        ipc_buf = (char*)malloc(IPC_BUF_SIZE);
 
        int i = 0;
 
        //storing program's stdin stream in input buffer
 
        if(child_input){
 
            fprintf(stderr, "shell: provide input for process %s: \n", argv[1]);
 
            while((input[i++] = getchar()) != EOF);
 
            write(link_to_child[1],input, i-1);//send the input to child process
 
        }
 
        close(link_to_child[1]);//done with sending input to child
 
        nbytes = read(link_from_child[0], ipc_buf,
 
            IPC_BUF_SIZE);//receive data from child process and store it in ipc_buf
 
        if(nbytes == -1)
 
            error("shell: Fatal Error. can't receive data from child process", 5);
 
        else 
 
            ipc_buf[nbytes] = '\0';//transform ipc_buf into a string of chars
 
        wait(NULL);//wait for child to finish its process
 
        fprintf(stderr, "shell: data received from %s:\n[[%s]]\n", argv[1], ipc_buf);
 
    }else{//child process which is a clone of its parent!
 
        close(link_from_child[0]);//child doesn't use this end!
 
        close(link_to_child[1]);//child doesn't use this end!
 
        //child redirects its stdin to the first FD of link_to_child
 
        dup2 (link_to_child[0], STDIN_FILENO);//child uses this end to receive data from parent
 
        //child redirects its stdout to the second FD of link_from_child
 
        dup2 (link_from_child[1], STDOUT_FILENO);//child uses this to send data to parent
 
        close(link_to_child[0]);
 
        close(link_from_child[1]);
 
        execv(argv[1], argv+1);//replace child's text section with the code of requested process
 
        //if execv fails, child continues with the following lines...
 
        char* message = (char*) malloc(1000);
 
        sprintf(message, "Failed to run %s with args: ", argv[1]);
 
        argv+=2;
 
        while(*argv)
 
            sprintf(message, "%s %s", message, *argv);
 
        error(message,6);
 
    }
 
    exit(0);//no error
 
}

