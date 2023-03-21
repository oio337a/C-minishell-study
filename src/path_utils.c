/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:00:06 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/21 22:03:44 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_code;

char	**set_path(char *cmd, t_envp *envp)
{
	char	*path;

	path = find_envp(envp, "PATH");
	if (!path)
	{
		common_errno(cmd, 2, NULL, STDOUT_FILENO);
		return (NULL);
	}
	return (ft_split(path, ':'));
}

static char	*is_folder(char *cmd, char **path)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		if (!ft_strncmp(cmd, path[i], ft_strlen(cmd)))
			return (NULL);
	}
	return (cmd);
}

static void	setting_cmd(char *cmd, char **envp_in_list)
{
	if (!is_folder(cmd, envp_in_list))
	{
		common_errno(cmd, 21, NULL, STDOUT_FILENO);
		g_last_exit_code = 126;
		return ;
	}
}

static char	*return_cmd(char **envp, char *cmd_path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		tmp = ft_strjoin(envp[i], cmd_path);
		if (access(tmp, X_OK) != -1)
		{
			free(cmd_path);
			return (tmp);
		}
		free(tmp);
	}
	return (NULL);
}

char	*get_cmd(char *cmd, t_envp *envp)
{
	char	*cmd_path;
	char	*tmp;
	char	**envp_in_list;

	if (!ft_strlen(cmd))
		common_errno(cmd, 127, NULL, STDOUT_FILENO);
	envp_in_list = set_path(cmd, envp);
	setting_cmd(cmd, envp_in_list);
	if (access(cmd, X_OK) != -1)
		return (cmd);
	else if (!ft_strncmp("/", cmd, 1))
	{
		common_errno(cmd, 2, NULL, STDOUT_FILENO);
		g_last_exit_code = 127;
		return (NULL);
	}
	cmd_path = ft_strjoin("/", cmd);
	tmp = return_cmd(envp_in_list, cmd_path);
	if (!tmp)
	{
		common_errno(cmd, 127, NULL, STDOUT_FILENO);
		return (NULL);
	}
	return (tmp);
}
