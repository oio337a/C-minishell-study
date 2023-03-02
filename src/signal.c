#include "../includes/minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT) //ctrl + c
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0); //컴파일 시 gcc -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
		rl_redisplay();
	}
	else if (signum == SIGQUIT) //ctrl + '\'
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

//ctrl + d == 시그널이 아니라, EOF


/*
빈 프롬프트에 ctrl-C 사용
빈 프롬프트에 ctrl-\ 사용
빈 프롬프트에 ctrl-D 사용

무언가 써있는 프롬프트에 ctrl-C 사용
엔터로 버퍼에 남아있는지 확인
무언가 써있는 프롬프트에 ctrl-\ 사용
무언가 써있는 프롬프트에 ctrl-D 사용

cat 이나 grep 실행 도중 ctrl-C 사용
cat 이나 grep 실행 도중 ctrl-\ 사용
cat 이나 grep 실행 도중 ctrl-D 사용
*/
void	