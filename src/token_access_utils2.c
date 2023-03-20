/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:40:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 20:57:27 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	type_redir_in(t_info **token, int fd)
{
	int	open_fd;

	(*token) = (*token)->next;
	open_fd = open((*token)->cmd, O_RDONLY);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2, NULL, fd);
		exit(127);
	}
	(dup2(open_fd, STDIN_FILENO), close(open_fd));
	(*token) = (*token)->next;
}

void	type_redir_out(t_info **token, int fd)
{
	int	open_fd;

	(*token) = (*token)->next;
	open_fd = open((*token)->cmd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2, NULL, fd);
		exit(1);
	}
	(dup2(open_fd, STDOUT_FILENO), close(open_fd));
}

void	type_heredoc_in(t_info **token, int fd, t_envp *envp)
{
	set_signal(HEREDOC);
	(*token) = (*token)->next;
	here_doc((*token)->cmd, envp, fd);
	(*token) = (*token)->next;	
}


void	type_heredoc_out(t_info **token, int fd)
{
	int	open_fd;

	(*token) = (*token)->next;
	open_fd = open((*token)->cmd, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2, NULL, fd);
		exit(1);
	}
	(dup2(open_fd, STDOUT_FILENO), close(open_fd));
}