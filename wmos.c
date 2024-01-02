#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//Creating a shell with basic in-built functions(cd ,info ,exit) (WMOSv1.0)
//NOTE: This is just a implementation of "brenns lsh shell" (but reduced some system call complexities) 

void cmd_loop();                       //cmd_loop == commands (reading command ,separatig command string and args,executing parse command) 
char *input_line();                    //reading input from user
char **div_ln_to_args(char *line);     // splitting line into arguments
int launch_shell(char **args);         //launching shell by forking process
int exe_args(char **args);             //executing arguments in shell 

int main(int argc ,char **argv){
   cmd_loop();
}

void cmd_loop(){
   char *line;                         //storing the input line by user eg: ls, clear, etc
   char **args;                        //divide the line into arguments
   int status;                         //for exiting the shell 

do {
   printf("-> ");
   line = input_line();
   args = div_ln_to_args(line);
   status = exe_args(args);

   
} while(status);

}

//reading line
char *input_line(){
int buffer_size = 256;
int position = 0;
char *buffer_mem = malloc(sizeof(char) * buffer_size);
int check_char;

while(true){
   check_char = getchar();
   if (check_char == EOF || check_char == '\n'){
      buffer_mem[position] = '\0';
      return buffer_mem;
   } 
   else{
      buffer_mem[position] = check_char;
   } 
   position++;
}

if(position > buffer_size){
   printf("exceeded limit\n");
   exit(EXIT_FAILURE);
}

}

//dividing input into arguments

char **div_ln_to_args(char *line){
   int token_buffer = 100;
   char *token_delimiter = {" \t\r\n\a"};
   int position = 0;
   char **tokens = malloc(sizeof(char*) * token_buffer);
   char *token;

   token = strtok(line,token_delimiter);

   while(token != NULL){
      tokens[position] = token;
      position++;
   
   if(position >token_buffer){
      exit(EXIT_FAILURE);
   }

   token = strtok(NULL,token_delimiter);
} 

tokens[position]= NULL;
return tokens;
   
}

int launch_shell(char **args){
   pid_t pid, wpid;
   int status;

   pid = fork();
   if(pid == 0){
      if(execvp(args[0],args)==-1){
         perror("no command\n");
      }
      exit(EXIT_FAILURE);
   }
   else{
      wait();
   }
   return 1;
}

int cd(char **args);
int info(char **args);
int sh_exit(char **args); 

char *builtin_cmds[] = {"cd","info","exit"};

int (*builtin_func[]) (char **) = {
   &cd, &info, &sh_exit
};

int builtins() {
   return sizeof(builtin_cmds) / sizeof(char *);
}

int cd(char **args){
   if(args[1] == NULL){
      fprintf(stderr,"expected arg after cd\n");
   } else {
      if(!chdir(args[1])){
         perror("error");
      }
   }
   return 1;
}

int info(char **args){
  printf("-> Tried to wrote a shell with help of \"brenns lsh implementation also reduced certain complexities of system call fucntions\n");
  printf("-> Written By Muhammad Mustafa \n");
  printf("-> It may have bugs or warnings \n");

}

int sh_exit(char **args){
   return 0;
}

int exe_args(char **args){

   if(args[0] == NULL){
      return -1;
   }

   for(int i = 0; i<builtins(); i++){
      if(strcmp(args[0],builtin_cmds[i])==0){
         return (*builtin_func[i])(args);
      }
   }
   return launch_shell(args);
}










