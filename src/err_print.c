#include "../includes/minishell.c"

void	errno_print(char *cmd, int errnum, char *string)
{
	errno = errnum;
	if (cmd != NULL && string != NULL && errno != 0)
		printf("%s: %s: %s", cmd, string, strerror(errno));
	if (cmd != NULL && char == NULL)
		printf("%s: %s", cmd, strerror(errno));
}

// void	errno_toomany(char *cmd)
// {
// 	printf("%s: too many arguments\n", cmd);
// }

// void	errno_numeric(char *cmd, char *string)
// {
// 	printf("%s: %s: numeric argument required", cmd, string);
// }