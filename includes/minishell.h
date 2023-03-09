/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:35:33 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/09 21:06:48 by suhwpark         ###   ########.fr       */
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
# define TRUE 1
# define FALSE 0

extern int	g_last_status;

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
char	**set_path(t_envp *envp);
char	*get_cmd(char *cmd, t_envp *envp);
// void	here_doc(t_arg *arg); // 이전 과제 가져온거라 인자 바꿔야대여
int		is_whitespace(char *line);
void	insert_list(t_info *info, char *cmd, int tpye);
void	list_delete(t_info **info);
void	pipe_parser(char *line, t_info *info);
// int		*count_q(char *munja);
char	*validate_readline(char *line, int *count);
void	str_tokenize(t_info *info, char *line);
int		is_dollar(char *token);
char	*parse_dollar(char *str, t_envp *head);
void	clear_qoute_in_token(t_info *token);
/*signal*/
void	handler(int signum);

/*shell_utils*/
void	print_error(char *errmsg, int errnum);
int		ft_arrlen(char **arr);
int		ft_strchr_int(const char *s, char c);

/*envp_utils*/
t_envp	*init_envp(void);
void	insert_envp(t_envp *envp, char *key, char *value);
void	append_envp(t_envp *envp, char *key, char *value);
int		size_envp(t_envp *lst);
void	delete_envp_all(t_envp **envp);
t_envp	*set_envp(char **envp);

/*export*/
char	**dup_envp(t_envp *head);
void	sort_arr(char **arr);
int		check_argv(char *argv);
void	add_envp(char *argv, t_envp *head);

/*unset*/
int 	validate_key(char *str);

/*builtin*/
int		ft_pwd(void);
int		ft_env(t_envp *head);
int		ft_export(t_info *arg, t_envp *head);
void	ft_unset(char *str, t_envp **envp);

/*quotes*/
char	*ft_strjoin_free(char *s1, char const *s2);
char	*parse_dollar(char *str, t_envp *head);
void	clear_qoute_in_token(t_info *token);
int		find_next_quotes(char *line, char quote, int quote_idx);

/*err*/
void	exit_errno(int arg_status, char *cmd, int res);
void	envp_errno(char *err_value, int res);
void	common_errno(char *cmd, int errno, char *next_arg);

#endif
