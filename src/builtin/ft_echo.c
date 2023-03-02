/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:19 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 21:09:04 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	------------------------------
	이거 테스트 해봐야함
	echo
	echo hello
	echo -n hello
	echo hello -n 
	echo -nnn hello
	echo -n-n hello
	echo -nnn hello -n 
	echo -nnn -n hello
	echo -
	echo - -
	echo --
	echo -n -n -nhjk hello
	echo -n -n -n -n -n hello
	echo "hello World"
	echo "hello            World"
	echo \\\"\'''\"
	------------------------------
	option 플래그가 0이면 \n 개행 출력.

	싱글쿼트일 때 환경변수 치환하지않고 그대로 출력.

	/Users/daelee/Desktop/42cursus/minishell $ echo '$PWD'
	> $PWD
	/Users/daelee/Desktop/42cursus/minishell $ echo "$PWD"
	> /Users/daelee/Desktop/42cursus/minishell

	echo $?
	g_exit_status 값 출력.

	echo -nnnnnn hello
	-> echo -n hello 와 동일

	echo hello ; ; 혹은 echo hello | |
	-> syntax error near unexpected token ;'` (258)
*/

static int	find_option(char **arg)
{
	int	i;

	if (ft_strncmp("-n", arg[1], 2))
	{
		i = 1;
		while (arg[++i])
		{
			if (!ft_strncmp("-n", arg[i], 2))
				return (i);
		}
	}
	return (0);
}

void	ft_echo(char **arg)
{
	int	option;
	int	i;

	option = find_option(arg);
	i = 1;
	if (option) // -n 이 있을때
	{
		while (arg[option])
		{
			write(1, arg[option], ft_strlen(arg[option]));
			option++;
			if (arg[option])
				write(1, " ", 1);
			option++;
		}
	}
	else // -n 이 없을때
	{
		while (arg[i])
		{
			write(1, arg[i], ft_strlen(arg[i]));
			i++;
			if (arg[i])
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
}
