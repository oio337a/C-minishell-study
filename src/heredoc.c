/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:40 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 22:25:47 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		common_errno("fd", 2 ,NULL);
	while (1)
	{
		write(1, "here doc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	fd = open(".here_doc", O_RDONLY);
	if (fd == -1)
	{
		unlink(".here_doc");
		common_errno("fd", 2 ,NULL);
	}
	unlink(".here_doc");
	dup2(fd, STDIN_FILENO);
}
