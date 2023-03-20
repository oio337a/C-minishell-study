/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:00:43 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/20 20:32:18 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_single_quote(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

static int	check_else(char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$')
			return (1);
		if (token[i] == '\"')
		{
			j = i + 1;
			while (token[j] && token[j] != '\"')
			{
				if (token[j] == '$')
					return (1);
				j++;
			}
			i = j - 1;
		}
		i++;
	}
	return (0);
}

static int	check_envp(char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!is_single_quote(token))
		return (0);
	if (check_else(token) == 1)
		return (1);
	return (0);
}

int	check_quote_couple(char *token)
{
	int	i;
	int	next;

	i = 0;
	next = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			next = find_next_quote(token, '\'', i);
			if (next == -1)
				return (0);
			i = next;
		}
		if (token[i] == '\"')
		{
			next = find_next_quote(token, '\"', i);
			if (next == -1)
				return (0);
			i = next;
		}
		i++;
	}
	return (1);
}

void	find_dollar(t_info *token, t_envp *_env)
{
	t_info	*head;
	char	*tmp;

	head = token;
	while (head)
	{
		if (check_envp(head->cmd))
		{
			tmp = head->cmd;
			head->cmd = parse_dollar(head->cmd, _env);
			free(tmp);
		}
		head = head->next;
	}
}
