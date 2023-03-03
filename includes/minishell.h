/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:35:33 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 18:34:11 by yongmipa         ###   ########seoul.kr  */
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
# include <signal.h>
# include <errno.h>
# include <string.h>
# define DLIMITER -77

typedef struct s_info
{
	char			*cmd;
	struct s_info	*next;
}	t_info;

t_info	*init_list(void);
char	**set_envp(char **envp);
char	*get_cmd(char **path, char *cmd);
// void	here_doc(t_arg *arg); // 이전 과제 가져온거라 인자 바꿔야대여
int		is_whitespace(char *line);
void	insert_list(t_info *info, char *cmd);
void	list_delete(t_info **info);
t_info	*ft_env(char **envp);
void	handler(int signum);
void	pipe_parser(char *line, t_info *info);
int		*count_q(char *munja);
char	*validate_readline(char *line, int *count);

#endif