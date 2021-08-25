#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *const av[], char *const envp[])
{
//	char *const cmd[] = {"echo", "$0", NULL};
//	execve("/bin/echo", cmd, envp);
//	perror(NULL);
	char *name = getenv("O");
	if (name)
		printf("%s\n", name);
	return (0);
}
