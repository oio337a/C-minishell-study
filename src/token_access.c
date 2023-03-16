/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:20 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/16 21:46:01 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

t_info	*get_token(t_info **token, int fd)
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
			(dup2(open_fd, STDIN_FILENO), close(open_fd)); // STDIN -> 자식 파이프 가리키기
			(*token) = (*token)->next;
			continue ;
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
			continue ;
		}
		if ((*token)->type == HEREDOC_IN) // cat << EOF 이러면 걍 파이프에 쓰인거 출력   //  << a
		{
			set_signal(CHILD);
			(*token) = (*token)->next;
			here_doc((*token)->cmd, fd); // 자식 프로세스 STDIN -> 내부 생성 ./heredoc 가리킴
			(*token) = (*token)->next;
			continue ;
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
			continue ;
		}
		if ((*token)->type == PIPE)
		{
			(*token) = (*token)->next;
			break ;
		}
		printf("before insert : %s\n", (*token)->cmd);
		insert_list(new, (*token)->cmd, (*token)->type);
		(*token) = (*token)->next;
	}
	// while (new)
	// {
	// 	printf("new : %s\n", new->cmd);
	// 	new = new->next;
	// }
	// exit(1);
	return (new);
}

static void	execve_token(t_info *token, t_envp *env, pid_t pid)
{
	char	**cmd;
	int		len;
	int		i;
	t_info	*head;

	printf("cmd : %s\n", token->cmd);
	len = list_size(token);
	head = token;
	i = 0;
	if (!builtin(token, env, pid))
	{
		cmd = (char **)malloc(sizeof(char *) * (len + 1));
		while (head)
		{
			cmd[i] = ft_strdup(head->cmd);
			i++;
			head = head->next;
		}
		cmd[i] = 0;
		if (execve(get_cmd(cmd[0], env), cmd, set_path(env)) == -1)
			exit(g_last_exit_code);
		ft_free(cmd);
	}
}
// 히어독 찾기
static	int	list_count_heredoc(t_info *token)
{
	t_info	*head;
	int		cnt;

	head = token;
	cnt = 0;
	while (head)
	{
		// printf("%d, %s\n", cnt, head->cmd);
		if (head->type == HEREDOC_IN)
			return (cnt);
		cnt++;
		head = head->next;
	}
	return (0);
}

static int	get_heredoc_pipe(t_info *token, int cnt)
{
	t_info	*head;
	int		pipe;

	pipe = 0;
	head = token;
	while (cnt--)
	{
		if (head->type == PIPE)
			pipe++;
		head = head->next;
	}
	return (pipe);
}

static void	move_heredoc(t_info **token, int pipe)
{
	while (pipe)
	{
		if ((*token)->type == PIPE)
			pipe--;
		(*token) = (*token)->next;
	}
}

void	pipex(t_info *token, t_envp *env) //heredoc 자식으로 넣을게여~~~~
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


	t_info	*test;
	test = token;
	while (test)
	{
		printf("all_token : %s\n", test->cmd);
		test = test->next;
	}
	i = 0;
	head = token;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	heredoc_pos = list_count_heredoc(head);
	heredoc_cnt = get_heredoc_pipe(head, heredoc_pos);
	if (heredoc_cnt > 0)
		move_heredoc(&head, heredoc_cnt);
	total_pipe = get_pipe_count(token) - heredoc_cnt + 1;
	//빌트인 해보자!
	if (total_pipe == 1 && is_builtin(head))
	{
		builtin(head, env, 12);
		return ;
	}
	while (i < total_pipe)
	{
		splited_token = get_token(&head, fd[2]); // ls -al | cat -e
		if (pipe(fd) == -1)
			common_errno("pipe error", 1, NULL);
		pid = fork();
		if (pid == 0)
		{
			set_signal(CHILD);
			if (i == total_pipe - 1)
				(dup2(STDOUT_FILENO, fd[1]), close(fd[1])); // STDIN ->heredoc, 파이프 출력->STDOUT
			else
				(dup2(fd[1], STDOUT_FILENO), close(fd[1])); // STDOUT -> 출력부 복사, 파이프 출력부 닫기.
			execve_token(splited_token, env, pid);
			list_delete(&splited_token);
		}
		else
		{
			set_signal(WAITING);
			dup2(fd[0], STDIN_FILENO);
			(close(fd[0]), close(fd[1]));
			waitpid(pid, &status, 0);
			g_last_exit_code = status >> 8;
			// printf("now g_last : %d\n", status >> 8);
		}
		i++;
	}
	set_signal(GENERAL);
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	// return (g_last_exit_code);
}
