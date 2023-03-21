/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:05:00 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/21 15:25:25 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_quote_all(t_info *token)
{
	t_info	*head;

	head = token;
	while (head)
	{
		if (!check_quote_couple(head->cmd))
			return (0);
		head = head->next;
	}
	return (1);
}

void	syntax_errno(char *cmd, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd("syntax error near unexpected token '", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd("'\n", fd);
	g_last_exit_code = 258;
}

static int	error_case(t_info *head)
{
	if ((head->next) == NULL)
	{
		if (head->type == HEREDOC_IN)
			syntax_errno("<<", STDOUT_FILENO);
		else if (head->type == REDIR_IN)
			syntax_errno("<", STDOUT_FILENO);
		return (0);
	}
	else if ((head->next)->type != WORD)
	{
		syntax_errno(head->next->cmd, STDOUT_FILENO);
		return (0);
	}
	return (1);
}

int	check_syntax(t_info *token)
{
	t_info	*head;

	head = token;
	if (head->type == PIPE)
	{
		syntax_errno((head->cmd), STDOUT_FILENO);
		return (0);
	}
	while (head)
	{
		if (!ft_strcmp("||", head->cmd))
		{
			syntax_errno("|", STDOUT_FILENO);
			return (0);
		}
		else if ((head->type == PIPE && ((head->next) == NULL)))
		{
			syntax_errno("|", STDOUT_FILENO);
			return (0);
		}
		else if (head->type == PIPE && (head->next->type != WORD))
		{
			syntax_errno("|", STDOUT_FILENO);
			return (0);
		}
		else if (head->type == HEREDOC_IN || head->type == REDIR_IN)
			if (!error_case(head))
				return (0);
		head = head->next;
	}
	return (1);
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
