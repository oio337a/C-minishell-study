/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:05:00 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/18 21:31:36 by sohyupar         ###   ########.fr       */
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
		else if (head->type == HEREDOC_IN)
		{
			if ((head->next) == NULL)
			{
				syntax_errno("<<", STDOUT_FILENO);
				return (0);
			}
			else if ((head->next)->type != WORD)
			{
				syntax_errno(head->next->cmd, STDOUT_FILENO);
				return (0);
			}
		}
		else if (head->type == REDIR_IN)
		{
			if ((head->next) == NULL)
			{
				syntax_errno("<", STDOUT_FILENO);
				return (0);
			}
			else if ((head->next)->type != WORD)
			{
				syntax_errno(head->next->cmd, STDOUT_FILENO);
				return (0);
			}
		}
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
