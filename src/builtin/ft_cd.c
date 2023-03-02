/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 21:09:00 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	cd, cd ~ 일때
	-> HOME 경로 찾아서 path에 저장 후 이동

	cd $변수 일때
	-> 변수 경로 찾아서 path에 저장 후 이동

	cd ~ 234 (cd ~ 후 인자가 들어왔을 때)
	-> 에러메세지 없이 ~로 이동

	cd $HSIDHSIHD (없는 환경변수일때)

	-> 에러메세지 없이 ~로 이동
*/
void	ft_cd(char **path)
{
	if (path[0] == "" || path[0] == "~")
	{
		
	}
	else
	{
		/*
			// if path[0] 이 있을때
			// else path[0] 이 없을 때
				{
					if 환경 변수 일때 
					else 
						bash: cd: asdf: No such file or directory
				}
		*/
			
	}
}
