#include "../includes/minishell.h"

/*
파이프 전까지 리스트 새로 담아
두개씩 join해 -> 실행, 만약 builtin이 있으면 그거 처리 먼저해

< a ls -al | cat -e | wc -l

< a ls -al

<
a
ls
-al
 -> process 실행
*/

char	**envp_arr(t_envp *envp)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (size_envp(envp)) + 1);
	while (envp)
	{
		tmp = ft_strjoin(envp->key, "=");
		res[i] = ft_strjoin_free(tmp, envp->value);
		i++;
		envp = envp->next;
	}
	res[i] = 0;
	return (res);
}

int	get_pipe_count(t_info *token)
{
	t_info	*head;
	int		cnt;

	head = token;
	cnt = 0;
	while (head)
	{
		if (head->type == PIPE)
			cnt++;
		head = head->next;
	}
	return (cnt);
}
// 파이프 전까지 새로운 리스트에 담는다
t_info	*make_new_list(t_info **token)
{
	t_info	*new;

	new = init_list();
	while (*token)
	{
		if ((*token)->type == PIPE)
		{
			*token = (*token)->next;
			break ;
		}	
		insert_list(new, (*token)->cmd, (*token)->type);
		printf("cmd %s\n", (*token)->cmd);
		*token = (*token)->next;
	}
	return (new);
}

//cmd에 대한 이차원 배열 만들기 ls , -al -> ls / -al / NULL 
char	**execve_path(t_info *token)
{
	char	**res;
	int		cnt;
	int		i;

	i = 0;
	cnt = list_size(token);
	res = (char **)malloc(sizeof(char *) * cnt + 1);
	while (token && i < cnt)
	{
		res[i] = token->cmd;
		token = token->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	redir_case(t_info *token)
{
	int	new_fd;

	if (token->type == REDIR_IN)
	{
		token = token->next;
		new_fd = open(token->cmd, O_RDONLY);
		if (new_fd == -1)
			common_errno(token->cmd, 2, NULL);
		dup2(new_fd, STDIN_FILENO);
		close(new_fd);
	}
	else if (token->type == REDIR_OUT)
	{
		token = token->next;
		new_fd = open(token->cmd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (new_fd == -1)
			common_errno(token->cmd, 1, NULL);
		dup2(new_fd, STDOUT_FILENO);
		close(new_fd);
	}
}

void	first_process(t_info *token, t_envp *env, int fd[])
{
	printf("It's first\n");
	char	**cmd_line;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	while (token)
	{
		redir_case(token);
		cmd_line = execve_path(token);
		printf("path : %s\n", get_cmd(cmd_line[0], env));
		execve(get_cmd(cmd_line[0], env), cmd_line, envp_arr(env));
		token = token->next;
	}
}

void	last_process(t_info *token, t_envp *env, int fd[])
{
	printf("It's last\n");
	char	**cmd_line;

	while (token)
	{
		redir_case(token);
		cmd_line = execve_path(token);
		execve(get_cmd(cmd_line[0], env), cmd_line, envp_arr(env));
		token = token->next;
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	mid_process(t_info *token, t_envp *env, int fd[])
{
	printf("dont'here\n");
	char	**cmd_line;

	while (token)
	{
		redir_case(token);
		cmd_line = execve_path(token);
		execve(get_cmd(cmd_line[0], env), cmd_line, envp_arr(env));
		token = token->next;
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	access_token(t_info *token, t_envp *env)
{
	int		pipe_cnt;
	pid_t	pid;
	int		fd[2];
	int		i;
	t_info	*new_token;

	i = -1;
	pipe_cnt = get_pipe_count(token);
	while (++i < pipe_cnt + 1)
	{
		new_token = make_new_list(&token);
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_process(new_token, env, fd);
			if (i == pipe_cnt)
				last_process(new_token, env, fd);
			mid_process(new_token, env, fd);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		list_delete(&new_token);
	}
	while (wait(NULL) == -1)
		return ;
}
