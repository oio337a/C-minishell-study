/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/25 18:07:56 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_heredoc(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		unlink(p[i]);
		i++;
	}
	free(p);
}

static void	child_process(t_info *head, t_envp *env, t_pipe *var, int i)
{
	t_info	*splited_token;

	// set_signal(CHILD);
	if (head->type == PIPE)
		head = head->next;
	splited_token = get_token(&head, env, var, i);
	if (i == var->total_pipe - 1)
		(dup2(STDOUT_FILENO, var->fd[1]), close(var->fd[1]));
	if (!var->flag)
	{
		close(var->fd[0]);
		(dup2(var->fd[1], STDOUT_FILENO), close(var->fd[1]));
	}
	execve_token(splited_token, env, var->pid);
	list_delete(&splited_token);
}

static int	parent_process(t_pipe *var, pid_t pid)
{
	// set_signal(WAITING);
	dup2(var->fd[0], STDIN_FILENO);
	(close(var->fd[0]), close(var->fd[1]));
	return (1);
}

static void	let_go(t_info *head, t_pipe *var, t_envp *env)
{
	int	i;

	i = 0;
	while (i < var->total_pipe)
	{
		if (i > 0)
			move_list(&head);
		if (pipe(var->fd) == -1)
			syntax_errno("|");
		var->pid = fork();
		if (var->pid == 0)
			child_process(head, env, var, i);
		else
			if (!parent_process(var, var->pid))
				break ;
		i++;
	}
	while (wait(&var->status) != -1)
		;
	if (var->status == 2)
	{
		if (!var->heredoc_pos)
			g_last_exit_code = 130;
		else
			g_last_exit_code = 1;
	}
	else if (var->status == 3)
	{
		if (!var->heredoc_pos)
			write(1, "Quit : 3\n", 9);
		g_last_exit_code = 131;
	}
	else
		g_last_exit_code = var->status >> 8;
	// set_signal(GENERAL);
}

void	pipex(t_info *token, t_envp *env)
{
	t_info	*head;
	t_pipe	*var;

	head = token;
	var = get_pipe_info(head);
	if (list_count_heredoc(head))
		get_heredoc_file(head, env, var);
	if (var->total_pipe == 1 && is_builtin(head))
	{
		access_builtin(head, env, var);
		free(var);
		return ;
	}
	let_go(head, var, env);
	ft_free_heredoc(var->filename);
	free(var->doc_cnt);
	free(var);
	dup2(var->stdin_back, STDIN_FILENO);
	dup2(var->stdout_back, STDOUT_FILENO);
}
