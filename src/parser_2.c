/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:37:57 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 20:08:49 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*count_q(char *munja)
{
	int	*q;
	int	i;

	q = malloc(8);
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
