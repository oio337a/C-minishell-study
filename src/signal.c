/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:30 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 16:02:51 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	control_d(char *str)
{
	if (!str)
	{
		printf("\033[1A\033[7Cexit"); //커서 위로 한 칸 올리고 7칸 앞에 출력. ANSI 이스케이프 시퀀스
		exit(0);
	}
	return ;
}

void	handler(int signum)
{
	if (signum == SIGINT) //ctrl + c
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	set_signal()
{
	if () //기본
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN); // SIG_IGN는 시그널 무시
	}
	else if () //
	{

	}
}

//ctrl + d == 시그널이 아니라, 아스키코드 4번 EOT임
//따라서 따로 시그널 처리할 필요 없이, char == 4 && idx == 0일 때 exit 출력 후 종료하면 됨

/*
기본 상태
ctrl-\ -> SIG_IGN
ctrl-C -> handler

자식 프로세스 ! cat 이나 grep 실행 도중 (표준 입력)
ctrl-C -> SIG_DFL (^C\n띄우며 표준입력 종료)
ctrl-\ -> SIG_DFL (^\Quit: 3\n띄우며 표준입력 종료)

자식 기다리는 부모 프로세스 -> both SIG_IGN

히어독 : 리미터 나올 때까지 입력
ctrl-C는 handler
ctrl-\는 SIG_IGN

빈 프롬프트에 ctrl-D 사용 -> 쉘 종료
무언가 써있는 프롬프트에 ctrl-D 사용 -> 아무일 x. ctrl+d가 eof면 왜 안끝남?제발
히어독에 ctrl-D -> 같은 줄에 띄어쓰고 입력 종료
*/