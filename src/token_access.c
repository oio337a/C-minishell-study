/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 22:51:40 by yongmipa         ###   ########seoul.kr  */
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
			continue ;
		}
		if ((*token)->type == REDIR_OUT)
		{
			*flag = 1;
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
			*flag = 1;
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
		// if ((*token)->type == WORD)
		(*token) = (*token)->next;
	}
	return (new);
}

// t_pipe	*get_pipe_info(t_info *token)
// {
// 	t_pipe	*var;

// 	var = (t_pipe *)ft_safe_malloc(sizeof(t_pipe));
// 	var->fd[2] = dup(STDIN_FILENO);
// 	var->fd[3] = dup(STDOUT_FILENO);
// 	var->heredoc_pos = list_count_heredoc(token);
// 	var->heredoc_cnt = get_heredoc_pipe(token, var->heredoc_pos);
// 	if (var->heredoc_cnt > 0)
// 		move_heredoc(&token, var->heredoc_cnt);
// 	var->total_pipe = get_pipe_count(token) - (var->heredoc_cnt) + 1;
// 	var->flag = 0;
// 	var->status = 0;
// 	return (var);
// }

// static void	child_process(t_info *head, t_envp *env, t_pipe *var, int i)
// {
// 	t_info	*splited_token;

// 	splited_token = get_token(&head, env, var->fd[2], &var->flag);
// 	if (i == var->total_pipe - 1)
// 		(dup2(STDOUT_FILENO, var->fd[1]), close(var->fd[1]));
// 	else
// 		if (!var->flag)
// 			(dup2(var->fd[1], STDOUT_FILENO), close(var->fd[1]));
// 	execve_token(splited_token, env, var->pid);
// 	list_delete(&splited_token);

// }

// static int	parent_process(t_pipe *var)
// {
// 	set_signal(WAITING);
// 	dup2(var->fd[0], STDIN_FILENO);
// 	(close(var->fd[0]), close(var->fd[1]));
// 	waitpid(var->pid, &var->status, 0);
// 	if (var->status == 2)
// 	{
// 		if (!var->heredoc_pos)
// 			g_last_exit_code = 130;
// 		else
// 			g_last_exit_code = 1;
// 		return (0);
// 	}
// 	else if (var->status == 3)
// 	{
// 		if (!var->heredoc_pos)
// 			write(1, "Quit : 3\n", 9);
// 		g_last_exit_code = 131;
// 		return (0);
// 	}
// 	else
// 		g_last_exit_code = var->status >> 8;
// 	return (1);
// }

// void	access_builtin(t_info *head, t_envp *env, t_pipe *var)
// {
// 	t_info	*splited_var;

// 	splited_var = get_token(&head, env, var->fd[2], &(var->flag));
// 	builtin(splited_var, env, 42);
// 	dup2(var->fd[2], STDIN_FILENO);
// 	dup2(var->fd[3], STDOUT_FILENO);
// 	free(splited_var);
// }

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
	// t_pipe	*var;
	int		status;
	int		flag;

	i = 0;
	flag = 0;
	head = token;
	// status = 0;
	// var = get_pipe_info(head);
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	heredoc_pos = list_count_heredoc(head);
	heredoc_cnt = get_heredoc_pipe(head, heredoc_pos);
	if (heredoc_cnt > 0)
		move_heredoc(&head, heredoc_cnt);
	total_pipe = get_pipe_count(token) - heredoc_cnt + 1;
	if (total_pipe == 1 && is_builtin(head))
	{
		splited_token = get_token(&head, env, fd[2], &flag);
		builtin(splited_token, env, 42);
		dup2(fd[2], STDIN_FILENO);
		dup2(fd[3], STDOUT_FILENO);
		free(splited_token);
		// access_builtin(head, env, var);
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
			execve_token(splited_token, env, pid);
			list_delete(&splited_token);
			// child_process(head, env, var, i);
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
			// if (!parent_process(var))
			// 	break ;
		}
		i++;
	}
	set_signal(GENERAL);
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
}
