/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/06 19:41:35 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_info			*info;
	t_info			*tmp;
	t_envp			*envp_head;

	envp_head = set_envp(envp); // 환경변수 세팅
	info = NULL;
	// 시그널 처리도 위에서 !
	while (1)
	{
		info = init_list();
		str = readline("Nakishell$: ");
		if (!str) //ctrl+D == NULL
		{
			printf("\033[1A\033[7Cexit");
			exit(0);
		}
		else
		{
			if (*str != '\0')
			{
				// add_history(str);
				// v_str = validate_readline(str); // valid한 라인으로 나와 -> pipe 기준 잘라 -> cmd_path에 넣어
				// pipe_parser(str, info);
				str_tokenize(info, str);
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
