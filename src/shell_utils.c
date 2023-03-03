#include "./includes/minishell.h"

void	print_error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	exit(errnum);
}