/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:34 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 14:33:24 by yongmipa         ###   ########seoul.kr  */
=======
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:34 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/12 18:45:52 by sohyupar         ###   ########.fr       */
>>>>>>> d99338a6d7d05c94f9cfd9fece4e458504baf720
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_info	*init_list(void)
{
	t_info	*info;

	info = (t_info *)ft_safe_malloc(sizeof(t_info));
	info->next = NULL;
	info->cmd = NULL;
	info->type = 0;
	return (info);
}

void	insert_list(t_info *info, char *cmd, int type)
{
	t_info	*head;

	head = info;
	if (head->cmd == NULL)
	{
		head->cmd = ft_strdup(cmd);
		head->type = type;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = (t_info *)ft_safe_malloc(sizeof(t_info));
		head->next->cmd = ft_strdup(cmd);
		head->next->type = type;
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

int	list_size(t_info *info)
{
	t_info	*head;
	int		i;

	head = info;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	cmd_size(t_info *info)
{
	t_info	*head;
	int		i;

	head = info;
	i = 0;
	while (head && (head->type != REDIR_IN) || (head->type != REDIR_OUT) || head->type != HEREDOC_IN || head->type != HEREDOC_IN)
	{
		i++;
		head = head->next;
	}
	return (i);
}
