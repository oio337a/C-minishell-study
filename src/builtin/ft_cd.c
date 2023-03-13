/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 16:36:12 by yongmipa         ###   ########seoul.kr  */
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

// void	ft_cd(char **path)
// {
// 	if (path[0] == "" || path[0] == "~")
// 	{
		
// 	}
// 	else
// 	{
// 		/*
// 			// if path[0] 이 있을때
// 			// else path[0] 이 없을 때
// 				{
// 					if 환경 변수 일때 
// 					else 
// 						bash: cd: asdf: No such file or directory
// 				}
// 		*/
			
// 	}
// }

/*
	#include <unistd.h>

	int	chdir(const char *dirname(path))
	-> dirname(path)로 경로를 변경함
	성공 시  0, 실패 시  -1
	char	*getcwd(char *buf, size_t size)
	-> buff에 현재 디렉토리 path 따옴
*/

// char	*old_path(char **envp)
// {
// 	int	i;
	
// 	i = -1;
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp("PWD", envp[i], 3))
// 			return (envp[i] + 4); // PWD 뒤부터염
// 	}
// 	return (NULL);
// }

static char	*set_home(t_envp *envp) // string 들어가서 ':' 기준으로 split 합니다.
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

static int	check_cd(t_info *temp)
{
	return (((temp->next)->cmd[0] == '~'
			&& (temp->next)->cmd[1] == '\0'));
}

void	ft_cd(t_info *arg, t_envp *envp)
{
	char	*path;
	t_info	*temp;
	t_envp	*tmp;

	tmp = envp;
	temp = arg;
	if (temp->next == NULL || check_cd(temp))
		path = set_home(envp);
	else
		path = ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), (temp->next)->cmd);
	if (!chdir(path))
	{
		while (tmp != NULL)
		{
			if (!ft_strncmp(tmp->key, "PWD", 3))
			{
				free(tmp->value);
				tmp->value = ft_strdup(getcwd(NULL, 0));
				break ;
			}
			tmp = tmp->next;
		}
	}
	else // 함수 종료 후 뉴라인 띄우기
		common_errno("cd", 2, NULL);
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