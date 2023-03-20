/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:54 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 17:29:00 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status;

void	ft_env(t_info *cmd, t_envp *head)
{
	t_envp	*tmp;

	tmp = head;
	if (cmd->next != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd->next->cmd);
		g_exit_status = 127;
		return ;
	}
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_last_exit_code = 0;
	return ;
}
