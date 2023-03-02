/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:56 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 21:11:35 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*
	envp 에서 pwd 찾고 출력
*/
#include "../../includes/minishell.h"

char	*ft_pwd(char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	while (ft_strncmp("PWD=", envp[i], 4))
		i++;
	pwd = envp[i] + 4;
	return (pwd);
}
