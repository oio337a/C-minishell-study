/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:03:30 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/15 21:31:27 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ctrl + d == 시그널이 아니라, 아스키코드 4번 EOT임
//따라서 따로 시그널 처리할 필요 없이, char == 4 && idx == 0일 때 exit 출력 후 종료하면 됨

/*
^C 제어문자 반향 출력 안 하는 거 배쉬 버전마다 달라서 처리 안 했습니 다람쥐
*/

int	g_exit_status;

// void	handler(int signum)
// {
// 	if (signum == SIGINT) //ctrl + c
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line(); //개행문자 출력 시 newline으로 이동한 것을 업데이트 해주는 함수
// 		rl_replace_line("", 1); //내부 버퍼를 ""로 바꾸는 함수
// 		rl_redisplay(); //버퍼와 프롬포트 재출력
// 		g_exit_status = 1;
// 	}
// }
/*
static void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, NULL, 0);
	}
}
*/
// void	set_signal(t_signal mode)
// {
// 	if (mode == CHILD) // 자식프로세스
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL); // SIG_DFL는 원래 설정된 시그널 동작
// 	}
// 	else if (mode == WAITING) // 자식 기다리는 부모 프로세스
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (mode == HEREDOC)
// 	{
// 		// signal(SIGINT, heredoc_handler);
// 		// signal(SIGINT, handler);
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (mode == GENERAL)
// 	{
// 		signal(SIGINT, handler);
// 		signal(SIGQUIT, SIG_IGN); // SIG_IGN는 시그널 무시
// 	}
// }

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
