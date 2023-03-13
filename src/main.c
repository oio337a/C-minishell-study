/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 17:58:03 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	show_naki(void)
{
	int		fd;
	char	*line;

	fd = open("naki.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_putstr_fd(PROMPT_COLOR, STDIN_FILENO);
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
	close(fd);
}

int	main(int ac, char **av, char **envp)
{
	int g_last_exit_code = 0;
	char			*str;
	t_info			*info;
	t_info			*tmp;
	t_envp			*envp_head;
	char			*cmd_path;
	t_info			*after_deleteq;

	envp_head = set_envp(envp); // 환경변수 세팅
	info = NULL;
	show_naki();
	while (1)
	{
		info = init_list();
		str = readline(PROMPT_COLOR "Nakishell$: " COMMAND_COLOR);
		if (!str) //ctrl+D == NULL. bash 버전에 따라 동작 달라서 그냥 exit만 해도 됨
		{
			// printf("askdjfklsajdflkasjdf\n");
			exit(0);
		}
		if (*str != '\0')
		{
			add_history(str);
			str_tokenize(info, str); // info 스페이스바 기준으로 잘린 cmd들이 들어있습니다.
			if (validate_quote_line(info)) // validate임 ㅅㅂ럼아
			{
				find_dollar(info, envp_head);
				clear_qoute_in_token(info); // 쿼터 제거
			}
			else
			{
				common_errno(info->cmd, 1, NULL); // 나중에 고치는걸로 완벽 X
				continue ;
			}
			tmp = info;
			// after_deleteq = info;
			// token -> builtin 검수 후 그대로 실행한다. 
			// builtin의 요소가 아니라면 cmd의 path를 가져와 execve로 넣거나,에러처리
			pipex(info, envp_head);
		}
		list_delete(&info);
	}
	return (0);
}
