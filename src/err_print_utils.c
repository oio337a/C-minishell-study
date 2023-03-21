/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:51:01 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 20:54:35 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

void	bulga(char *next_arg, int fd)
{
	ft_putstr_fd(next_arg, fd);
	ft_putstr_fd(strerror(errno), fd);
	ft_putstr_fd("\n", fd);
	g_last_exit_code = 1;
}
