/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:40 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/24 18:07:36 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	after_here_doc(int fd, int origin_fd)
// {
// 	if (fd == -1)
// 	{
// 		unlink(".here_doc");
// 		common_errno("fd", 2);
// 	}
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	unlink(".here_doc");
// }

void	here_doc(char *limiter, t_envp *envp, char *filename)
{
	int		fd;
	char	*line;
	char	*ret;

	limiter = ft_strjoin_free(limiter, "\n");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		common_errno("fd", 2);
	while (1)
	{
		write(1, "\033[38:5:141m" "Nadocki 🐶 ⍩ " COMMAND_COLOR, 33);
		line = get_next_line(STDIN_FILENO);
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ret = parse_dollar(line, envp);
		write(fd, ret, ft_strlen(ret));
		free(line);
		free(ret);
	}
	// fd = open(".here_doc", O_RDONLY);
	// after_here_doc(fd, origin_fd);
}
