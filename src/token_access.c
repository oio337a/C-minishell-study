/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/14 15:39:49 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

t_info	*get_token(t_info **token)
{
	t_info	*new;
	int		open_fd;

	new = init_list();
	while (*token)
	{
		if ((*token)->type == REDIR_IN)
		{
			(*token) = (*token)->next;
			open_fd = open((*token)->cmd, O_RDONLY);
			if (open_fd == -1)
				common_errno((*token)->cmd, 2, NULL);
			(dup2(open_fd, STDIN_FILENO), close(open_fd));
			(*token) = (*token)->next;
		}
		if ((*token)->type == REDIR_OUT)
		{
			(*token) = (*token)->next;
			open_fd = open((*token)->cmd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (open_fd == -1)
				common_errno((*token)->cmd, 2, NULL);
			(dup2(open_fd, STDOUT_FILENO), close(open_fd));
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
		}
		if ((*token)->type == HEREDOC_IN)
		{
			// set_signal(HEREDOC);
			(*token) = (*token)->next;
			here_doc((*token)->cmd);
			(*token) = (*token)->next;
		}
		if ((*token)->type == HEREDOC_OUT)
		{
			(*token) = (*token)->next;
			open_fd = open((*token)->cmd, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (open_fd == -1)
				common_errno((*token)->cmd, 2, NULL);
			(dup2(open_fd, STDOUT_FILENO), close(open_fd));
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
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

static void	execve_token(t_info *token, t_envp *env)
{
	char	**cmd;
	int		len;
	int		i;
	t_info	*head;

	len = list_size(token);
	cmd = (char **)malloc(sizeof(char *) * (len + 1));
	head = token;
	i = 0;

	/*
	if (빌트인이 아니면 밑에 실행)
	*/
	while (head)
	{
		cmd[i] = ft_strdup(head->cmd);
		// printf("%s\n", cmd[i]);
		i++;
		head = head->next;
	}
	cmd[i] = 0;
	if (execve(get_cmd(cmd[0], env), cmd, set_path(env)) == -1)
		g_last_exit_code = -1;
	ft_free(cmd);
}

void	pipex(t_info *token, t_envp *env)
{
	pid_t	pid;
	int		i;
	int		fd[4];
	t_info	*splited_token;
	t_info	*head;

	i = 0;
	head = token;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	g_last_exit_code = 0;
	while (i < get_pipe_count(token) + 1)
	{
		splited_token = get_token(&head);
		if (pipe(fd) == -1)
			common_errno("pipe error", 1, NULL);
		pid = fork();
		if (pid == 0)
		{
			// set_signal(CHILD);
			if (i == get_pipe_count(token))
				(dup2(STDOUT_FILENO, fd[1]), close(fd[1]));
			else
				(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
			execve_token(splited_token, env);
			list_delete(&splited_token);
		}
		else
		{
			// set_signal(WAITING);
			waitpid(pid, NULL, 0);
			dup2(fd[0], STDIN_FILENO);
			(close(fd[0]), close(fd[1]));
		}
		i++;
	}
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	// return (g_last_exit_code);
}