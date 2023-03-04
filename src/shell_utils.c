#include "./includes/minishell.h"

void	print_error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	exit(errnum);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
