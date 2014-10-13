#include "pipe_func.h"

char *userName;
char hostName[HOST_NAME_MAX];
char currDir[PATH_MAX];
char input;
char cmdBuffer[INPUT_MAX];
char *commands[CMD_MAX];

int cmdCount;

void init()
{	
	cmdCount = 0;
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
	// Getting first command from cmdBuffer
	char *command = strtok(cmdBuffer, "|");
	// Getting the rest of commands
	cmdCount = 0;
    while(command != NULL)
    {
		commands[cmdCount++] = command;
		//printf("%s\n",command);
		// Note that second time using strtok(), it's first
		// param should be NULL
        command = strtok(NULL, "|");
    }
	commands[cmdCount] = NULL;
}

void parseCommands()
{
	if(strcmp("exit", commands[0]) == 0 || strcmp("q", commands[0]) == 0)
    {
        exit(EXIT_SUCCESS);
    }

	char * temp = NULL, * cmdArgs[MAX_ARGUMENTS];
    int newPipe[2], oldPipe[2], aCount, i, status;
    pid_t pid;
	
	for(i = 0; i < cmdCount; i++) 
    {
        aCount = 0;
        //printf("%s\n",commands[i]);
        temp = strtok(commands[i], " ");
        while(temp != NULL)
        {
			//printf("%s\n",temp);
            cmdArgs[aCount++] = temp;
            temp = strtok(NULL, " ");
			
        }
        
        cmdArgs[aCount] = NULL;
        
        if(i < cmdCount-1)
        {
            pipe(newPipe); 
        }

        pid = fork();

        if(pid == 0)
        {
            if(i > 0)
            {
                close(oldPipe[1]);
                dup2(oldPipe[0], 0);
                close(oldPipe[0]);
            }
            if(i < cmdCount-1)
            {
                close(newPipe[0]);
                dup2(newPipe[1], 1);
                close(newPipe[1]);
            }
            if (execvp(cmdArgs[0], cmdArgs) == -1)
            {
                printf("Error. Command not found: %s\n", cmdArgs[0]);
            }
            exit(0);
        }
        else
        {
            if(i > 0)
            {
                close(oldPipe[0]);
                close(oldPipe[1]);
            }
            if(i < cmdCount-1)
            {
                oldPipe[0] = newPipe[0];
                oldPipe[1] = newPipe[1];
            }
            if(i == cmdCount-1)
            {
                waitpid(pid, &status, 0);
            }
        }
    }
}
