/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:40 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/15 20:32:08 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(char *limiter)
{
	int		fd;
	char	*line;
	char	*limiter_tmp;
	
	limiter_tmp = ft_strjoin(limiter, "\n");
	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		common_errno("fd", 2, NULL);
	while (1)
	{
		write(1, "\033[38:5:141m" "Nadocki 🐶 ⍩ " COMMAND_COLOR, 33);
		line = get_next_line(STDIN_FILENO);
		if (!line || !ft_strncmp(line, limiter_tmp, ft_strlen(limiter_tmp)))
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
	free(limiter_tmp);
	dup2(fd, STDIN_FILENO);
	unlink(".here_doc");
}
