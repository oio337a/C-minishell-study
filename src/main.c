/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 18:39:17 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 프롬프트 열어서 하나의 완전한 커맨드를 readline으로 받아야됨

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_info	*env;

	env = env2(envp);
	while (env != NULL)
	{
		printf("%s\n", env->cmd);
		env = env->next;
	}
	exit(1);
	while (1)
	{
		str = readline("Nakishell$: ");
		if (!str)
		{
			//D
		}
		if (str != NULL)
		{
			if (*str != '\0' && is_whitespace(str))
			{
				add_history(str);
				/*작동*/
				// rl_on_new_line();
				
			}
			free(str);
		}
	}
	return (0);
}
