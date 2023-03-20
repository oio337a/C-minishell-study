/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:59:28 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 18:12:27 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char line)
{
	if (line != 32 && !(line >= 9 && line <= 13))
		return (1);
	return (0);
}

int	modu_spacebarya(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (1);
		line++;
	}
	return (0);
}

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
	insert_list(info, bulk, WORD);
	free(tmp);
}

static int	reminder_in_quote(char quote, int i, char *line)
{
	if (quote == '\"')
	{
		if (find_next_quote(line, '\"', i) == -1)
			i++;
		else
			i = find_next_quote(line, '\"', i);
	}
	else if (quote == '\'')
	{
		if (find_next_quote(line, '\'', i) == -1)
			i++;
		else
			i = find_next_quote(line, '\'', i);
	}
	return (i);
}

void	ft_remainder(t_info *info, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*line)[i] && is_whitespace((*line)[i]) && (*line)[i] != '>'
		&& (*line)[i] != '<')
		i = reminder_in_quote((*line)[i], i, *line) + 1;
	tmp = ft_substr(*line, 0, i);
	*line += ft_strlen(tmp) - 1;
	insert_list(info, tmp, WORD);
	free(tmp);
}
