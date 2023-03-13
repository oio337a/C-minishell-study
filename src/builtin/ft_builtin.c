/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:01:16 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 19:08:37 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin(t_info *cmd, t_envp *head) // 전체 cmd 모두 들어옴 -> 빌트인 실행하면 1, 아니면 0 리턴
{
	if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(head);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		/*ret =*/ ft_export(cmd, head);
	// else if (ft_strcmp(cmd->cmd, "unset") == 0) //인자로 str
	// 	ft_unset(cmd, &head);
	else if (ft_strcmp(cmd->cmd, "cd") == 0) //인자로 dir ! 
		ft_cd(cmd, head);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		/*ret =*/ ft_exit(cmd);
	else //위의 경우에서 전부 해당 안되면, 0 리턴
		return (0);
	return (1); //if나 else if에서 안 끝날 시 1리턴
}
