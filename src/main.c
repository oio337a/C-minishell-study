/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/14 13:33:01 by naki             ###   ########.fr       */
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
	write(1, "\n", 1);
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

	// set_signal(GENERAL);
	envp_head = set_envp(envp); // 환경변수 세팅
	info = NULL;
	show_naki();
	while (1)
	{
		info = init_list();
		str = readline(PROMPT_COLOR "Nakishell$: " COMMAND_COLOR);
		if (!str) //ctrl+D == NULL. bash 버전에 따라 동작 달라서 그냥 exit만 해도 됨
			exit(0);
		if (*str != '\0')
		{
			add_history(str);
			str_tokenize(info, str);
			// t_info *a;
			// a = info;
			// while(a)
			// {
			// 	printf("%s\n", a->cmd);
			// 	a = a->next;
			// }
			if (validate_quote_line(info))
			{
				find_dollar(info, envp_head);
				clear_quote_in_token(info);
			}
			else
			{
				common_errno(info->cmd, 1, NULL);
				continue ;
			}
			tmp = info;
			pipex(info, envp_head);
		}
		list_delete(&info);
	}
	delete_envp_all(&envp_head);
	return (0);
}
