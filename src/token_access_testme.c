/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access_testme.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 15:44:53 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

t_info	*get_token(t_info **token, t_envp *envp, int fd, int *flag)
{
	t_info	*new;

	new = init_list();
	while (*token)
	{
		if ((*token)->type == REDIR_IN)
		{
			type_redir_in(token, fd);
			// continue ;
		}
		if ((*token)->type == REDIR_OUT)
		{
			*flag = 1;
			type_redir_out(token, fd);
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
			// continue ;
		}
		if ((*token)->type == HEREDOC_IN)
		{
			type_heredoc_in(token, fd, envp);
			// continue ;
		}
		if ((*token)->type == HEREDOC_OUT)
		{
			*flag = 1;
			type_heredoc_out(token, fd);
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
			// continue ;
		}
		if ((*token)->type == PIPE)
		{
			(*token) = (*token)->next;
			break ;
		}
		insert_list(new, (*token)->cmd, (*token)->type);
		if ((*token)->type == WORD)
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
	int		flag;

	i = 0;
	flag = 0;
	head = token;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	heredoc_pos = list_count_heredoc(head);
	printf("herdor in? %d\n", heredoc_pos);
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
			splited_token = get_token(&head, env, fd[2], &flag);
			if (i == total_pipe - 1)
				(dup2(STDOUT_FILENO, fd[1]), close(fd[1]));
			else
				if (!flag)
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
			{
				if (!heredoc_pos)
					g_last_exit_code = 130;
				else
					g_last_exit_code = 1;
				break ;
			}
			else if (status == 3)
			{
				if (!heredoc_pos)
					write(1, "Quit : 3\n", 9);
				g_last_exit_code = 131;
				break ;
			}
			else
				g_last_exit_code = status >> 8;
		}
		i++;
	}
	set_signal(GENERAL);
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
}
