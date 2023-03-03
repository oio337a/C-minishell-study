/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:25 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 18:32:16 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_parser(char *line, t_info *info)
{
	char	**a_p;
	char	**cmd;
	char	*v_line;
	int		i;
	int		j;

	i = 0;
	a_p = ft_split(line, '|'); // "ls" -al / "cat" -e / wc -l
	// if (!a_p)
	// 	return (NULL);
	while (a_p[i])
	{
		// cmd = ft_split(a_p[i], ' '); // cmd = "ls" / -al?
		v_line = validate_readline(a_p[i], count_q(a_p[i])); //-> str -> ls -al
		///쿼터 확인하는 함수!
		j = 0;
		while (v_line[j])
		{
			insert_list(info, v_line[j]);
			j++;
		}
		// if (*a_p[i] == '\'' || '\"')
			// quoters = 1;
		ft_free(cmd);
		i++;
	}
	// ft_free(a_p);
}
