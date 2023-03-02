#include "../includes/minishell.h"

void	init_list(t_info *info)
{
	if (info == NULL)
		info = (t_info *)ft_safe_malloc(sizeof(t_info));
	info->next = NULL;
	info->cmd = NULL;
}

void	insert_list(t_info *info, char *cmd)
{
	t_info	*head;

	head = info;
	if (head->cmd == NULL)
	{
		head->next = NULL;
		head->cmd = ft_strdup(cmd);
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = (t_info *)ft_safe_malloc(sizeof(t_info));
		head->next->cmd = ft_strdup(cmd);
		head->next->next = NULL;
	}
}

void	list_delete(t_info **info)
{
	t_info	*tmp;

	while (*info)
	{
		tmp = (*info)->next;
		free((*info)->cmd);
		free(*info);
		*info = tmp;
	}
}