#include "pipe_func.h"

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
    while(command != NULL)
    {
		commands[cmdCount++] = command;
		// Note that second time using strtok(), it's first
		// param should be NULL
        command = strtok(NULL, "|");
    }
}
