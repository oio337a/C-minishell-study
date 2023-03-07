/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:33:42 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/07 20:33:13 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. 쿼터 개수 판별 -> 1. 하나의 str 총 길이꺼 다 세야됨? -> 홀짝 맞는지
	1.1 이미 잘린 리스트 쿼터 지운 채로 다시 재할당할 때 쿼터 개수 빼서 malloc해야됨
*/
// 리스트 순회 -> syntax 확인
// 리스트 순회 -> 쿼터 갯수 확인 후 쿼터 제거 및 환경변수 처리 ' '-> 없애버려 " "-> 알맞은거 찾아서 넣어주기
// <<< 들어오면 신신택택스  에에러러
static int	*count_q(char *munja)
{
	int	*q;
	int	i;

	q = (int *)malloc(sizeof(int) * 2);
	i = -1;
	q[0] = 0;
	q[1] = 0;
	while (munja[++i])
	{
		if (munja[i] == '\"')
			q[1]++;
		else if (munja[i] == '\'')
			q[0]++;
	}
	return (q);
}

static int	find_next_quotes(char *line, char quote, int quote_idx)
{
	int	next_idx;

	next_idx = quote_idx + 1;
	while (line[next_idx])
	{
		if (line[next_idx] == quote)
			return (next_idx);
		next_idx++;
	}
	return (-1);
}

static int	here_quote(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i + len])
	{
		if (line[i + len] == '\''
			|| line[i + len] == '\"' || line[i + len] != '\0')
			return (len);
		len++;
	}
	return (-1); // -1 이면 오류 처리 해보자
}

static char	*get_full_token(t_info *cmd)
{
	t_info	*head;
	char	*tmp;
	char	*full_token;

	head = cmd;
	full_token = ft_strjoin("", head->cmd);
	head = head->next;
	while (head != NULL)
	{
		tmp = full_token;
		full_token = ft_strjoin(full_token, head->cmd);
		free(tmp);
		head = head->next;
	}
	list_delete(&cmd);
	return (full_token);
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
	while (token->cmd[i])
	{
		if (token->cmd[i] == '\'')
		{
			next_idx = find_next_quotes(token->cmd, '\'', i);
			clear_token = ft_substr(token->cmd, i + 1, next_idx - 1);
			insert_list(cmd, clear_token, WORD);
			free(clear_token);
			i += next_idx;
		}
		else if (token->cmd[i] == '\"')
		{
			next_idx = find_next_quotes(token->cmd, '\"', i);
			clear_token = ft_substr(token->cmd, i + 1, next_idx - 1);
			insert_list(cmd, clear_token, WORD);
			free(clear_token);
			i += next_idx;
		}
		else
		{
			clear_token = ft_substr(token->cmd, i, here_quote(token->cmd, i));
			insert_list(cmd, clear_token, WORD);
			free(clear_token);
			i += here_quote(token->cmd, i) - 1;
		}
		i++;
	}
	tmp = token->cmd;
	token->cmd = get_full_token(cmd);
	free(tmp);
}

static int	is_qoute(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

void	clear_qoute_in_token(t_info *token)
{
	t_info	*head;
	char	*tmp;

	head = token;
	while (head != NULL)
	{
		if (is_qoute(head->cmd) >= 0)
		{
			// tmp = head->cmd;
			delete_quote(head);
			// free(tmp);
		}
		head = head->next;
	}
}
