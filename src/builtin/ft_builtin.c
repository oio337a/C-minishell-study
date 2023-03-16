/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:01:16 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/16 18:00:09 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
unset 존재하는 일반 환경변수 -> 그 환경변수만 envp, export에서 제거

unset PATH -> envp 위치 없어져서 env 명령어 터짐, 
나머지 export는 존재
이후 PATH를 사용하는 모든 명령어들 사용(export도) 불가능함
*/

int	g_last_exit_code;
//새로운거
int	is_builtin(t_info *cmd)
{
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd, "cd") == 0) //인자로 dir !
		return (1);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (1);
	else //위의 경우에서 전부 해당 안되면, 0 리턴
		return (0);
}
// 이거 필요함
int	builtin(t_info *cmd, t_envp *head, pid_t pid) // 전체 cmd 모두 들어옴
{
	if (cmd->cmd[0] == '\0')
		return (0);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(cmd, head);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd, head);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd, &head);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd, head);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd);
	else
		return (0);
	if (pid == 0)
		exit(g_last_exit_code); //builtin 해당 시 실행 후 자식 프로세스 종료
	return (0);
}
