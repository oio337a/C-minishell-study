#include "../includes/minishell.c"

void	errno_print(char *cmd, int errnum, char *string)
{
	errno = errnum;
	if (cmd != NULL && string != NULL && errno != 0)
		printf("%s: %s: %s", cmd, string, strerror(errno));
	if (cmd != NULL && char == NULL)
		printf("%s: %s", cmd, strerror(errno));
}