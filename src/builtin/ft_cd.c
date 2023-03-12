/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/12 13:58:38 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	cd, cd ~ 일때
	-> HOME 경로 찾아서 path에 저장 후 이동

	cd $변수 일때
	-> 변수 경로 찾아서 path에 저장 후 이동

	cd ~ 234 (cd ~ 후 인자가 들어왔을 때)
	-> 에러메세지 없이 ~로 이동

	cd $HSIDHSIHD (없는 환경변수일때)

	-> 에러메세지 없이 ~로 이동
	
	#include <unistd.h>

	int	chdir(const char *dirname(path))
	-> dirname(path)로 경로를 변경함
	성공 시  0, 실패 시  -1
	char	*getcwd(char *buf, size_t size)
	-> buff에 현재 디렉토리 path 따옴
	
*/

static char	*set_home(t_envp *envp)
{
	int		i;
	char	*path;
	t_envp	*envp_tmp;

	envp_tmp = envp;
	i = 0;
	while (ft_strcmp("HOME", envp_tmp->key))
		envp_tmp = envp_tmp->next;
	path = ft_strdup(envp_tmp->value);
	return (path);
}

t_envp	set_oldpath(t_envp *envp)
{
	while (envp)
	{
		if (!ft_strncmp("OLDPWD", envp->key, 6))
		{
			envp->value = ft_strdup(getcwd(NULL, 0));
			break ;
		}
		envp = envp->next;
	}
}

void	ft_cd(t_info *arg, t_envp *envp)
{
	char	*path;
	char	*old_pwd;

	set_oldpath(envp);
	if (arg->next == NULL || ((arg->next)->cmd[0] == '~'
			&& (arg->next)->cmd[1] == '\0'))
		path = set_home(envp);
	else
		path = ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), (arg->next)->cmd);
	if (!chdir(path))
	{
		path = getcwd(NULL, 0);
		while (envp != NULL)
		{
			if (!ft_strncmp(envp->key, "PWD", 3))
			{
				free(envp->value);
				envp->value = ft_strdup(path);
				break ;
			}
			envp = envp->next;
		}
	}
	else
		common_errno("cd", 2, NULL);
}

// int	main()
// {
// 	t_envp *envp;
// 	char	*file_path;

// 	file_path = getcwd(NULL, 0);
// 	printf("현재 dir 경로 : %s\n", file_path);
// 	// while (envp != NULL)
// 	// {
// 	// 	printf("key : %s, value : %s", envp->key, tmp->value);
// 	// 	tmp = tmp->next;
// 	// }

// 	errno = ENOENT;
// 	printf("err : %s\n", strerror(1883));
// }