#include "../includes/minishell.h"

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

int	ft_strchr_int(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if ((s[i]) == c)
		return (i);
	return (-1);
}
