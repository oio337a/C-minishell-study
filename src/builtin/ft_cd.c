/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 18:28:29 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_home(t_envp *envp)
{
	int		i;
	char	*path;
	t_envp	*envp_tmp;

	envp_tmp = envp;
	i = 0;
	while (envp_tmp)
	{
		if (ft_strcmp("HOME", envp_tmp->key) == 0)
		{
			path = ft_strdup(envp_tmp->value);
			return (path);
		}
		envp_tmp = envp_tmp->next;
	}
	return (NULL);
}

static char	*get_oldpwd(t_envp *envp)
{
	int		i;
	char	*path;
	t_envp	*envp_tmp;

	envp_tmp = envp;
	i = 0;
	while (envp_tmp)
	{
		if (ft_strcmp("OLDPWD", envp_tmp->key) == 0)
		{
			path = ft_strdup(envp_tmp->value);
			return (path);
		}
		envp_tmp = envp_tmp->next;
	}
	ft_putstr_fd("Nakishell$: cd: OLDPWD not set\n", STDOUT_FILENO);
	g_last_exit_code = 1;
	return (NULL);
}

static void	set_newpwd(t_envp *envp, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	insert_envp(envp, "PWD", new_pwd);
	insert_envp(envp, "OLDPWD", old_pwd);
	free(new_pwd);
	g_last_exit_code = 0;
}

void	ft_cd(t_info *arg, t_envp *envp)
{
	char	*path;
	char	*old_pwd;
	t_info	*tmp;

	tmp = arg;
	old_pwd = getcwd(NULL, 0);
	if (tmp->next == NULL || ft_strcmp(tmp->next->cmd, "~") == 0 || \
	ft_strcmp(tmp->next->cmd, "") == 0)
		path = get_home(envp);
	else if (ft_strcmp(tmp->next->cmd, "-") == 0)
		path = get_oldpwd(envp);
	else
		path = ft_strdup(tmp->next->cmd);
	if (!path)
		return ;
	if (chdir(path) == 0)
		set_newpwd(envp, old_pwd);
	else
		cd_errno(path, STDOUT_FILENO);
	free(old_pwd);
	free(path);
}
