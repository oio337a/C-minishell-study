/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 22:44:54 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*str;
	static t_info	*env;
	t_info			*info;
	t_info			*tmp;
	
	info=NULL;
	// env = ft_env(envp); // 환경변수 세팅 + 시그널 처리 한번에 하는거 어떰?
	info = init_list();
	while (1)
	{
		str = readline("Nakishell$: ");
		if (str != NULL)
		{
			if (*str != '\0')
			{
				add_history(str);
				pipe_parser(str, info);
				tmp = info;
				while (tmp != NULL)
				{
					printf("%s\n", tmp->cmd);
					tmp = tmp->next;
				}
				/*작동*/
				//parse_command()
			}
			free(str);
		}
	}
	return (0);
}
