/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:53:45 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/25 17:21:21 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	each_heredoc_cnt(t_info	**token)
{
	t_info	*head;
	int		cnt;

	head = *token;
	cnt = 0;
	while (head)
	{
		if (head->type == HEREDOC_IN)
			cnt++;
		if (head->type == PIPE)
			break ;
		head = head->next;
	}
	return (cnt);
}

int	*process_heredoc_cnt(t_info *token, int total_pipe)
{
	int	*cnt;
	int	i;

	i = 0;
	cnt = (int *)malloc(sizeof(int) * total_pipe);
	while (i < total_pipe)
	{
		cnt[i] = each_heredoc_cnt(&token);
		i++;
	}
	return (cnt);
}
