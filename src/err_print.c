/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:06:57 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/18 21:57:15 by sohyupar         ###   ########.fr       */
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

static void	common_errnos(char *cmd, char *next_arg, int fd, int type)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	if (type != 3)
		ft_putstr_fd("Nakishell: ", fd);
	ft_putstr_fd(cmd, fd);
	if (type == 1)
		ft_putstr_fd(": command not found", fd);
	else if (type == 2)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(strerror(errno), fd);
	}
	else if (type == 3)
	{
		ft_putstr_fd(next_arg, fd);
		ft_putstr_fd(strerror(errno), fd);
	}
	ft_putstr_fd("\n", fd);
}

void	common_errno(char *cmd, int res, char *next_arg, int fd)
{
	if (res == 127) // 커맨드 한개 넣었는데 개소리
	{
		g_last_exit_code = 127;
		common_errnos(cmd, next_arg, fd, 1);
		// exit(g_last_exit_code);
		return ;
	}
	if (next_arg == NULL) // 앞에 커맨드는 맞는데 뒤에 개소리
	{
		common_errnos(cmd, next_arg, fd, 2);
		g_last_exit_code = 1;
		// exit(g_last_exit_code);
	}
	else // 걍 커맨드 여러개 갈겨서 다 개소리
	{
		// printf("%s: %s: %s\n", cmd, next_arg, strerror(errno));
		common_errnos(cmd, next_arg, fd, 3);
		g_last_exit_code = 1;
		// exit(g_last_exit_code);
	}
}

void	envp_errno(char *err_value, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd("Nakishell$: export: ", fd);
	ft_putstr_fd(err_value, fd);
	ft_putstr_fd(": not a valid identifier\n", fd);
	g_last_exit_code = 1;
	// exit(g_last_exit_code);
}

void	cd_errno(char *err_value, int fd) // file or
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd("Nakishell$: cd: ", fd);
	ft_putstr_fd(err_value, fd);
	ft_putstr_fd(": No such directory\n", fd);
	g_last_exit_code = 1;
}

void	exit_errno(int arg_status, char *cmd, int res, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	if (arg_status != 0)
	{
		ft_putstr_fd("Nakishell$: ", fd);
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": too many arguments\n", fd);
		g_last_exit_code = 1;
		// exit(g_last_exit_code);
	}
	else
	{
		ft_putstr_fd("Nakishell$: exit: ", fd);
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": numeric argument required\n", fd);
		g_last_exit_code = 255;
		// exit(g_last_exit_code);
	}
}

void	syntax_errno(char *cmd, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd("syntax error near unexpected token '", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd("'\n", fd);
	g_last_exit_code = 258;
	// exit(g_last_exit_code);
}

void	badpath_errno(char *str, int res, int fd)
{
	ft_putstr_fd(ERROR_COLOR, STDIN_FILENO);
	ft_putstr_fd(strerror(res), fd);
	ft_putstr_fd("\n", fd);
	// exit(g_last_exit_code);
}
