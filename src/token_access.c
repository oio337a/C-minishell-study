/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 20:51:50 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

t_info	*get_token(t_info **token, t_envp *envp, int fd)
{
	t_info	*new;

	new = init_list();
	while (*token)
	{
		if ((*token)->type == REDIR_IN)
		{
			type_redir_in(token, fd);
			continue ;
		}
		if ((*token)->type == REDIR_OUT)
		{
			type_redir_out(token, fd);
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
			continue ;
		}
		if ((*token)->type == HEREDOC_IN)
		{
			type_heredoc_in(token, fd, envp);
			continue ;
		}
		if ((*token)->type == HEREDOC_OUT)
		{
			type_heredoc_out(token, fd);
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
			continue ;
		}
		if ((*token)->type == PIPE)
		{
			(*token) = (*token)->next;
			break ;
		}
		insert_list(new, (*token)->cmd, (*token)->type);
		(*token) = (*token)->next;
	}
	return (new);
}

void	pipex(t_info *token, t_envp *env)
{
	pid_t	pid;
	int		i;
	int		fd[4];
	t_info	*splited_token;
	t_info	*head;
	int		total_pipe;
	int		heredoc_pos;
	int		heredoc_cnt;
	int		status;

	i = 0;
	head = token;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	heredoc_pos = list_count_heredoc(head);
	heredoc_cnt = get_heredoc_pipe(head, heredoc_pos);
	if (heredoc_cnt > 0)
		move_heredoc(&head, heredoc_cnt);
	total_pipe = get_pipe_count(token) - heredoc_cnt + 1;
	if (total_pipe == 1 && is_builtin(head))
	{
		builtin(head, env, 42);
		return ;
	}
	while (i < total_pipe)
	{
		if (i > 0)
			move_list(&head);
		if (pipe(fd) == -1)
			syntax_errno("|", fd[3]);
		pid = fork();
		if (pid == 0)
		{
			set_signal(CHILD);
			splited_token = get_token(&head, env, fd[2]);
			if (i == total_pipe - 1)
				(dup2(STDOUT_FILENO, fd[1]), close(fd[1]));
			else
				if (!heredoc_pos)
					(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
			execve_token(splited_token, env, pid, fd[2]);
			list_delete(&splited_token);
		}
		else
		{
			set_signal(WAITING);
			dup2(fd[0], STDIN_FILENO);
			(close(fd[0]), close(fd[1]));
			waitpid(pid, &status, 0);
			if (status == 2)
				g_last_exit_code = 130;
			else if (status == 3)
				g_last_exit_code = 131;
			else
				g_last_exit_code = status >> 8;
		}
		i++;
	}
	set_signal(GENERAL);
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
}
