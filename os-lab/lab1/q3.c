#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int val =10;  
// Function to take input
int Input(char* str)
{
    char buf[100];
    printf("\n$");

    scanf("%[^\n]%*c", buf);
    if (strlen(buf) != 0) {
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
// Function where the system command is executed
void execute(char** parsed)
{
    // Forking a child
    pid_t pid = fork(); 
  
    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}

int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }
  
    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}
// function for parsing command words
void parseSpace(char* str, char** parsed)
{
    int i;
  
    for (i = 0; i < 100; i++) {
        parsed[i] = strsep(&str, " ");
  
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            break;
    }
}
int command(char** parsed)
{
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;
  
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
  
    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
  
    switch (switchOwnArg) {
    case 1:
        printf("\nExiting shell\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    default:
        break;
    }
  
    return 0;
}

void executePiped(char** res, char** parsedpipe)
{
    int resFd[2];
    pid_t pipe1,pipe2;

    pipe1 = fork();
    if(pipe(resFd)<0)
    {
        // printf("Forking failed.");
        return;
    }

    if(pipe1==0)
    {
        close(resFd[0]);
        dup2(resFd[1], STDOUT_FILENO);
        close(resFd[1]);

        if(execvp(res[0], res) < 0)
        {
            exit(0);
        }
    }
    else
    {
        pipe2 = fork();

        if(pipe2<0)
        {
            return;
        }

        if(pipe2==0)
        {
            close(resFd[1]);
            dup2(resFd[0], STDIN_FILENO);
            close(resFd[0]);

            if(execvp(parsedpipe[0], parsedpipe) < 0)
            {
                exit(0);
            }
        }
        else
        {
            wait(NULL);
            wait(NULL);
        }
    }
}

int processString(char* str, char** parsed, char** parsedpipe)
{
  
    char* pipeStrings[2];
    int pipe_exec = 0;
  
    pipe_exec = parsePipe(str, pipeStrings);
  
    if (pipe_exec) {
        parseSpace(pipeStrings[0], parsed);
        parseSpace(pipeStrings[1], parsedpipe);
  
    } else {
  
        parseSpace(str, parsed);
    }
  
    if (command(parsed))
        return 0;
    else
        return 1 + pipe_exec;
} 

void sigint_handler()
{
    printf("\nKilling the current process");
    printf("\n$abc");
}

void sigchld_handler(int sig)
{
    val+= 5;
}
int main()
{
    
    char input[1000], *parsed[100];
    char* parsedPiped[100];

    // pid_t pid;
    
    //     signal(SIGCHLD, sigchld_handler);
    //     if ((pid = fork()) == 0)
    //     {
    //         // val -= 3;
    //         exit(0);
    //     }
    //     waitpid(pid, NULL, 0);

    printf("\t****Starting shell****");
  
    while (1) {
        
        signal(SIGINT, sigint_handler);  //ctrl -c
        
        char pwd[1024];
        getcwd(pwd, sizeof(pwd));
        printf("\nPath: %s", pwd);

        // for user input
        if (Input(input))
            continue;

        // flag for process in execution 
        int execCount = processString(input,
        parsed, parsedPiped);
        
        if (execCount == 1)
            execute(parsed);
  
        if (execCount == 2)
            executePiped(parsed, parsedPiped);
        
    }
    return 0;
}