#include "../includes/minishell.h"

int	g_last_exit_code;

void	type_in(t_info **token)
{
	int	open_fd;

	if ((*token)->type == REDIR_IN)
	{
		(*token) = (*token)->next;
		open_fd = open((*token)->cmd, O_RDONLY);
		if (open_fd == -1)
			common_errno((*token)->cmd, 2, NULL);
		(dup2(open_fd, STDIN_FILENO), close(open_fd));
		(*token) = (*token)->next;
		printf("when < cmd : %s\n", (*token)->cmd);
	}
	else if ((*token)->type == HEREDOC_IN)
	{		
		// set_signal(HEREDOC);
		(*token) = (*token)->next;
		here_doc((*token)->cmd);
		(*token) = (*token)->next;
		printf("when << cmd : %s\n", (*token)->cmd);
	}
}

void	type_out(t_info **token)
{
	int	open_fd;

	if ((*token)->type == REDIR_OUT)
	{
		(*token) = (*token)->next;
		open_fd = open((*token)->cmd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (open_fd == -1)
			common_errno((*token)->cmd, 2, NULL);
		(dup2(open_fd, STDOUT_FILENO), close(open_fd));
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		printf("when > cmd : %s\n", (*token)->cmd);
	}
	else if ((*token)->type == HEREDOC_OUT)
	{
		(*token) = (*token)->next;
		open_fd = open((*token)->cmd, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (open_fd == -1)
			common_errno((*token)->cmd, 2, NULL);
		(dup2(open_fd, STDOUT_FILENO), close(open_fd));
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		printf("when >> cmd : %s\n", (*token)->cmd);
	}
}