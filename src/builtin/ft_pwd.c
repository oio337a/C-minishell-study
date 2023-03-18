/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:56 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/19 01:13:08 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_last_exit_code;

void	ft_pwd(void) //성공시 0, 실패시 그 이상 리턴
{
	char	*pwd;

	pwd = getcwd(NULL, 0); //현재 프로그램의 절대경로 리턴. 사용 후 프리해야함
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
