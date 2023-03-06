/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:56 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/06 16:25:18 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
char	*ft_pwd(char **envp) // envp에서 pwd찾고 출력 -> unset PWD 시 세그폴트 뜹니다.
{
	int		i;
	char	*pwd;

	i = 0;
	while (ft_strncmp("PWD=", envp[i], 4))
		i++;
	pwd = envp[i] + 4;
	return (pwd);
}
*/

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0); //현재 프로그램의 절대경로 리턴. 사용 후 프리해야함
	if (!pwd)
		return (1);
	printf("%s", pwd);
	free(pwd);
	return (0);
}
