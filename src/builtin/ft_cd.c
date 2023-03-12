/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/12 13:52:07 by sohyupar         ###   ########.fr       */
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
*/

/*
	#include <unistd.h>

	int	chdir(const char *dirname(path))
	-> dirname(path)로 경로를 변경함
	성공 시  0, 실패 시  -1
	char	*getcwd(char *buf, size_t size)
	-> buff에 현재 디렉토리 path 따옴
	
*/

char	*old_path(t_envp *envp)
{
	int	i;

	i = -1;
	while (envp)
	{
		if (ft_strncmp("PWD", envp->key, 3))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

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

void	ft_cd(t_info *arg, t_envp *envp)
{
	char	*path;
	char	*old_pwd;
	t_info	*temp;
	t_envp	*tmp;

	tmp = envp;
	temp = arg;
	while (envp)
	{
		if (!ft_strncmp("OLDPWD", envp->key, 6))
		{
			envp->value = ft_strdup(getcwd(NULL, 0));
			break ;
		}
		envp = envp->next;
	}
	if (temp->next == NULL || ((temp->next)->cmd[0] == '~'
			&& (temp->next)->cmd[1] == '\0'))
		path = set_home(envp);
	else
		path = ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), (temp->next)->cmd);
	if (!chdir(path))
	{
		path = getcwd(NULL, 0);
		while (tmp != NULL)
		{
			if (!ft_strncmp(tmp->key, "PWD", 3))
			{
				free(tmp->value);
				tmp->value = ft_strdup(path);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else // 함수 종료 후 뉴라인 띄우기
	{
		printf("from else...\n");
		common_errno("cd", 2, NULL);
		// badpath_errno("cd", 2);
	}
}

// int	main()
// {
// 	t_envp *tmp;
// 	char	*file_path;

// 	file_path = getcwd(NULL, 0);
// 	printf("현재 dir 경로 : %s\n", file_path);
// 	// while (tmp != NULL)
// 	// {
// 	// 	printf("key : %s, value : %s", tmp->key, tmp->value);
// 	// 	tmp = tmp->next;
// 	// }

// 	errno = ENOENT;
// 	printf("err : %s\n", strerror(1883));
// }