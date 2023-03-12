/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:35 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/12 14:23:11 by sohyupar         ###   ########.fr       */
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
int g_last_exit_code;

int	check_sec(t_info *arg)
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
	while (check > 0)
	{
		check /= 10;
		digit_idx++;
	}
	return (digit_idx == cmd_len);
}

int	list_get_size(t_info *lst)
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

long long	ft_exit(t_info *arg)
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
			exit_errno(check_arg, arg->cmd, 1);
		else if (!check_arg)
		{
			exit_errno(check_arg, (arg->next)->cmd, 255);
			exit(g_last_exit_code);
		}
	}
	else // 인자 1개 들어왓을 때
	{
		if (check_arg)
		{
			g_last_exit_code = ft_atoi((arg->next)->cmd) % 256;
			exit(g_last_exit_code);
		}
		else
		{
			exit_errno(check_arg, (arg->next)->cmd, 255);
			exit(g_last_exit_code);
		}
	}
	return (g_last_exit_code);
}

// int main()
// {
// 	/*
// 		1. exit 만 들어왓다.
// 			=> exit\n 출력  exit code 0 O
// 		2. 3개다
// 			exit q24 142  -> numeric 255  O
// 			exit 142 242 -> 출력만, 1로 반환 O
// 		3. 2개다
// 			eixt qkw -> numeric 255 O
// 			exit 2 -> 2로 exit O
// 		all clear ~!~!~!
// 	*/
// 	t_info	*arg;

// 	arg = malloc(sizeof(t_info));
// 	arg->next = NULL;

// 	t_info	*node1 = malloc(sizeof(t_info));
// 	node1->next = arg->next;
// 	node1->cmd = "exit";
// 	arg->next = node1;

// 	t_info	*node2 = malloc(sizeof(t_info));
// 	node2->next = node1->next;
// 	node2->cmd = "123";
// 	node1->next = node2;

// 	t_info	*node3 = malloc(sizeof(t_info));
// 	node3->next = node2->next;
// 	node3->cmd = "1";
// 	node2->next = node3;

// 	// t_info	*node4 = malloc(sizeof(t_info));
// 	// node4->next = node3->next;
// 	// node4->cmd = "-n";
// 	// node3->next = node4;

// 	t_info *curr = arg->next;
// 	ft_exit(curr);
// 	return (0);
// }
/*
// 여러분~~~ 이런 경우 생각 해야해요.  exit > e 또는 exit << EOF 이런거 말이죵~!~!!~!
exit 뒤의!!

0. 인자가 없다
exit 출력, 실행, exit code 0

1. 인자가 1개다
	1.1 exit char -> exit 출력, exit 실행, 오류 문구 출력(numeric arg required), exit code -> 255
	1.2 exit numeric -> eixt 출력, 실행, exit code -> numeric

2. 인자가 2개다
	1. exit !!!char!!! numeric ->exit 출력, 실행, 오류문구 출력(numeric arg required), exit code -> 255
	2. exit !!!!numeric!!!! numeric -> exit 출력, >실행 안함!<, 오류문구 출력(too many arg), exit code -> 1
*/
