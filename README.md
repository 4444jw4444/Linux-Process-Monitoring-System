# PMS
Process Management System

This application generates and monitors process forks. These forks are monitoring and provide heartbeat information as feedback to the CLI.

To test the application you will have to create a new folder and download it there. Use the compilation command "make -f MakeFile" to compile the source into your folder. To run the application you only need to specify the number of processes that you would like to create x as in the following run command: "./PMS x". From there the application creates a random tree of x processes, and you will be presented with a CLI interface that will guide you through your options. 

Please input your selection:
 1. List
 2. Suspend
 3. Resume
 4. Terminate
 5. Exit

Listing the processes will display information about the tree structure of the processes.
Suspending a process by PID will pause, but not permanently stop the process. 
Resuming a process by PID will resume a process that is Suspended
Terminating a process by PID will kill a process. 
Exiting leaves the program and kills all children of the root. 

The UI specified above is not fully descriptive of the options that appear in the application. 
