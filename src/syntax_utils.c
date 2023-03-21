/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:10:45 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 20:13:11 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	vaildate_type(t_info *head)
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
	return (1);
}
