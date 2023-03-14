/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:00:43 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/14 13:38:57 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	"$ENVPNAME" -> $ENVPNAME 변수 내부 value를 출력
	없으면 걍 빈줄
	'$~` -> 걍 문자열 취급
*/

static int	check_envp(char *token)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (token[k])
	{
		if (token[k] == '\'')
			return (0);
		k++;
	}
	while (token[i])
	{
		if (token[i] == '$')
			return (1);
		if (token[i] == '\"')
		{
			j = i + 1;
			while (token[j] && token[j] != '\"')
			{
				if (token[j] == '$')
					return (1);
				j++;
			}
			i = j - 1;
		}
		i++;
	}
	return (0);
}

static int	quote_quote(char *token)
{
	int	i;
	int	next;

	i = 0;
	next = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			next = find_next_quotes(token, '\'', i);
			if (next == -1)
				return (0);
			i = next;
		}
		if (token[i] == '\"')
		{
			next = find_next_quotes(token, '\"', i);
			if (next == -1)
				return (0);
			i = next;
		}
		i++;
	}
	return (1);
}

int	validate_quote_line(t_info *token)
{
	t_info	*head;

	head = token;
	while (head)
	{
		if (!quote_quote(head->cmd))
		{
			printf("error\n");
			return (0);
		}
		head = head->next;
	}
	return (1);
}

void	find_dollar(t_info *token, t_envp *_env)
{
	t_info	*head;
	char	*tmp;

	head = token;
	while (head)
	{
		if (check_envp(head->cmd))
		{
			tmp = head->cmd;
			head->cmd = parse_dollar(head->cmd, _env);
			free(tmp);
		}
		head = head->next;
	}
}

// int main(int ac, char **av, char **envp)
// {
// 	t_info *test;
// 	t_info *head1;
// 	t_info *head2;
// 	t_envp	*env;
// 	char *str = "cat \"\"\"$USER\"\"\" | ls -al | cat '-e' | 'w'c -l > a";

// 	// printf("line : %s\n", str);
// 	test = init_list();
// 	str_tokenize(test, str);
// 	head1 = test;
// 	env = set_envp(envp);
// 	//쿼터 짝 맞는지 확인
// 	while(head1 != NULL)
// 	{
// 		printf("cmd : %s, type : %d\n", head1->cmd, head1->type);
// 		head1 = head1->next;
// 	}
// 	if (validate_quote_line(test))
// 	{
// 		find_dollar(test, env);
// 		clear_quote_in_token(test);
// 	}
// 	head2 = test;
// 	while (head2 != NULL)
// 	{
// 		printf("a-fter cmd : %s, type : %d\n", head2->cmd, head2->type);
// 		head2 = head2->next;
// 	}
	// system("leaks a.out");
// }
