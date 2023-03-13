/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:06:57 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/13 19:47:59 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	errno_print(char *cmd, int errnum, char *string)
// {
// 	errno = errnum;
// 	if (cmd != NULL && string != NULL && errno != 0)
// 		printf("%s: %s: %s", cmd, string, strerror(errno));
// 	if (cmd != NULL && char == NULL)
// 		printf("%s: %s", cmd, strerror(errno));
// }
// errno 대충 
/*
	0	: It indicates successful execution.	
	1	: It is used to catch all general errors.	“Divide by zero”, “Operation not permitted” etc. can be the error messages of this code.
	2	: It indicates the abuse of shell built-ins.	“Missing keyword”, “No such file or directory” etc. can be the error messages of this code.
	126	: It generates when the any command is unable to execute.	Permission problem or required key not available can generate this status code
	127	: It normally generates for the command path problem.	“Command not found” can be the message for this error code.
	130	: It generates for fatal error.	“Script terminated by Ctrl+C” can be the message of this code.
	255*	It indicates exit code out of range.$

	에러 출력 순서?

	일반적으로는
	1. 인자가 하나다
		bash: cmd: command not found
	// 2. 인자가 두개다
	// 	처음은 맞는 cmd고, 옵션에서 터졌다
	// 	ls: illegal option -- j
	// 	usage: ls [-@ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1%] [file ...]

	-------------------------------------------------------
exit은 예외 인자가 3개일 때

	첫번 째에서 터졌다
		bash: exit: cmd1: numeric arg ~ (인자가 두개일 때도 동일하다.)
	두번 째에서 터졌다
		bash: exit: too many arg
	

환경변수
	value만 들어왔다
		export TEST =2244
			bash: export: `=value`: errmsg(not a valid idnetifier)

*/

// int	errno_print(char *str, int errnum, char *option)
// {

// 	return (errnum);
// }
int	g_last_exit_code;

// 추후에 errno를 사용하지 않는 케이스는 테스트 후 perror로 바꾸겠읍니다
// 우리 쉘에서 될지 안될지 몰라서 일단 printf..
// +) 여기서 뉴라인 띄우도록 기능 추가 필요
void	common_errno(char *cmd, int res, char *next_arg)
{
	printf("here?\n");
	if (res == 127) // command not found  errno에 등록 안돼있어여
	{
		printf("%s: command not found\n", cmd);
		g_last_exit_code = 127;
	}
	if (next_arg == NULL)
	{
		printf("%s: %s\n", cmd, strerror(res)); // No such~ errno == 2
		g_last_exit_code = 1;
	}
	else
	{
		printf("%s: %s: %s\n", cmd, next_arg, strerror(errno));
		g_last_exit_code = 1;
	}
	// return (1); // 앞에는 실행 가능하다는 cmd 전제
}

void	envp_errno(char *err_value, int res)
{
	printf("export: %s: not a valid identifier\n", err_value);
	g_last_exit_code = 1;
}

void	exit_errno(int arg_status, char *cmd, int res)
{
	if (arg_status != 0)
	{
		printf("Nakishell$: %s: too many arguments\n", cmd);
		g_last_exit_code = 1;
	}
	else
	{
		printf("Nakishell$: exit: %s: numeric argument required\n", cmd);
		g_last_exit_code = 255;
	}
}

void	syntax_errno(char *cmd)
{
	printf("syntax error near unexpected token `%s'\n", cmd);
	g_last_exit_code = 258;
}

void badpath_errno(char *str, int res)
{
	printf("%s\n", strerror(res));
}
