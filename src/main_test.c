/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/15 22:27:14 by yongmipa         ###   ########seoul.kr  */
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

void	execute(char *str, t_info *info, t_envp *envp_head)
{
	str_tokenize(info, str);
	if (validate_quote_all(info))
	{
		find_dollar(info, envp_head);
		clear_quote_in_token(info);
		pipex(info, envp_head);
	}
	else
		common_errno(info->cmd, 1, NULL);
	list_delete(&info);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_info	*info;
	t_envp	*envp_head;

	if (ac != 1 && av)
		return (0);
	// set_signal(GENERAL);
	envp_head = set_envp(envp);
	show_naki();
	while (1)
	{
		info = init_list();
		str = readline(PROMPT_COLOR "Nakishell$: " COMMAND_COLOR);
		if (!str)
			exit(0);
		if (*str == '\0')
			continue ;
		add_history(str);	
		execute(str, info, envp_head);
	}
	delete_envp_all(&envp_head);
	return (0);
}