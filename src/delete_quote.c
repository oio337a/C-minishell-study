/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:33:42 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/20 18:13:21 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quotes_case(t_info *list, char *cmd, int i, char quote)
{
	char	*clear_token;
	int		next_idx;

	next_idx = find_next_quote(cmd, quote, i);
	printf("pp %d", i);
	printf("after next : %d, %c\n", next_idx, cmd[next_idx]);
	// exit(1);
	if (next_idx == i + 1)
		i++;
	else
	{
		clear_token = ft_substr(cmd, i + 1, next_idx - i - 1);
		printf("clear token : %s\n", clear_token);
		// exit(1);
		insert_list(list, clear_token, WORD);
		free(clear_token);
		i = next_idx;
	}
	return (i);
}

static int	not_quotes(t_info *list, char *cmd, int i)
{
	char	*clear_token;

	clear_token = ft_substr(cmd, i, here_quote(cmd + i));
	insert_list(list, clear_token, WORD);
	free(clear_token);
	printf("not quote idx %d, here_q :%d \n", i, here_quote(cmd + i));
	i += here_quote(cmd + i) - 1;
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
			i = quotes_case(cmd, token->cmd, i, '\'');
		else if (token->cmd[i] == '\"')
			i = quotes_case(cmd, token->cmd, i, '\"');
		else
			i = not_quotes(cmd, token->cmd, i);
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
