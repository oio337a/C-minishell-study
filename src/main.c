/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 20:07:17 by yongmipa         ###   ########seoul.kr  */
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
	
	while (1)
	{
		info = init_list();
		str = readline("Nakishell$: ");
		if (!str)
		{
			printf("\033[1A\033[7Cexit");
			exit(0);
		}
		else
		{
			if (*str != '\0')
			{
				add_history(str);
				v_str = validate_readline(str); // valid한 라인으로 나와 -> pipe 기준 잘라 -> cmd_path에 넣어
				// pipe_parser(str, info);
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
		list_delete(&info);
	}
	return (0);
}
