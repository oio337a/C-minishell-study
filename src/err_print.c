/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:06:57 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/21 22:46:08 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

static void	common_errnos(char *cmd, int res, int fd, int type)
{
	if (type != 3)
		ft_putstr_fd("Nakishell: ", fd);
	ft_putstr_fd(cmd, fd);
	if (type == 1)
		ft_putstr_fd(": command not found", fd);
	else if (type == 2)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(strerror(res), fd);
	}
	ft_putstr_fd("\n", fd);
	g_last_exit_code = 127;
}

void	common_errno(char *cmd, int res, char *next_arg, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	if (res == 127)
	{
		if (!ft_strncmp(cmd, "$?", 2))
		{
			printf("Nakishell: %d%s: command not found\n", \
			g_last_exit_code, (cmd + 2));
			g_last_exit_code = 127;
			return ;
		}
		common_errnos(cmd, res, fd, 1);
		return ;
	}
	if (next_arg == NULL)
	{
		common_errnos(cmd, res, fd, 2);
		g_last_exit_code = 1;
	}
	else
		bulga(next_arg, fd);
}

int	envp_errno(char *err_value, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd("Nakishell$: export: `", fd);
	ft_putstr_fd(err_value, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
	g_last_exit_code = 1;
	return (0);
}

void	cd_errno(char *err_value, int res)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd("Nakishell$: cd: ", STDOUT_FILENO);
	ft_putstr_fd(err_value, STDOUT_FILENO);
	if (res == 1)
		ft_putstr_fd(": No such directory\n", STDOUT_FILENO);
	else if (res == 2)
		ft_putstr_fd(": not set\n", STDOUT_FILENO);
	g_last_exit_code = 1;
}

void	exit_errno(int arg_status, char *cmd, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	if (arg_status != 0)
	{
		ft_putstr_fd("Nakishell$: ", fd);
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": too many arguments\n", fd);
		g_last_exit_code = 1;
	}
	else
	{
		ft_putstr_fd("Nakishell$: exit: ", fd);
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": numeric argument required\n", fd);
		g_last_exit_code = 255;
		exit(g_last_exit_code);
	}
}
