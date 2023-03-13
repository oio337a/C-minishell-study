#include "../includes/minishell.h"

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

t_info	*get_token(t_info *token)
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
}

void	pipex(t_info *token, t_envp *env)
{
	pid_t	pid;
	int		i;
	int		fd[2];
	int		pipe_cnt;
	t_info	*splited_token;

	i = 0;
	pipe_cnt = get_pipe_count(token) + 1;
	while (i < pipe_cnt)
	{
		splited_token = get_token();
		if (pipe(fd) == -1)
			common_errno("pipe error", 1, NULL);
		pid = fork();
		
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}