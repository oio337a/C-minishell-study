/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:30 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 18:06:20 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

//ctrl + d == 시그널이 아니라, 아스키코드 4번 EOT임
//따라서 따로 시그널 처리할 필요 없이, char == 4 && idx == 0일 때 exit 출력 후 종료하면 됨

/*
빈 프롬프트에 ctrl-D 사용 -> 쉘 종료
무언가 써있는 프롬프트에 ctrl-D 사용 -> 아무일 x. ctrl+d가 eof면 왜 안끝남?제발
히어독에 ctrl-D -> 같은 줄에 띄어쓰고 입력 종료
*/

/*
^C 제어문자 반향 출력 안 하는 거 배쉬 버전마다 달라서 처리 안 했습니 다람쥐
*/

void	handler(int signum)
{
	if (signum == SIGINT) //ctrl + c
	{
		write(1, "\n", 1);
		rl_on_new_line(); //개행문자 출력 시 newline으로 이동한 것을 업데이트 해주는 함수
		rl_replace_line("", 1); //내부 버퍼를 ""로 바꾸는 함수
		rl_redisplay(); //버퍼와 프롬포트 재출력
		g_last_exit_code = 1;
	}
}

void	wait_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_last_exit_code = 33280;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "Quit : 3\n", 9);
		g_last_exit_code = 131;
	}
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_last_exit_code = 130;
		exit(g_last_exit_code);
	}
	else if (signum == SIGQUIT)
	{
		g_last_exit_code = 131;
		exit(g_last_exit_code);
	}
}

void	set_signal(t_signal mode)
{
	if (mode == CHILD) // 자식프로세스
	{ // SIG_DFL는 원래 설정된 시그널 동작
		signal(SIGINT, SIG_DFL); // (^C\n띄우며 표준입력 종료) -> exit code 130
		signal(SIGQUIT, SIG_DFL); // (^\Quit: 3\n띄우며 표준입력 종료) -> exit code 131
	}
	else if (mode == WAITING) // 자식 기다리는 부모 프로세스
	{
		signal(SIGINT, SIG_IGN); // SIG_IGN는 시그널 무시
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == GENERAL) // 기본 상태
	{
		signal(SIGINT, handler); // exit code 1
		signal(SIGQUIT, SIG_IGN);
	}
}
