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
/*process generator
/ returns a 0 for child
/ returns a 1 for original parent
/ returns a -1 for failure
*/
int PG(int n){
    //if the processes have all been created, then return that you are a child
    if(n == 0){
         return 0;
    }
    //init the randomizer
    srand(time(NULL));
    //prepare a randomly sized chunk to be created.
    int chunk = rand() % n + 1;
    //Remove this from n.
    n = n - chunk;
    //we are the first child    
    bool firstChild = true;
    //so long as there are still processes left in chunk, repeat.
    while(chunk > 0){
         //decrement chunk       
         chunk --;
         //fork!
         pid_t forkedChild = fork();
         //now the process deviates into different processes. Here we check if fork() returned 0 for a child
         if(forkedChild == 0){
              //if we are the first child, then we recurse on the PG call with our n = n-chunk          
              if(firstChild){
                    //keep result
                    int result = PG(n);
                    //check if the fork failed for some reason.
                    if(result == -1){
                         return -1;
                    }
              }
              //return 0 for both non-first children, and first children
              return 0;
         }
         // if the fork returned a -1, then it failed
         if(forkedChild == -1){
              return -1;
         }
         //make sure that on the next pass, we are working as a secondary child
         firstChild = false;               
    }
    // return as parent
    return 1;
}

int main(int argc, char* argv[]){ 
    printf("Creating this many child processes: %s\n ", argv[1]);
    //create all the processes
    int result = PG(atoi(argv[1]));
    //we are in a child
    if(result == 0){ 
    while(1){
      }
    } else if (result < 0){
      //error
      printf("Error creating a child");
    } 
    //string that represents the menu. Options are selected by typing in the string.
   	const char* prompt = "\nPlease choose one of the following process operations by name: \n\n 1. list \n 2. suspend \n 3. resume \n 4. terminate \n 5. exit \n > ";
    //from the process PIDs selectr one that is valid
    const char* processID = "Please enter a valid PID >";
    //loop on bailout != 0 until we exit
	  int bailout = 0;
	  while (!bailout) {
     //read in the user's input and then go to each case.
     char* reply = readline(prompt);
     printf("\nYou selected: %s\n", reply);
     if (!strcmp(reply, "list")) { //list all processes in the process tree
          printf("Listing all processes: \n");
          system("ps -f | head -1");//display the header row
          system("ps -f | grep jorinw");//display the rows of processes
     }
     else if (!strcmp(reply, "suspend")) { //suspend processes by PID
          int pid = atoi(readline(processID));
          if(pid > 1){
                 printf("Suspending process: %i\n", pid);
                 if(!kill(pid, SIGSTOP) == 0){
                      printf("Suspend failed.");
                 }
                 
          } else {
            printf("Invalid PID.\n");
          }
     }
     else if (!strcmp(reply, "resume")) { //resume processes by PID
          int pid = atoi(readline(processID));
           if(pid > 1){
                 printf("Resuming process: %i\n", pid);
                 if(!kill(pid, SIGCONT) == 0){
                      printf("Resume failed.");
                 }
          } else {
            printf("Invalid PID.\n");
          }
     }
     else if (!strcmp(reply, "terminate")) { //terminate processes by PID
          int pid = atoi(readline(processID));
          if(pid > 1){
                 printf("Terminating process: %i\n", pid);
                 if(!kill(pid, SIGTERM) == 0){
                      printf("Terminate failed.");
                 }
          } else {
            printf("Invalid PID");
          }
     }
     else if (!strcmp(reply, "exit")) { //exit and terminate all processes
			bailout = 1;
     } 
	   else {
			printf("This is not a valid option, try again please");
		 }
      free(reply);
    }
    printf("Exiting\n");
    //kill off all the processes in the tree
    system("killall PMS");
}

