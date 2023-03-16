/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:59:28 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/16 22:37:54 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_process(t_info *info, char **line)
{
	char	*bulk;
	char	*tmp;

	bulk = quote_bulk(*line, **line);
	if (!ft_strlen(bulk))
	{
		*line += 2;
		while (**line == '\"' && **line != '\0' && **line != ' ')
		{
			if (**(line + 1) != '\"')
				break ;
			*line += 2;
		}
	}
	else
		*line += ft_strlen(bulk);
	tmp = bulk;
	if (**line != ' ')
	{
		bulk = get_after_quote(*line, tmp);
		*line += (ft_strlen(bulk) - ft_strlen(tmp));
	}
	printf("bulk : %s\n", bulk);
	insert_list(info, bulk, WORD);
	free(tmp);
}

void	ft_remainder(t_info *info, char **line)
{
	char	*tmp;
	int		i;
	int		next_q;
	char	*quote_bulk;
	int		next_idx;

	i = 0;
	next_q = -1;
	// if ((*line)[i] != '\'' && (*line)[i] != '\"')
	// 	quote_process(info, line);
	while (*line[i]) // a=" lqj wj lsljxlj wjlsj " -> i 여기 while문 수정
	{
		if ((*line)[i] == '\'')
		{
			next_idx = find_next_quote(*line, '\'', i);
			quote_bulk = ft_substr(*line, i + 1, next_idx);
			i += next_idx;
		}
		else if ((*line)[i] == '\"')
		{
			next_idx = find_next_quote(*line, '\"', i);
			quote_bulk = ft_substr(*line, i + 1, next_idx);
			i += next_idx;
		}
		i++;
	}
	while ((*line)[i] && is_whitespace2((*line)[i]) && (*line)[i] != '>'
		&& (*line)[i] != '<')
		{
			//여기 if문만 넣음
			if ((*line)[i] == '\'' || (*line)[i] == '\"')
			{
				// 쿼터~ 다음 쿼터까지 substr로 떼오고 idx 밀면 밖에서 알아서 끝가지 밀듯?
				// a=" wklj 's'j jxlj lwj jslj w"aaaa
				quote_bulk = ft_substr(*line, (*line)[i]);
			}
		}
		i++;
	tmp = ft_substr(*line, 0, i);
	*line += ft_strlen(tmp) - 1;
	insert_list(info, tmp, WORD);
	free(tmp);
}
