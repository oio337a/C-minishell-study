/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:35 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 16:37:32 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_last_exit_code;

static int	check_sec(t_info *arg)
{
	t_info	*temp;
	int		digit_idx;
	int		cmd_len;
	int		check;

	temp = malloc(sizeof(t_info));
	temp = arg->next;
	digit_idx = 0;
	cmd_len = ft_strlen(temp->cmd);
	check = ft_atoi(&temp->cmd[digit_idx]);
	if (check <= 0)
	{
		digit_idx++;
		check *= -1;
	}
	while (check > 0)
	{
		check /= 10;
		digit_idx++;
	}
	return (digit_idx == cmd_len);
}

static int	list_get_size(t_info *lst)
{
	int		i;
	t_info	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

static void	one_arg(int check_arg, t_info *arg)
{
	if (check_arg)
	{
		g_last_exit_code = ft_atoi((arg->next)->cmd) % 256;
		exit(g_last_exit_code);
	}
	else
		exit_errno(check_arg, (arg->next)->cmd, 255);
}

void	ft_exit(t_info *arg)
{
	int	check_arg;
	int	arg_size;

	arg_size = list_get_size(arg);
	write(1, "exit\n", 5);
	if (arg_size == 1)
	{
		g_last_exit_code = 0;
		exit(g_last_exit_code);
	}
	check_arg = check_sec(arg);
	if (arg_size >= 3)
	{
		if (check_arg)
			exit_errno(check_arg, arg->cmd, STDOUT_FILENO);
		else
			exit_errno(check_arg, (arg->next)->cmd, STDOUT_FILENO);
	}
	else
		one_arg(check_arg, arg);
}
