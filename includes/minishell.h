/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:35:33 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 15:05:49 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <stdlib.h>
# include <termios.h>
# define PIPE 100
# define CMD 101
# define SIMCMD 102
# define RIDIR 103

typedef struct s_info
{
	char	**cmd;
	int		token;
	t_info	*left;
	t_info	*right;
}	t_info;

void	*insert_cmd(t_info *root, char **cmd, int token);
char	**set_envp(char **envp);
char	*get_cmd(char **path, char *cmd);
void	here_doc(t_arg *arg); // 이전 과제 가져온거라 인자 바꿔야대여

#endif