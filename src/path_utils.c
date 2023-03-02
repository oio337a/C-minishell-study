/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:50 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 18:14:48 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

char	**set_envp(char **envp) // 환경변수를 ':' 기준으로 잘라서 path로 생성합니다.
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	path = envp[i] + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd(char **path, char *cmd) // ls, echo 형식으로 들어온 cmd가 실행 가능하다면 execve의 path_cmd 형식 (/bin/ls)로 변환
{
	int		i;
	int		fd;
	char	*cmd_path;
	char	*tmp;

	i = -1;
	fd = access(cmd, X_OK);
	if (fd != -1)
		return (cmd);
	cmd_path = ft_strjoin("/", cmd);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd_path);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(cmd_path);
			return (tmp);
		}
		close(fd);
		free(tmp);
	}
	free(cmd_path);
	return (NULL);
}
