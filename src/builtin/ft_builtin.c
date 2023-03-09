/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:58:24 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/09 21:04:31 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin(t_info *cmd, t_envp *head)
{
	int	ret;

	if (ft_strcmp(cmd, "env") == 0) //실행 과정에서 명령어 유효성 체크해야되면. 이대론않되~
		ret = ft_env(head);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ret = ft_export(cmd, head);
	else if (ft_strcmp(cmd, "unset") == 0) //인자로 str
		ret = ft_unset(head);
	else if (ft_strcmp(cmd, "cd") == 0) //인자로 dir ! 
		ret = ft_cd(head);
	else if (ft_strcmp(cmd, "echo") == 0)
		ret = ft_echo(cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		ret = ft_exit(cmd);
	return (ret);
}
