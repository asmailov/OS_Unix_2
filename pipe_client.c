#include "pipe_func.h"

int main()
{
	init();
	// Main cycle
	while(input != EOF)
	{
		input = getchar();
		// If "enter" is pressed print promt.
		if (input == '\n')
		{
			printPromt();
		} else
		{
			// Get commands from input.
			getCommands();
			// Parse commands.
			parseCommands();
			printPromt();
		}
	}
    return 0;
}
