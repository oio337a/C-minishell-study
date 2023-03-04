#include "../../includes/minishell.h"

int	builtin(char *cmd, t_envp *head, char *op, char *argv)
{
	int	ret;

	if (ft_strncmp(cmd, "env", 3) == 0) //실행 과정에서 명령어 유효성 체크해야되면. 이대론않되~
		ret = ft_env(head);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		ret = ft_pwd();
	else if (ft_strncmp(cmd, "export", 6) == 0)
		ret = ft_export(head, argv);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		ret = ft_unset(head, argv);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ret = ft_cd(head, argv);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		ret = ft_echo(op, argv);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		ret = ft_exit(op, argv);
	return (ret);
}
