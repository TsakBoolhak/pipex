#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	char *str = malloc(-1);
	perror(NULL);
	return (0);
}
