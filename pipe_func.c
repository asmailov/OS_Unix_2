#include "pipe_func.h"

void init()
{	
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
}
