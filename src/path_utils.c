/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:50 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/09 21:04:58 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	is_whitespace(char *line) // 빈 프롬프트만 들어왔는지 검수.
// {
// 	while (*line)
// 	{
// 		if (*line != 32 && !(*line >= 9 && *line <= 13))
// 			return (0);
// 		line++;
// 	}
// 	return (1);
// }

char	**set_path(t_envp *envp) // string 들어가서 ':' 기준으로 split 합니다.
{
	int		i;
	char	*path;
	t_envp	*envp_tmp;

	envp_tmp = envp;
	i = 0;
	while (!ft_strcmp("PATH", envp_tmp->key))
		envp_tmp = envp_tmp->next;
	path = envp_tmp->value;
	return (ft_split(path, ':'));
}

char	*get_cmd(char *cmd, t_envp *envp)
// ls, echo 형식으로 들어온 cmd가 실행 가능하다면 execve의 path_cmd 형식 (/bin/ls)로 변환
{
	int		i;
	char	*cmd_path;
	char	*tmp;
	char	**envp_in_list;

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
	common_errno(cmd, 127, NULL); // command not found 출력 후, 상태를 127로 저장합니다.
	return (NULL);
}
