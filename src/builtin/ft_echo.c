/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:19 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 17:27:58 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_last_exit_code;

static int	find_option(t_info *arg)
{
	int		i;
	int		option_idx;
	t_info	*temp;

	option_idx = 0;
	temp = arg->next;
	while (temp && temp->cmd[0] == '-' && temp->cmd[1] == 'n')
	{
		i = 1;
		while (temp->cmd[++i])
		{
			if (temp->cmd[i] != 'n')
				return (option_idx);
		}
		option_idx++;
		temp = temp->next;
	}
	return (option_idx);
}

static void	ft_pcmd(t_info *temp)
{
	while (temp)
	{
		if (temp->type == WORD)
		{
			if (!ft_strncmp(temp->cmd, "$?", 2))
				printf("%i%s", g_last_exit_code, (temp->cmd + 2));
			else
				printf("%s", temp->cmd);
			printf(" ");
		}
		temp = temp->next;
	}
	g_last_exit_code = 0;
}

void	ft_echo(t_info *arg)
{
	int		option;
	int		i;
	t_info	*temp;

	option = find_option(arg);
	temp = arg->next;
	i = 1;
	if (option)
	{
		while (temp && option--)
			temp = temp->next;
		ft_pcmd(temp);
	}
	else
	{
		ft_pcmd(temp);
		printf("\n");
	}
}
