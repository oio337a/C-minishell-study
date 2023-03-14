/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/14 20:24:26 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

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
	char	*str;
	t_info	*info;
	t_info	*tmp;
	t_envp	*envp_head;

	if (ac != 1 && av)
		return (0);
	envp_head = set_envp(envp);
	// info = NULL;
	show_naki();
	while (1)
	{
		info = init_list();
		str = readline(PROMPT_COLOR "Nakishell$: " COMMAND_COLOR);
		if (!str)
		{
			g_last_exit_code = 0;
			exit(0);
		}
		if (*str != '\0')
		{
			add_history(str);
			str_tokenize(info, str);
			tmp = info;
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
			pipex(info, envp_head);
		}
		list_delete(&info);
	}
	delete_envp_all(&envp_head);
	return (0);
}
