/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:54 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/09 20:09:16 by suhwpark         ###   ########.fr       */
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

	if (!head)
		return (0); //이거맞나 ?
	tmp = head;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
