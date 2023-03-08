/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:32 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/08 22:24:08 by yongmipa         ###   ########seoul.kr  */
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
static int validate_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	i++;
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char *str, t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*before;
	t_envp	*curr;

	tmp = envp;
	if (!validate_key(str))
	{
		printf("Nakishell: unset '%s': not a valid identifier", str);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (!ft_strncmp(str, tmp->next->key, ft_strlen(str)) && (ft_strlen(str) == ft_strlen(tmp->next->key)))
		{
			before = tmp;
			curr = tmp->next;
			before->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
		}
		else
			tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp) //test 메인문
{
	t_envp	*head;
	t_envp	*tmp;
	t_envp *tmp2;
	int i = 0;
	int j = 0;
	char	*str = "abc";

	head = set_envp(envp);
	tmp = head;
	// tmp2 = head;
	// while (tmp2)
	// {
	// 	j++;// printf("%s=%s\n", tmp2->key, tmp2->value);
	// 	tmp2 = tmp2->next;
	// }
	ft_unset(str, tmp);
	// while (tmp)
	// {
	// 	printf("%s=%s\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }
	// system("leaks a.out");
	// ft_env(head);
	return (0);
	// 저희 exit done ~!@~!@ 뿡
}
