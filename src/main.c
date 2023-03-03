/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 19:44:27 by yongmipa         ###   ########seoul.kr  */
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
				validate_readline(str);
				//"ls" -al | cat -e "|" "wc -al" -> double : 6, ls -al | cat -e | wc$-al
				// ls -al / cat -e / wc$-al -> split 공백기준, path_cmd 실행 +)<, >> , $ , 예외처리 어케하죠?
				// 근데 위에 경우 에러인데요.뿡
				// 이것도 에러에요
				// "ls" -al | cat -e "|" "wc" -al
				v_str = validate_readline(str)
				// pipe_parser(str, info);
				tmp = info;
				while (tmp != NULL)
				$
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
