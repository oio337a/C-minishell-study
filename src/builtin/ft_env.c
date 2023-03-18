/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:54 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/19 00:58:11 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_exit_status;

void	ft_env(t_info *cmd, t_envp *head) //exit status 성공시 0, 에러시 0 이상 ?
//126은 utility가 있지만 execute 못함, 127은 utility가 없는 경우. 근데 utility는 인자 .. 인듯 ?
{
	t_envp	*tmp;

	tmp = head;
	if (cmd->next != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd->next->cmd); // write로 고쳐야 하나요
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
