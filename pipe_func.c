#include "pipe_func.h"

void init()
{
	userName = getenv("USER");
	gethostname(hostName, HOST_NAME_MAX);
	getcwd(currDir, PATH_MAX);
	printf("%s@%s:~%s$ ", userName, hostName, currDir);
}
