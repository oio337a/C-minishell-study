/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:35:33 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/04 17:57:18 by naki             ###   ########.fr       */
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

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

t_info	*init_list(void);
char	**set_path(char **envp);
char	*get_cmd(char **path, char *cmd);
// void	here_doc(t_arg *arg); // 이전 과제 가져온거라 인자 바꿔야대여
int		is_whitespace(char *line);
void	insert_list(t_info *info, char *cmd);
void	list_delete(t_info **info);
void	pipe_parser(char *line, t_info *info);
int		*count_q(char *munja);
char	*validate_readline(char *line, int *count);

/*signal*/
void	handler(int signum);

/*shell_utils*/
void	print_error(char *errmsg, int errnum);
int		ft_arrlen(char **arr);

/*envp_utils*/
t_envp	*init_envp(char *key, char *value);
void	insert_envp(t_envp *head, t_envp *new);
void	delete_envp(t_envp *head, t_envp *del);
void	delete_envp_all(t_envp **envp);
t_envp	*set_envp(char **envp);
t_envp	*dup_envp(t_envp *head);
t_envp	*sort_envp(t_envp *head);
void	add_envp(t_envp *head, char *argv);

/*builtin*/
int		ft_pwd(void);
int		ft_env(t_envp *head);
int		ft_export(t_envp *head, char *argv);

#endif
