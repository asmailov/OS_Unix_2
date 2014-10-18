#include "pipe_func.h"

char *userName;
char hostName[HOST_NAME_MAX];
char currDir[PATH_MAX];
char input;
char cmdBuffer[INPUT_MAX];
char tmpBuffer[INPUT_MAX];
char *commands[CMD_MAX];
char *tmpCommands[CMD_MAX];

int cmdCount;
int pipes;
int debug;

void init()
{	
    debug = 0;
    // Make kernel automatically reap children processes
    signal(SIGCHLD, SIG_IGN);
    cmdCount = 0;
    input = '\0';
    // Getting username, hostname and currDir
    userName = getenv("USER");
    gethostname(hostName, HOST_NAME_MAX);

    printWelcome();
    printPromt();
}

void printWelcome()
{
    puts("");
    puts("Jus sveikina:");
    puts("IV kurso, I grupės");
    puts("Informatikos (matematinės info) studentas,");
    puts("Aleksandr Šmailov");
    puts("Sėkmės naudojantis mano shell'u.");
    puts("");
}

void printPromt()
{
    getcwd(currDir, PATH_MAX);
    printf("%s@%s:~%s$ ", userName, hostName, currDir);
}

void getCommands()
{
    int i = 0;
    
    /* Write input to cmd buffer until "new line" character
       is found or counter is over INPUT_MAX constant. */
    while(input != '\n' && i <= INPUT_MAX)
    {
        cmdBuffer[i] = input;
        i++;
        input = getchar();
    }
    cmdBuffer[i] = '\0';
    strcpy(tmpBuffer, cmdBuffer);
    // Getting first command from cmdBuffer
    char *command = strtok(cmdBuffer, "|");
    // Getting the rest of commands
    cmdCount = 0;
    while(command != NULL)
    {
        commands[cmdCount++] = command;
        // Note that second time using strtok(), it's first
        // param should be NULL
        command = strtok(NULL, "|");
    }
    commands[cmdCount] = NULL;
    
    command = strtok(tmpBuffer, "|");
    cmdCount = 0;
    while(command != NULL)
    {
        tmpCommands[cmdCount++] = command;
        // Note that second time using strtok(), it's first
        // param should be NULL
        command = strtok(NULL, "|");
    }
    tmpCommands[cmdCount] = NULL;
}

void parseCommands()
{	
    char * temp = NULL, * cmdArgs[MAX_ARGUMENTS];
    int count = 0;
    temp = strtok(tmpCommands[0], " ");
    while(temp != NULL)
    {
        cmdArgs[count++] = temp;
        temp = strtok(NULL, " ");
    }

    // Parse exit, q commands.
    if(strcmp("exit", cmdArgs[0]) == 0 || strcmp("q", cmdArgs[0]) == 0)
    {
        exit(EXIT_SUCCESS);
    }

    // Parse cd command.
    if(strcmp("cd", cmdArgs[0]) == 0)
    {
        if(cmdArgs[1] == NULL)
        {
            chdir(getenv("HOME"));
        }
        else
        {
            
            if(chdir(cmdArgs[1]) == -1)
            {
                 printf("cd: %s: No such directory\n", cmdArgs[1]);
            }
        }
        return;
    }
    createPipes();
}

void createPipes()
{
    char * temp = NULL, * cmdArgs[MAX_ARGUMENTS];
    int newPipe[2], oldPipe[2], argCount, i, status;
    pid_t pid;
    for(i = 0; i < cmdCount; i++) 
    {
        argCount = 0;
        // Split exec and arguments.
        temp = strtok(commands[i], " ");
        //printf("%s\n", commands[i]);
        while(temp != NULL)
        {
            cmdArgs[argCount++] = temp;
            temp = strtok(NULL, " ");
        }
        cmdArgs[argCount] = NULL;
        int j=0;
        // If debug is turned on, type commands and their arguments.
        if (debug == 1)
        {
            for (j = 0; j < argCount; j++)
            {
                printf("%i cmd, %i arg: %s\n",i+1,j+1,cmdArgs[j]);
            }
        }
        // Create new pipes until we get to last command.
        if(i < cmdCount-1)
        {
            pipe(newPipe); 
        }
        // Fork new child process and exit if error occurs.
        if((pid = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }
        // Child process
        if(pid == 0)
        {
            // If i>0 one pipe was already made.
            if(i > 0)
            {
                // Child process closes up output side of oldPipe.
                close(oldPipe[1]);
                // Input descriptor of the oldPipe is duplicated onto its standart input.
                dup2(oldPipe[0], 0);
                // Child process closes up input side of oldPipe.
                // close(oldPipe[0]);
            }
            // Executed until last command.
            if(i < cmdCount-1)
            {
                // Child process closes up input side of newPipe.
                close(newPipe[0]);
                // Output descriptor of the newPipe is duplicated onto its standart output.
                dup2(newPipe[1], 1);
                // Child process closes up output side of newPipe.
                // close(newPipe[1]);
            }
            // This new executed prog will have input side of the pipe as its standart input.
            if (execvp(cmdArgs[0], cmdArgs) == -1)
            {
                printf("Error. Command not found: %s\n", cmdArgs[0]);
            }
            exit(0);
        }
        else
        // Parent process.
        {
            if(i > 0)
            {
                // Remove oldPipe descriptors, since we don't need them anymore.
                close(oldPipe[0]);
                close(oldPipe[1]);
            }
            if(i < cmdCount-1)
            {
                // Currently new, but soon to be old pipe descriptors are
                // saved so we can close() and dub() later on.
                oldPipe[0] = newPipe[0];
                oldPipe[1] = newPipe[1];
            }
            // At the last command we wait for child.
            if(i == cmdCount-1)
            {
                waitpid(pid, &status, 0);
            }
            
        }
    }
}
