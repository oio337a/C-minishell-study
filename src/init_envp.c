#include "../includes/minishell.h"

t_envp	*init_envp(void)
{
	t_envp	*envp;

	envp = (t_envp *)ft_safe_malloc(sizeof(t_envp));
	envp->next = NULL;
	envp->key = NULL;
	envp->value = NULL;
	return (envp);
}

void	insert_envp(t_envp *envp, char *key, char *value)
{
	t_envp	*head;

	head = envp;
	if (head->key == NULL)
	{
		head->key = ft_strdup(key);
		head->value = ft_strdup(value);
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = (t_envp *)ft_safe_malloc(sizeof(t_envp));
		head->next->key = ft_strdup(key);
		head->next->value = ft_strdup(value);
		head->next->next = NULL;
	}
}

void	delete_envp(t_envp *head, t_envp *del)
{
	t_envp	*tmp;

	while (tmp->next != del) //del 전 노드 찾기
		tmp = tmp->next;
	//이제 tmp->next == del
	tmp->next = tmp->next->next;
	free(del->key);
	free(del->value);
	free(del);
}

void	delete_envp_all(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = (*envp)->next;
		free((*envp)->key);
		free((*envp)->value);
		free(*envp);
		*envp = tmp;
	}
}

t_envp	*set_envp(char **envp)
{
	t_envp	*head;
	t_envp	*new;
	char	**arr;
	int		i;
	int		j;

	i = 0;
	head = init_envp();
	while (envp[i])
	{
		j = ft_strchr_int(envp[i], '=');
		arr = (char **)ft_safe_malloc(2 * sizeof(char *));
		arr[0] = ft_substr(envp[i], 0, j);
		arr[1] = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j + 1);
		insert_envp(head, arr[0], arr[1]);
		free(arr[0]);
		free(arr[1]);
		free(arr);
		i++;
	}
	return (head);
}

// int	main(int ac, char **av, char **envp) //test 메인문
// {
// 	int i = 0;
// 	t_envp	*head;

// 	head = set_envp(envp);
// 	printf("////////////////////////\n");
// 	printf("original output\n");
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// 	printf("////////////////////////\n");
// 	printf("ft_env output\n");
// 	ft_env(head);
// 	return 0;
// }
