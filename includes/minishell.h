/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:59:07 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 20:50:21 by yongmipa         ###   ########seoul.kr  */
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
# include <sys/wait.h>
# define TRUE 1
# define FALSE 0
# define PROMPT_COLOR "\033[38:5:111m"
# define COMMAND_COLOR "\033[0m"
# define WELCOME_COLOR "\033[38:5:225m"
# define ERROR_COLOR "\033[38:5:196m"

extern int	g_last_exit_code;

typedef enum e_signal
{
	GENERAL,
	CHILD,
	WAITING,
	HEREDOC
}	t_signal;

typedef enum e_type
{
	HEREDOC_IN,
	HEREDOC_OUT,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	WORD
}	t_type;

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

/*main.c*/
void		execute(char *str, t_info *info, t_envp *envp_head);

/*tokenize.c*/
char		*quote_bulk(char *line, char c);
char		*get_after_quote(char *line, char *bulk);
void		str_tokenize(t_info *info, char *line);
int			reminder_in_quote(char quote, int i, char *line);

/*find_dollar.c*/
void		find_dollar(t_info *token, t_envp *_env);
int			check_quote_couple(char *token);

/*dollar.c*/
int			is_dollar(char *token);
char		*parse_dollar(char *str, t_envp *head);

/*delete_quote.c*/
void		clear_quote_in_token(t_info *token);

/*delete_quote_util.c*/
int			find_next_quote(char *line, char quote, int quote_idx);
int			*count_q(char *munja);
int			here_quote(char *line);
char		*get_full_token(t_info *cmd);
int			is_quote(char *s);

/*tokenize_utils.c*/
int			is_whitespace(char line);
int			modu_spacebar_ya(char *line);
void		quote_process(t_info *info, char **line);
void		ft_remainder(t_info *info, char **line);
void		move_heredoc(t_info **token, int pipe);
void		move_list(t_info **token);
int			list_count_heredoc(t_info *token);
int			get_heredoc_pipe(t_info *token, int cnt);
void		execve_token(t_info *token, t_envp *env, pid_t pid, int fd);

/*token_access.c*/
t_info		*get_token(t_info **token, t_envp *envp, int fd);
void		pipex(t_info *token, t_envp *env);
void		type_redir_in(t_info **token, int fd);
void		type_redir_out(t_info **token, int fd);
void		type_heredoc_in(t_info **token, int fd, t_envp *envp);
void		type_heredoc_out(t_info **token, int fd);

/*heredoc.c*/
void		here_doc(char *limiter, t_envp *envp, int origin_fd);

/*path_utils.c*/
char		**set_path(t_envp *envp);
char		*get_cmd(char *cmd, t_envp *envp);

/*syntax.c*/
void		syntax_errno(char *cmd, int fd);
int			check_syntax(t_info *token);
int			get_pipe_count(t_info *token);
int			validate_quote_all(t_info *token);

/*shell_utils*/
void		print_error(char *errmsg, int errnum);
int			ft_arrlen(char **arr);
int			ft_strchr_int(const char *s, char c);
char		*ft_strjoin_free(char *s1, char const *s2);

/*list_utils.c*/
t_info		*init_list(void);
void		insert_list(t_info *info, char *cmd, int tpye);
void		list_delete(t_info **info);
int			list_size(t_info *info);

/*init_envp.c*/
t_envp		*init_envp(void);
int			check_dupkey(t_envp *envp, char *key);
void		insert_envp(t_envp *envp, char *key, char *value);
void		append_envp(t_envp *envp, char *key, char *value);
t_envp		*set_envp(char **envp);

/*envp_utils.c*/
int			size_envp(t_envp *lst);
void		delete_envp_all(t_envp **envp);
char		**envp_to_arr(t_envp *head);
char		**dup_envp(t_envp *head);

/*builtin*/
int			is_builtin(t_info *cmd);
int			builtin(t_info *cmd, t_envp *head, pid_t pid);
void		ft_pwd(void);
void		ft_env(t_info *cmd, t_envp *head);
void		ft_export(t_info *arg, t_envp *head);
void		ft_unset(t_info *arg, t_envp **envp);
int			validate_key(char *str);
void		ft_cd(t_info *arg, t_envp *envp);
void		ft_echo(t_info *arg);
void		ft_exit(t_info *arg);

/*signal*/
void		handler(int signum);
void		set_signal(t_signal mode);
void		wait_handler(int signum);

/*err_print.c*/
void		common_errno(char *cmd, int res, char *next_arg, int fd);
int			envp_errno(char *err_value, int fd);
void		cd_errno(char *err_value, int fd);
void		exit_errno(int arg_status, char *cmd, int fd);

#endif
