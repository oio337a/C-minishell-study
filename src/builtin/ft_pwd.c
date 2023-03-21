/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:56 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 21:16:44 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_last_exit_code;

void	ft_pwd(t_envp *envp)
{
	char	*path;
	char	*pwd;

	path = find_envp(envp, "PWD");
	if (path)
		pwd = ft_strdup(path);
	else
		pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		g_last_exit_code = 1;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	g_last_exit_code = 0;
	return ;
}
