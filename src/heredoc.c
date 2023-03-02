/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:40 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 22:03:41 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_heredoc(char *str)
{
	if (!ft_strncmp(str, "here_doc", ft_strlen2("here_doc")))
		return (1);
	return (0);
}

static void	unlink_heredoc(char *str)
{
	unlink(str);
	print_exit("cant't open tmp heredoc");
}

void	here_doc(t_arg *arg)
{
	int		heredoc_fd;
	char	*line;

	arg->limiter = ft_strjoin(arg->av[2], "\n");
	heredoc_fd = open("/tmp/.here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		print_exit("can't make tmp file for heredoc");
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || !ft_strncmp(arg->limiter, line, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, heredoc_fd);
		free(line);
	}
	heredoc_fd = open("/tmp/.here_doc", O_RDONLY);
	if (heredoc_fd == -1)
		unlink_heredoc("/tmp/.here_doc");
	dup2(heredoc_fd, STDIN_FILENO);
}