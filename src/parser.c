/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:25 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 15:47:45 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_parser(char *line, t_info *info)
{
	char	**a_p;
	char	**cmd;
	// int		quoters;
	int		i;
	int		j;

	i = 0;
	// quoters = 0;
	a_p = ft_split(line, '|');
	// if (!a_p)
	// 	return (NULL);
	while (a_p[i])
	{
		cmd = ft_split(a_p[i], ' ');
		///쿼터 확인하는 함수!
		j = 0;
		while (cmd[j])
		{
			insert_list(info, cmd[j]);
			j++;
		}
		// if (*a_p[i] == '\'' || '\"')
			// quoters = 1;
		ft_free(cmd);
		i++;
	}
	// ft_free(a_p);
}