/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:32:13 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/13 22:40:13 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_whitespace2(char line)
{
	if (line != 32 && !(line >= 9 && line <= 13))
		return (1);
	return (0);
}

static char	*quote_bulk(char *line, char c)
{
	int		i;
	char	*bulk;

	i = 1;
	while (line[i] != c)
		i++;
	bulk = ft_substr(line, 0, i + 1);
	return (bulk);
}

static char	*get_after_quote(char *line, char *bulk)
{
	char	*tmp;
	char	*real_bulk;
	int		i;

	i = 0;
	while (is_whitespace2(line[i]))
		i++;
	tmp = ft_substr(line, 0, i);
	real_bulk = ft_strjoin(bulk, tmp);
	free(tmp);
	return (real_bulk);
}

int	redir_check(t_info *info, char *line, int i)
{
	char	*temp;
	int		type;

	type = HEREDOC_IN;
	if (line[i] == line[i + 1])
	{
		if (line[i] == '>')
			type = HEREDOC_OUT;
		temp = ft_substr(line, i, i + 1);
		insert_list(info, temp, type);
		free(temp);
		i++;
	}
	else
	{
		if (line[i] == '>')
			insert_list(info, ">", REDIR_OUT);
		else if (line[i] == '<')
			insert_list(info, "<", REDIR_IN);
		else
			insert_list(info, "|", PIPE);
	}
	return (i);
}

// static char	*char_to_str(char c)
// {
// 	char	*ret;

// 	ret = malloc(2);
// 	ret[0] = c;
// 	ret[1] = '\0';
// 	return (ret);
// }

int	bulk_bulk(t_info *info, char *line, int i)
{
	char	*tmp;
	int		j;

	j = i;
	while (line[j] && is_whitespace2(line[j]))
		j++;
	tmp = ft_substr(line, i, j);
	insert_list(info, tmp, WORD);
	i += j;
	free(tmp);
	return (i);
}

int	slice_quote_bulk(t_info *info, char *line, int i)
{
	char	*bulk;
	char	*tmp;

	bulk = quote_bulk(line, line[i]);
	tmp = bulk;
	i += ft_strlen(bulk);
	if (line[i] != ' ')
	{
		bulk = get_after_quote(line, tmp);
		i += (ft_strlen(bulk) - ft_strlen(tmp));
	}
	insert_list(info, bulk, WORD);
	free(tmp);
	return (i);
}

void	str_tokenize(t_info *info, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			i = redir_check(info, &line, i);
		else if (line[i] == '\"' || line[i] == '\'')
			i = slice_quote_bulk(info, line, i);
		else if (line[i] != '>' && line[i] != '<'
			&& line[i] != '|' && line[i] != ' ')
			i = bulk_bulk(info, line, i);
		if (line[i] == '\0')
			break ;
	}
}

// 용민아 내일 이거 해야 되는데 기억해!!!
// 이거 함수들 다 인덱스 받아와서 건드린다음에 보내줘야해.. 할 수 있지??
// 힘내 용민 넌 할 수있어!! 오늘도 수고했어!!! ㅎㅎ