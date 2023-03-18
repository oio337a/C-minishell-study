/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:32 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/19 01:12:02 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	# 예시
	-------------------------------
	[root@wiki ~] str="hello world"
	[root@wiki ~] echo $str
	hello world
	[root@wiki ~] unset str
	[root@wiki ~] echo $str
	-------------------------------
	인자로 들어온 환경변수가 유효한지 검사
	문자/_로 시작해야함 (숫자로 시작할 수 없다)
	이미 존재하는 환경변수인지 검사
	파이프 뒤에 있다면 자식프로세스의 unset이기 때문에 환경변수 삭제 X <- 먼말임 ?
*/

int	validate_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

void	free_envp(t_envp *envp)
{
	free(envp->key);
	free(envp->value);
	free(envp);
}

static void	delete_envp(t_info *arg_tmp, t_envp **envp)
{
	t_envp	*tmp;
	t_envp	*before;
	t_envp	*curr;

	tmp = *envp;
	if (!ft_strcmp(arg_tmp->cmd, tmp->key))
	{
		*envp = (*envp)->next;
		free_envp(tmp);
	}
	while (tmp->next != NULL)
	{
		if (!ft_strcmp(arg_tmp->cmd, tmp->next->key))
		{
			before = tmp;
			curr = tmp->next;
			before->next = curr->next;
			free_envp(curr);
		}
		else
			tmp = tmp->next;
	}
}

void	ft_unset(t_info *arg, t_envp **envp)
{
	t_info	*arg_tmp;

	if (!arg->next || !envp)
		return ;
	arg_tmp = arg->next;
	while (arg_tmp)
	{
		if (!validate_key(arg_tmp->cmd))
		{
			// envp_errno(arg_tmp->cmd);
			arg_tmp = arg_tmp->next;
			continue ;
		}
		delete_envp(arg_tmp, envp);
		arg_tmp = arg_tmp->next;
	}
	g_last_exit_code = 0;
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_envp	*head = set_envp(envp);
// 	t_info	*arg = init_list();
// 	t_info	*arg2 = init_list();
// 	t_info	*arg3 = init_list();

// 	insert_list(arg, "export", WORD);
// 	insert_list(arg, "xxx=123", WORD);
// 	insert_list(arg, "a====b", WORD);
// 	insert_list(arg, "123a=123", WORD);
// 	insert_list(arg, "xxx=456", WORD);
// 	insert_list(arg, "ooo+=456", WORD);
// 	ft_export(arg, head);

// 	insert_list(arg3, "export", WORD);

// 	printf("before unset\n");
// 	ft_export(arg3, head);

// 	insert_list(arg2, "unset", WORD);
// 	insert_list(arg2, "SECURITYSESSIONID", WORD);
// 	insert_list(arg2, "a", WORD);
// 	insert_list(arg2, "b=a", WORD);
// 	ft_unset(arg2, &head);

// 	printf("after unset\n");
// 	ft_export(arg3, head);
// 	return (0);
// }
