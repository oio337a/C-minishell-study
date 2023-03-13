/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:19 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/12 16:22:13 by sohyupar         ###   ########.fr       */
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
int	g_last_exit_code;

static int	find_option(t_info *arg)
{
	// echo 다음에 -n 이 있으면 -n 으로 시작해야함.
	// echo -nn 블라블라 
	// echo aaaa -n daaa => aaaa -n daaa
	int		i;
	int		option_idx;
	t_info	*temp;

	option_idx = 0;
	temp = arg->next; // echo 명령어 건너기
	// 1. -n 으로 시작해야 하고 다음은 n만 올 수 있다.
	while (temp && temp->cmd[0] == '-' && temp->cmd[1] == 'n')
	{
		i = 1;
		while (temp->cmd[++i])
		{
			if (temp->cmd[i] != 'n')
				return (option_idx);
		}
		option_idx++;
		temp = temp->next;
	}
	return (option_idx);
}

static void	ft_pcmd(t_info *temp)
{
	while (temp)
	{
		if (temp->type == WORD)
		{
			if (!ft_strncmp(temp->cmd, "$?", 2))
				printf("%i%s", g_last_exit_code, (temp->cmd + 2));
			else
				printf("%s", temp->cmd);
			// if (!temp->next)
			// 	break ;
			// temp = temp->next;
			printf(" ");
		}
		// else
		// {
			// if (!temp->next)
				// break ;
			temp = temp->next;
		// }
	}
}

void	ft_echo(t_info *arg)
{
	int		option;
	int		i;
	t_info	*temp;

	option = find_option(arg);
	temp = arg->next;
	i = 1;
	if (option)
	{
		while (temp && option--)
			temp = temp->next;
		ft_pcmd(temp);
	}
	else
	{
		ft_pcmd(temp);
		// write(1, "\n", 1);
		printf("\n");
	}
}

// int main()
// {
// 	t_info	*arg;

// 	arg = malloc(sizeof(t_info));
// 	arg->next = NULL;

// 	t_info	*node1 = malloc(sizeof(t_info));
// 	node1->next = arg->next;
// 	node1->cmd = "echo";
// 	arg->next = node1;

// 	t_info	*node2 = malloc(sizeof(t_info));
// 	node2->next = node1->next;
// 	node2->cmd = "-naa";
// 	node1->next = node2;

// 	t_info	*node3 = malloc(sizeof(t_info));
// 	node3->next = node2->next;
// 	node3->cmd = "hello";
// 	node2->next = node3;

// 	t_info	*node4 = malloc(sizeof(t_info));
// 	node4->next = node3->next;
// 	node4->cmd = "-n";
// 	node3->next = node4;

// 	t_info *curr = arg->next;
// 	ft_echo(curr);
// 	return (0);
// }
