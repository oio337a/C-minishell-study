/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:58:24 by yongmipa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/10 22:37:31 by yongmipa         ###   ########seoul.kr  */
=======
/*   Updated: 2023/03/12 11:16:20 by naki             ###   ########.fr       */
>>>>>>> d99338a6d7d05c94f9cfd9fece4e458504baf720
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin(t_info *cmd, t_envp *head)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->cmd, "env") == 0)
		ret = ft_env(head);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ret = ft_export(cmd, head);
	else if (ft_strcmp(cmd->cmd, "unset") == 0) //인자로 str
		ft_unset(cmd->next->cmd, &head);
	else if (ft_strcmp(cmd->cmd, "cd") == 0) //인자로 dir !
		ft_cd(cmd, head);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ret = ft_exit(cmd);
	return (ret);
}
/*화긴된거 (인자 하나만 썻음)
	pwd
	exit 
	echo(환경변수 추가 처리 필요)
<<<<<<< HEAD
	cd
	env
*/
=======
*/
>>>>>>> d99338a6d7d05c94f9cfd9fece4e458504baf720
