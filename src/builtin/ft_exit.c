/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:35 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/08 18:29:06 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	exit 만 입력 받았다면 exit 출력 후 EXIT_SUCCESS 넘기며 종료

	exit 뒤에 인자가 있다면 그 인자를 부모에게 상태값으로 전달 (ex exit 127), exit 출력하지 않고 종료

	exit 뒤의 숫자 인자가 2개 이상이라면 "exit\n" "bash: exit: too many arguments" 두 줄 출력 후 쉘 종료 X

	exit 뒤의 인자가 숫자가 아닌 게 있다면 "bash: exit: 첫 번째 인자: numeric argument required" 출력 후 쉘 종료

	exit 범위는 0 ~ 255
	exit값 인자 자체는 long long 범위까지 처리가 가능함 long long을 넘어갈시 numeric error을 출력하면서 255로 exit
	255가 넘어가는 숫자는 %256함
*/

long long	ft_exit(t_info *arg)
{
	write(1, "exit\n", 5);
	
	if (ft_lstsize(arg) >= 3) // 투매니 알규먼트 레쓰고!
	{
		// bash: exit: too many arguments
		// last_exit_code = 1;
	}
	else if (ft_lstsize(arg) == 1) // 걍 exit (위 아래 위위 아래 위 아래 위위 아래)
	{
		last_exit_code = 0;
		exit(last_exit_code);
	}
	else
	{ // 여러분~~~ 이런 경우 생각 해야해요.  exit > e 또는 exit << EOF 이런거 말이죵~!~!!~!
		last_exit_code = (arg->next)->cmd;
		exit(last_exit_code);
	}
	return (last_exit_code);
}
