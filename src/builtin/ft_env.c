/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:30:54 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/04 17:21:09 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
t_info	*ft_env(char **envp)
{
	t_info	*env;
	int		i;

	init_list(env);
	i = 0;
	while (envp[i])
		insert_list(env, envp[i++]);
	return (env);
}
*/

t_envp	*init_envp(char *key, char *value)
{
	t_envp	*envp;

	envp = (t_envp *)malloc(sizeof(t_envp));
	envp->key = key; //safe_malloc이랑 ft_free 함수 어디있는지
	envp->value = value; //걍 칼록 쓰면 안되는지 물어보기 ㅋㅋ
	envp->next = NULL;
	return (envp);
}

void	insert_envp(t_envp *head, t_envp *new)
{
	t_envp	*tmp;

	if (!head || !new)
		return ;
	tmp = head;
	while (tmp->next != NULL) //마지막 노드 찾아서 뒤에 붙여주기
		tmp = tmp->next;
	tmp->next = new;
}

void	delete_envp(t_envp *head, t_envp *del)
{
	t_envp	*tmp;

	while (tmp->next != del) //del 전 노드 찾기
		tmp = tmp->next;
	//이제 tmp->next == del
	tmp->next = tmp->next->next;
	free(del->key);
	free(del->value);
	free(del);
}

void	delete_envp_all(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = (*envp)->next;
		free((*envp)->key);
		free((*envp)->value);
		free(*envp);
		*envp = tmp;
	}
}

t_envp	*set_envp(char **envp)
{
	t_envp	*head;
	t_envp	*new;
	char	**arr;
	int		i;

	i = 0;
	head = init_envp(NULL, NULL);
//	if (!head)
//		error();
	while (envp[i])
	{
		arr = ft_split(envp[i], '=');
//		if (!arr)
//			error();
		new = init_envp(arr[0], arr[1]);
//		if (!new)
//			error();
		insert_envp(head, new);
		free(arr);
		i++;
	}
	return (head);
}

int	ft_env(t_envp *head)
{
	t_envp	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	int i = 0;
// 	t_envp	*head;

// 	printf("////////////////////////\n");
// 	printf("original output\n");
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// 	printf("////////////////////////\n");
// 	printf("ft_env output\n");
// 	ft_env(envp);
// 	return 0;
// }
