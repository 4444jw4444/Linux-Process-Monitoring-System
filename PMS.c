#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <signal.h>
typedef int bool;
#define true 1
#define false 0
//process generator
//returns a 0 for child
//returns a 1 for original parent
//returns a -1 for failure
int PG(int n){
    if(n == 0){
         return 0;
    }
    
    int chunk = 3;
    
    n = n - chunk;
    
    bool firstChild = true;
    
    while(chunk > 0){
    
         chunk --;
         
         pid_t forkedChild = fork();
         
         if(forkedChild == -1){
              return -1;
         }
         
         if(forkedChild == 0){
              if(firstChild){
                    int result = PG(n);
                    
                    if(result == -1){
                         return -1;
                    }
              }
              return 1;
         }
         firstChild = false;               
    }
    return 1;
    /*int pid = fork();
    n--;
    if(n==0){
             return 0;
    } 
    
    return 1;// parent
    
    /*int pid;
    int i;
    for(i = 0; i < n; i++){
            pid = fork();
            if(pid < 0){
                   return -1;
            }
    }
    return 1;    
    return pid;    */
}

int main(int argc, char* argv[]){ 
    printf("Creating this many child processes: %s\n ", argv[1]);
    //create all the processes
    int result = PG(atoi(argv[1]));
    if(result == 0){ //we are in a child
      while(1){
      }
    } else if (result < 0){
      //error
    } // otherwise we are in parent
    //delete this (its from sample and just exits correctly
    const char* prompt = "shell> ";

	int bailout = 0;
	while (!bailout) {

		char* reply = readline(prompt);
		/* Note that readline strips away the final \n */
		/* For Perl junkies, readline automatically chomps the line read */

		if (!strcmp(reply, "bye")) {
			bailout = 1;
		} else {
			printf("\nYou said: %s\n\n", reply);
		}
		free(reply);
	}
	printf("Bye Bye\n");
    
    
    /*
    printf("\nChild process ID is : %i ", result);
    
   	const char* prompt = "\nPlease choose one of the following process operations by name: \n\n 1. list \n 2. suspend \n 3. resume \n 4. terminate \n 5. exit \n > ";
    
    const char* processID = "Please enter a valid PID >";
    
	  int bailout = 0;
	  while (!bailout) {

     char* reply = readline(prompt);
     printf("\nYou selected: %s\n", reply);
     if (!strcmp(reply, "list")) { //list all processes in the process tree
        printf("Listing all processes: \n");
     }
     else if (!strcmp(reply, "suspend")) { //suspend processes by PID
          char* pid = readline(processID);
          printf("Suspending process: %s\n", pid);
     }
     else if (!strcmp(reply, "resume")) { //resume processes by PID
          char* pid = readline(processID);
          printf("Resuming process: %s\n", pid);
     }
     else if (!strcmp(reply, "terminate")) { //terminate processes by PID
          int pid = atoi(readline(processID));
          if(pid != 0){
                 printf("Terminating process: %i\n", pid);
                 int retVal = kill(pid, SIGTERM);
          } else {
            printf("Invalid PID:  Reason: not an integer");
          }
     }
     else if (!strcmp(reply, "exit")) { //exit and terminate all processes
			bailout = 1;
      //kill off all the processes in the tree
      //int retVal = kill(result, SIGTERM);
     } 
	   else {
			printf("This is not a valid option, try again please");
		 }
      free(reply);
    }
    printf("Bye Bye\n");
    */
}

