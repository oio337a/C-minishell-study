/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 18:20:46 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_info	*get_token(t_info **token)
{
	t_info	*new;

	new = init_list();
	while (*token)
	{
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
		i++;
		head = head->next;
	}
	cmd[i] = 0;
	execve(get_cmd(cmd[0], env), cmd, set_path(env));
	ft_free(cmd);
}

void	pipex(t_info *token, t_envp *env)
{
	pid_t	pid;
	int		i;
	int		fd[2];
	int		origin_fd;
	t_info	*splited_token;
	t_info	*head;
	int		status;
	
	i = 0;
	head = token;
	origin_fd = dup(STDIN_FILENO);
	while (i < get_pipe_count(token) + 1) // pipe count 빼면서 하는건 어떰 좋지
	{
		splited_token = get_token(&head);
		if (pipe(fd) == -1)
			common_errno("pipe error", 1, NULL);
		pid = fork();
		if (pid == 0)
		{
			if (i == get_pipe_count(token))
				(dup2(STDOUT_FILENO, fd[1]), close(fd[1]));
			else
				(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
			execve_token(splited_token, env);
			list_delete(&splited_token);
		}
		else
		{
			waitpid(pid, NULL, 0);
			dup2(fd[0], STDIN_FILENO);
		}
		i++;
	}
	dup2(origin_fd, STDIN_FILENO);
	// dup2(fd[0], STDIN_FILENO);
	// while(wait(&status) == -1)
	// 	return ;
	// while (wait(&status) > 0);
	// while (waitpid(pid, &status, 0) > 0)
	// 	;
}