/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/16 18:31:59 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

	첫번째 인자만 확인하고 동작하는걸로 ! ! 첫번째만 정상이면 그 뒤로 이상한거 붙어도 노상관

	1. PWD / OLDPWD 환경변수 업뎃 !
	2. 없는 디렉토리 인자로 넣었을 때 에러메시지
	3. unset HOME 후 cd ~ 시 에러메시지
	4. cd $env 시 해당 경로로 이동 -> 환경변수 파싱에서 끝나야 하는 거 아닌가? 마즘
	5. 
	
	cd ~ 일때 = 그냥 cd = cd $없는 환경변수 = cd ~ 인자
	-> HOME 경로 찾아서 path에 저장 후 이동

	cd $변수 일때 == cd 절대경로
	-> 변수 경로 찾아서 path에 저장 후 이동

	cd -
	-> OLDPWD로 이동

	cf. cd "" 시 아무 동작 x . . . ㅋㅋ
*/

static char	*set_home(t_envp *envp)
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
	cd_errno("HOME");
	return (NULL);
}

/*
	int	chdir(const char *dirname(path))
	-> dirname(path)로 경로를 변경함
	성공 시  0, 실패 시  -1
	char	*getcwd(char *buf, size_t size)
	-> buff에 현재 디렉토리 path 따옴
*/

void	ft_cd(t_info *arg, t_envp *envp)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;
	t_info	*tmp;
	t_envp	*head;

	tmp = arg;
	head = envp;
	old_pwd = getcwd(NULL, 0);
	if (tmp->next == NULL || ft_strcmp(tmp->next->cmd, "~") == 0) //인자 없거나 ~면
		path = set_home(envp);
	else //인자 있으면
		path = ft_strdup(tmp->next->cmd);
//ft_strjoin(ft_strjoin(pwd, "/"), tmp->next->cmd);
	if (!path)
		return ;
	if (chdir(path) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		insert_envp(envp, "PWD", new_pwd);
		insert_envp(envp, "OLDPWD", old_pwd);
		while (head != NULL)
		{
			if (ft_strcmp(head->key, "PWD") == 0)
			{
				free(head->value);
				head->value = new_pwd;
				break ;
			}
			head = head->next;
		}
		free(new_pwd);
		free(old_pwd);
	}
	else // 함수 종료 후 뉴라인 띄우기
		common_errno("cd", 2, NULL); //2는 머죠 ? ?
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