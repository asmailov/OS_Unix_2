#include "pipe_func.h"

int main( int argc, char *argv[] )
{
	init();
    if ((argc > 1) && (strcmp(argv[1], "-d") == 0))
    {
        debug = 1;
    } else 
    {
        debug = 0;
    }
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
