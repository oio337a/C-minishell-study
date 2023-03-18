/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:59:28 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/18 15:59:31 by sohyupar         ###   ########.fr       */
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
	insert_list(info, bulk, WORD);
	free(tmp);
}

void	ft_remainder(t_info *info, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*line)[i] && is_whitespace2((*line)[i]) && (*line)[i] != '>'
		&& (*line)[i] != '<')
	{
		if ((*line)[i] == '\"')
			i += find_next_quote(*line, '\"', i);
		if ((*line)[i] == '\"')
			i += find_next_quote(*line, '\"', i);
		i++;
	}
	tmp = ft_substr(*line, 0, i);
	*line += ft_strlen(tmp) - 1;
	insert_list(info, tmp, WORD);
	free(tmp);
}
