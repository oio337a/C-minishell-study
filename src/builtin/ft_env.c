/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:54 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/06 16:58:28 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_env(t_envp *head)
{
	t_envp	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1); //0은 언제 리턴하지 ?
}
