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
	HEREDOC_IN, // <<
	HEREDOC_OUT, // >> append
	REDIR_IN, // <
	REDIR_OUT, // >
	PIPE, // |
	WORD
}	t_type;

typedef struct s_info
{
	char			*cmd;
	int				type;
	struct s_info	*next;
}	t_info;

typedef struct s_dup
{
	void			*content;
	struct s_dup	*next;
}	t_dup;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

//제발 만들고 헤더에 추가좀 할사람
t_info		*init_list(void);
char		**set_path(t_envp *envp);
char		*get_cmd(char *cmd, t_envp *envp);
// void	here_doc(t_arg *arg); // 이전 과제 가져온거라 인자 바꿔야대여
int			is_whitespace(char *line);
void		insert_list(t_info *info, char *cmd, int tpye);
void		list_delete(t_info **info);
int			validate_quote_all(t_info *token);
void		str_tokenize(t_info *info, char *line);
int			is_dollar(char *token);
char		*parse_dollar(char *str, t_envp *head);
void		clear_quote_in_token(t_info *token);
void		quote_process(t_info *info, char **line);
void		ft_remainder(t_info *info, char **line);
char		*quote_bulk(char *line, char c);
int			is_whitespace2(char line);
char		*get_after_quote(char *line, char *bulk);

int	is_builtin(t_info *cmd);

/*signal*/
void		handler(int signum);
void		set_signal(t_signal mode);
void	heredoc_handler(int signum);

/*shell_utils*/
void		print_error(char *errmsg, int errnum);
int			ft_arrlen(char **arr);
int			ft_strchr_int(const char *s, char c);
char		*ft_strjoin_free(char *s1, char const *s2);

/*envp_utils*/
t_envp		*init_envp(void);
int			check_dupkey(t_envp *envp, char *key);
void		insert_envp(t_envp *envp, char *key, char *value);
void		append_envp(t_envp *envp, char *key, char *value);
void		delete_envp_all(t_envp **envp);
t_envp		*set_envp(char **envp);

/*export*/
// int			size_envp(t_envp *lst);
// void		sort_arr(char **arr);
int			check_argv(char *argv);
void		set_key_value(t_envp *head, char *argv, int i, int plus);
void		add_envp(char *argv, t_envp *head);

/*unset*/
int			validate_key(char *str);
int			check_edges_unset(t_info *arg, t_envp **envp);
void		free_envp(t_envp *envp);

/*builtin*/
int			builtin(t_info *cmd, t_envp *head, pid_t pid);
void		ft_pwd(void);
void		ft_env(t_info *cmd, t_envp *head);
void		ft_export(t_info *arg, t_envp *head);
void		ft_unset(t_info *arg, t_envp **envp);
void		ft_cd(t_info *arg, t_envp *envp);
void		ft_echo(t_info *arg);
void	ft_exit(t_info *arg);

/*pipex*/
void		pipex(t_info *token, t_envp *env);
int			get_pipe_count(t_info *token);
int			list_size(t_info *info);
t_info		*get_token(t_info **token, int fd);
void		here_doc(char *limiter, int origin_fd);
int	check_syntax(t_info *token);
/*dollar*/
void		find_dollar(t_info *token, t_envp *_env);
char		*parse_dollar(char *str, t_envp *head);

/*quotes*/
int			is_quote(char *s);
int			*count_q(char *munja);
int			here_quote(char *line);
char		*parse_dollar(char *str, t_envp *head);
char		*get_full_token(t_info *cmd);
void		clear_quote_in_token(t_info *token);
// void		delete_quote(t_info *token);
int			find_next_quote(char *line, char quote, int quote_idx);

/*err*/
void		exit_errno(int arg_status, char *cmd, int res);
void		envp_errno(char *err_value);
void		cd_errno(char *err_value);
void		common_errno(char *cmd, int res, char *next_arg);
void		syntax_errno(char *cmd);
void		badpath_errno(char *str, int res);

#endif
