/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote_before.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:33:42 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/20 15:55:15 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quotes_case(t_info *list, char *cmd, int i, char quote)
{
	char	*clear_token;
	int		next_idx;

	next_idx = find_next_quote(cmd, '\'', i);
	if (next_idx == i + 1)
		i++;
	else
	{
		clear_token = ft_substr(cmd, i + 1, next_idx - i - 1);
		insert_list(list, clear_token, WORD);
		free(clear_token);
		i += next_idx;
	}
	return (i);
}

static int	not_quotes(t_info *cmd, t_info *arg, int i)
{
	char	*clear_token;

	clear_token = ft_substr(arg->cmd, i, here_quote(arg->cmd + i));
	insert_list(cmd, clear_token, WORD);
	free(clear_token);
	i += here_quote(arg->cmd + i) - 1;
	return (i);
}

static void	include_nothing(char *line, t_info *token)
{
	line = token->cmd;
	token->cmd = ft_strdup("");
	free(line);
}

static void	delete_quote(t_info *token)
{
	int		i;
	char	*clear_token;
	int		next_idx;
	t_info	*cmd;
	char	*tmp;

	i = 0;
	cmd = init_list();
	if (!ft_strlen(token->cmd))
	{
		include_nothing(token->cmd, token);
		return ;
	}
	while (token->cmd[i])
	{
		if (token->cmd[i] == '\'')
		{
			next_idx = find_next_quote(token->cmd, '\'', i);
			if (next_idx == i + 1)
				i++;
			else
			{
				clear_token = ft_substr(token->cmd, i + 1, next_idx - i - 1);
				insert_list(cmd, clear_token, WORD);
				free(clear_token);
				i += next_idx;
			}
			// i = quotes_case(cmd, token, i, '\'');
		}
		else if (token->cmd[i] == '\"')
		{
			next_idx = find_next_quote(token->cmd, '\"', i);
			if (next_idx == i + 1)
				i++;
			else
			{
				clear_token = ft_substr(token->cmd, i + 1, next_idx - i - 1);
				insert_list(cmd, clear_token, WORD);
				free(clear_token);
				i += next_idx;
			}
			// i = quotes_case(cmd, token, i, '\"');
		}
		else
		{
			clear_token = ft_substr(token->cmd, i, here_quote(token->cmd + i));
			insert_list(cmd, clear_token, WORD);
			free(clear_token);
			i += here_quote(token->cmd + i) - 1;
			// i = not_quotes(cmd, token, i);
		}
		i++;
	}
	tmp = token->cmd;
	token->cmd = get_full_token(cmd);
	free(tmp);
}

void	clear_quote_in_token(t_info *token)
{
	t_info	*head;

	head = token;
	while (head != NULL)
	{
		if (is_quote(head->cmd) >= 0)
			delete_quote(head);
		head = head->next;
	}
}
