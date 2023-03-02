#include "../includes/minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT) //ctrl + c
	{
		write(1, "\n", 1);
		rl_on_new_line(); //컴파일 시 gcc -lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include
		rl_replace_line("", 0); // 두번째 인자 0이면 undo list 초기화 x, 1이면 초기화 => 어떻게 할지 정하기
		rl_redisplay();	//근데 brew readline이 안됩니다 .. 
	}
	else if (signum == SIGQUIT) //ctrl + '\'
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

char 

void	

signal(SIGINT, handler);
signal(SIGQUIT, handler);

//ctrl + d == 시그널이 아니라, 아스키코드 4번 EOT임. 근데 ctrl+c도 아스키 3번, ctrl+'\'도 아스키 28인디 . .
//글고 ctrl + d가 시그널 15번 SIGTERM 이라는 사람도 있음 ; ㅠ
//따라서 따로 시그널 처리할 필요 없이, char == 4 && idx == 0일 때 exit 출력 후 종료하면 됨

/*
빈 프롬프트에 ctrl-C 사용 -> 새로운 프롬포트
빈 프롬프트에 ctrl-\ 사용 -> 아무일 x
빈 프롬프트에 ctrl-D 사용 -> 쉘 종료

무언가 써있는 프롬프트에 ctrl-C 사용, 엔터로 버퍼에 남아있는지 확인 -> 새 프롬포트
무언가 써있는 프롬프트에 ctrl-\ 사용 -> 아무일 x
무언가 써있는 프롬프트에 ctrl-D 사용 -> 아무일 x. ctrl+d가 eof면 왜 안끝남?제발

자식 프로세스 ! 
cat 이나 grep 실행 도중 (표준 입력) ctrl-C 사용 -> ^C\n띄우며 표준입력 종료
cat 이나 grep 실행 도중 ctrl-\ 사용 -> ^\Quit: 3\n띄우며 표준입력 종료.........
cat 이나 grep 실행 도중 ctrl-D 사용 -> 표준입력 종료
*/