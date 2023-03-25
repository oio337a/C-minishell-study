/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:40:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/24 19:24:52 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	type_redir_in(t_info **token)
{
	int	open_fd;

	(*token) = (*token)->next;
	open_fd = open((*token)->cmd, O_RDONLY);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2);
		exit(1);
	}
	(dup2(open_fd, STDIN_FILENO), close(open_fd));
	(*token) = (*token)->next;
	return (0);
}

int	type_redir_out(t_info **token)
{
	int	open_fd;

	(*token) = (*token)->next;
	open_fd = open((*token)->cmd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2);
		exit(1);
	}
	(dup2(open_fd, STDOUT_FILENO), close(open_fd));
	return (1);
}

int	type_heredoc_in(t_info **token, t_pipe *var, t_envp *envp, int i)
{
	int	open_fd;
    
	(*token) = (*token)->next;
	/*
		cat << a << b << c | 
		cat << a << a << b |
		cat << a << a << v |
		파이프 갯수 만큼 동적할당 
		int a = (int *)malloc(sizeof())
	*/
	open_fd = open(var->filename[i], O_RDONLY);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2);
		exit(1);
	}
	(dup2(open_fd, STDIN_FILENO), close(open_fd));
	(*token) = (*token)->next;
	return (0);
}

int	type_heredoc_out(t_info **token)
{
	int	open_fd;

	(*token) = (*token)->next;
	open_fd = open((*token)->cmd, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (open_fd == -1)
	{
		common_errno((*token)->cmd, 2);
		exit(1);
	}
	(dup2(open_fd, STDOUT_FILENO), close(open_fd));
	return (1);
}
