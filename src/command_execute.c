/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:51 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 14:32:52 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**make_second_arg(char *str, t_info *arg) // 쿼터가 지워진 list를 순회하며 2차원 배열로 적절히 뱉어보자..
{
	t_info	*tmp;

	tmp = arg;
	while (tmp)
	{
		if (tmp->cmd == '|' && tmp->type == PIPE)
			return (do_split_pipe(str, tmp));
		tmp = tmp->next;
	}
	return (ft_split(str));
}

char	*delete_all_quote_str(char *str)
{
	char	*cleared;
	int		i;
	int		count;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	i = 0;
	cleared = (char *)malloc(sizeof(char) * (ft_strlen(str) - count) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
			cleared[i] == str[i];
		i++;
	}
	return (cleared);
}

char	**do_split_pipe(char *str, t_info *arg)
{
	t_info	*tmp;
	char	*line;
	char	**splitted_str;

	tmp = arg;
	line = delete_all_quote_str(str);
	splitted_str = ft_split(line, '|');
	while (tmp)
	{
		if (tmp->type != WORD)
		{
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}