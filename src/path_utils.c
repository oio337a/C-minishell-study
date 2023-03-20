/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:00:06 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 17:38:19 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_path(t_envp *envp)
{
	int		i;
	char	*path;
	t_envp	*envp_tmp;

	envp_tmp = envp;
	i = 0;
	while (ft_strncmp("PATH", envp_tmp->key, 4))
		envp_tmp = envp_tmp->next;
	path = envp_tmp->value;
	return (ft_split(path, ':'));
}

char	*get_cmd(char *cmd, t_envp *envp)
{
	int		i;
	char	*cmd_path;
	char	*tmp;
	char	**envp_in_list;

	if (!ft_strlen(cmd))
		common_errno(cmd, 127, NULL, STDOUT_FILENO);
	envp_in_list = set_path(envp);
	if (access(cmd, X_OK) != -1)
		return (cmd);
	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	while (envp_in_list[++i])
	{
		tmp = ft_strjoin(envp_in_list[i], cmd_path);
		if (access(tmp, X_OK) != -1)
		{
			free(cmd_path);
			return (tmp);
		}
		free(tmp);
	}
	common_errno(cmd, 127, NULL, STDOUT_FILENO);
	return (NULL);
}
