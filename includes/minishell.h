/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:35:33 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/08 21:06:05 by yongmipa         ###   ########seoul.kr  */
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

typedef enum s_type
{
	REDIR,
	PIPE,
	WORD
} 	t_type;

typedef struct s_info
{
	char			*cmd;
	int				type;
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
void	insert_list(t_info *info, char *cmd, int tpye);
void	list_delete(t_info **info);
void	pipe_parser(char *line, t_info *info);
// int		*count_q(char *munja);
char	*validate_readline(char *line, int *count);
void	str_tokenize(t_info *info, char *line);
int		is_dollar(char *token);
/*signal*/
void	handler(int signum);

/*shell_utils*/
void	print_error(char *errmsg, int errnum);
int		ft_arrlen(char **arr);
int	ft_strchr_int(const char *s, char c);

/*envp_utils*/
t_envp	*init_envp(void);
void	insert_envp(t_envp *envp, char *key, char *value);
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

/*quotes*/
char	*ft_strjoin_free(char *s1, char const *s2);
char	*parse_dollar(char *dollar, t_envp *envp);
void	clear_qoute_in_token(t_info *token);

/*err*/
void	errno_print(char *cmd, int errnum, char *string);
void	errno_numeric(char *cmd, char *string);
void	errno_toomany(char *cmd);

#endif
