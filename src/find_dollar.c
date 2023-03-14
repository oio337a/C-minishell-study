/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:00:43 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/14 21:52:34 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	"$ENVPNAME" -> $ENVPNAME 변수 내부 value를 출력
	없으면 걍 빈줄
	'$~` -> 걍 문자열 취급
*/

static int	is_single_quote(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

static int	check_else(char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

static int	check_envp(char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!is_single_quote(token))
		return (0);
	if (check_else(token) == 1)
		return (1);
	return (0);
}

static int	check_quote_couple(char *token) // quote_quote -> find_quote_couple
{ //쿼터 발견 시 다음 쿼터 찾으면서 짝 맞는지 확인
	int	i;
	int	next;

	i = 0;
	next = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			next = find_next_quote(token, '\'', i);
			if (next == -1)
				return (0);
			i = next;
		}
		if (token[i] == '\"')
		{
			next = find_next_quote(token, '\"', i);
			if (next == -1)
				return (0);
			i = next;
		}
		i++;
	}
	return (1);
}

int	validate_quote_all(t_info *token) // validate_quote_line -> validate_quote_all
{ // 전체 명령어 토큰 돌면서 쿼터 짝 맞는지 확인
	t_info	*head;

	head = token;
	while (head)
	{
		if (!check_quote_couple(head->cmd))
			return (0);
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
// 	if (validate_quote_all(test))
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