/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:05:00 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/20 17:21:28 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	err 유형
	1. < 하나만 들어왔을 때
	2. << word 2개 word 아니면 오류
	3. | 뒤에는 | 오면 안되고, NULL 이면 오류 < << 이면 오류 | 앞에도 word 필요
	4. > 뒤에는 word 1(trunc) , >> 뒤에 word 1(append)
	5. <<< 케이스도 < <<로 생각돼서 걸러지긴 할듯

------------------------------------------------------------------
	1. RDIR 뒤에 WORD가 아니면
	2. PIPE 뒤에 WORD가 아니면
	-> 풀어서 위에 적어놓음, 나중에 위에 것도 생각해서 구현해야할듯 버억 ㅅㅂ
	3. rdir은 뒤에만 word가 와야한다.

	before가 있으면 좋을거 같은 생각
*/

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
		if ((head->type == PIPE && ((head->next) == NULL)))
		{
			syntax_errno("|", STDOUT_FILENO);
			return (0);
		}
		else if (head->type == HEREDOC_IN || head->type == REDIR_IN) // 이거 리팩토링 했는데 heredoc 이랑 redir 테스트좀 부탁해여~! (소현, 수환님)
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
