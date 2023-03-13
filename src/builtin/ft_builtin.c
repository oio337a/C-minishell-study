/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:01:16 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 22:21:27 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
unset 존재하는 일반 환경변수 -> 그 환경변수만 envp, export에서 제거

unset PATH -> envp 위치 없어져서 env 명령어 터짐, 
나머지 export는 존재
이후 PATH를 사용하는 모든 명령어들 사용(export도) 불가능함
*/

int	builtin(t_info *cmd, t_envp *head) // 전체 cmd 모두 들어옴 -> 빌트인 실행하면 1, 아니면 0 리턴
{
	if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(cmd, head);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd, head);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd, &head);
	else if (ft_strcmp(cmd->cmd, "cd") == 0) //인자로 dir !
		ft_cd(cmd, head);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd);
	else //위의 경우에서 전부 해당 안되면, 0 리턴
		return (0);
	return (1); //if나 else if에서 안 끝날 시 1리턴
}
