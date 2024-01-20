# WMOS-v1.0
# (Write My Own Shell)
A basic shell in C <br>
Note: This shell is modified version of "Stephen Brennan" lsh <br>
v1.0 -> Improved some system call complexities but may have some bugs and warnings which to lookout for  

## Working:
After the command is enetred in shell it stores it into and array of characters including the newline and NULL which determines the end of string and stores it in the memory then the shell passes the command line into the **parser**. The parser does numerous things such as removing newline character and replacing with NULL char. The shell separates the command line into an array of strings using the **space** as the delimiter. This process is called **tokenization** and each string is referred as token
eg: {"ls", "a" }. After this the **Executor** takes the string and creates a new process from it but before creating a new process it checks for the **built-in** commands. Shell comes with some builtin commands, they are usually stored in an array of structs (usually consist of two elements name of command and a pointer to the appropiate fucntion). If not, it checks the command provided is not a path then it tries to look for the exe file with the command name in the **envoirmentable variable** path. This variable contains list of path where program are stored if the command is found in the path variable, then it creates a new process to run the command. When the command is found it gets replaced by where it is found eg: **ls** is found in **/bin** now the string of array {"/bin/ls", "a"}.The new process is created with the help of **fork()** system call which is identical to the parent process. Now, two process are running the shell makes another system call in the child process **execv** to execute program and parent process wait till the child process is completed with **wait()**.The parent class waits for the status code for the child process is successful or not.             

## Shell Components
### 1. Parser
Firstly, This is the component that takes the command line and splits it into tokens.
eg: ls -a -> {"ls","a"}

### 2. Executor
This uses the array of strings and creates new child process for execution of it. 


