/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/18 17:36:51 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code = 0;

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
		ft_putstr_fd(WELCOME_COLOR, STDIN_FILENO);
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
	write(1, "\n\n", 2);
	close(fd);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_info	*info;
	t_envp	*envp_head;
	// t_info	*head;
	// int		fd[2];

	// fd[0] = dup(STDIN_FILENO);
	// fd[1] = dup(STDOUT_FILENO);
	if (ac != 1 && av)
		return (0);
	set_signal(GENERAL);
	envp_head = set_envp(envp);
	show_naki();
	while (1)
	{
		info = init_list();
		str = readline(PROMPT_COLOR "Nakishell$: " COMMAND_COLOR);
		if (!str)
			exit(0);
		if (*str != '\0')
		{
			add_history(str);
			str_tokenize(info, str);
			if (validate_quote_all(info))
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
			// dup2(fd[0], STDIN_FILENO);
			// dup2(fd[1], STDOUT_FILENO);
		}
		list_delete(&info);
	}
	delete_envp_all(&envp_head);
	return (0);
}
