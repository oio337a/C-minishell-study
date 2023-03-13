/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:54 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 17:55:28 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status;

/*
t_info	*ft_env(char **envp)
{
	t_info	*env;
	int		i;

	init_list(env);
	i = 0;
	while (envp[i])
		insert_list(env, envp[i++]);
	return (env);
}
*/

void	ft_env(t_envp *head) //exit status 성공시 0, 에러시 0 이상 ?
//126은 utility가 있지만 execute 못함, 127은 utility가 없는 경우. 근데 utility는 인자 .. 인듯 ?
{
	t_envp	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_exit_status = 0;
}
