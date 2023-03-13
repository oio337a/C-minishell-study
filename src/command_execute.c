/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:51 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 14:32:52 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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
 -> first_process
*/

char	**envp_arr(t_envp *envp)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (list_size(envp)) + 1);
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
	while (head)
	{
		if (head->type == PIPE)
			cnt++;
		head = head->next;
	}
	return (cnt);
}
// 파이프 전까지 새로운 리스트에 담는다
t_info	*make_new_list(t_info *token)
{
	t_info	*new;

	new = init_list();
	while (token)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			break ;
		}	
		insert_list(new, token->cmd, token->type);
		token = token->next;
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
	// cnt = list_size(token);
	cnt = cmd_size(token);
	res = (char **)malloc(sizeof(char *) * cnt + 1);  // dd나 해봐도 됌?
	while (token && i < cnt)
	{
		res[i] = token->cmd;
		token = token->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	firsrt_process(t_info *token, t_envp *env, int fd[])
{
	t_info	*new;
	char	**cmd_line;
	char	*path;
	int		new_fd;

	new = make_new_list(token); // 얘 리스트 자체를 한바퀴 돌아야될거같음 중간에 RDIR나와도 실행이라 // 이거일줄은 몰랐네
	while (new) // token 자체를 밀어주면 안될거같은 생각이 듬 왜냐면 main 끝나면 list delete 하는데 거기서 터질거같음
	{
		if (new->type == REDIR_IN)
		{
			new = new->next;
			new_fd = open(new->cmd, O_RDONLY);
			if (new_fd == -1)
				common_errno(new->cmd, 2, NULL);
			dup2(new_fd, STDIN_FILENO);
			close(new_fd);
			new = new->next;
		}
		else
		{
			cmd_line = execve_path(new);
			path = get_cmd(cmd_line[0], env);
			execve(path, cmd_line, envp_arr(env));
			free(path);
			ft_free(cmd_line);
		}
		// new = new->next;
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	last_process(t_info *token, t_envp *env, int fd[])
{

}

void	access_token(t_info *token, t_envp *env)
{
	int		pipe_cnt;
	pid_t	pid;
	int		fd[2];
	int		i;

	i = -1;
	pipe_cnt = get_pipe_count(token);
	while (++i < pipe_cnt)
	{
		if (pipe(fd) == -1)
			exit(1); // 나중에 고치자
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_process(token, env, fd);
			if (i == pipe_cnt - 1)
				last_process(token, env, fd);
			mid_process(token, env, fd);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
	}
	while (wait(NULL) == -1)
		return ;
}
