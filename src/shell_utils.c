#include "./includes/minishell.h"

void	print_error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	exit(errnum);
}

t_envp	*init_env(char **envp)
{
	t_envp	*ret;
	int	i;
	int	j;

	i = 0;
	ret = ft_safe_malloc(sizeof(t_envp *));
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			envp[i][j] = 
			if (envp[i][j] == '=')
				;
		}
	}
}