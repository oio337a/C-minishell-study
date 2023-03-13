/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 22:31:14 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dollar(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' || token[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

static char	*find_value(char *dollar, t_envp *envp, int *idx) //find_key랑 합침
{
	t_envp	*head;
	char	*key;
	int		i;

	i = 1; //1. key 찾기. key 이름은 알파벳 + 숫자 + 언더바만 고려.
	while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
		i++;
	key = ft_substr(dollar, 1, i - 1); //2. key에 duplicate . .
	*idx += (ft_strlen(key) + 1); //int 포인터를 받아 값을 변경..
	free(key);
	head = envp;
	while (head != NULL) //3. 환경변수 리스트 돌면서 key값 일치하는 것 있는지 찾음
	{
		if (!ft_strcmp(key, head->key)) // 있는 환경변수면 replace
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (ft_strdup("")); // 없는 환경변수면 안 나옴
}

static int	check_edges(char next, char **str, int *i)
{
	char	*pid;

	if (ft_isdigit(next))
		*i += 2;
	else if (next == '$')
	{
		pid = ft_itoa(getpid());
		*str = ft_strjoin_free(*str, pid);
		*i += 2;
		free(pid);
	}
	else if ((!ft_isalnum(next) && next != '_') || next == '\0')
	{
		*str = ft_strjoin_free(*str, "$");
		*i += 1;
	}
	else
		return (0);
	return (1);
}

// char	*set_sub(char *str)
// {
// 	char	*sub;

// sub = ft_substr((str), 0, is_dollar(str));
// ret = 
// }

char	*parse_dollar(char *str, t_envp *head)
{
	char	*ret;
	char	*value;
	char	*sub;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (check_edges(str[i + 1], &ret, &i))
				continue ;
			value = find_value((str + i), head, &i); // 어차피 find_value함수 내에서 tmp선언하기 때문에 head 직접 대입
			ret = ft_strjoin_free(ret, value);
			free(value);
			return (ret);
		}
		else
		{
			//set_sub(str + i);
			sub = ft_substr((str + i), 0, is_dollar(str + i));
			ret = ft_strjoin_free(ret, sub);
			i += is_dollar(str + i);
			free(sub);
		}
	}
	return (ret);
}

/*
	1. str[i] == $
		$뒤에를 판별하자! 
		$(뒤가 스페이스나 '\0'), $$, $!, $?, $num => 하드코딩  ${} => 끝이 특수문자 이기 전까지 '_' 제외 substring(str + i, 0, len)
	2. str[i] == 달러가 아닌경우
		$ 나 '\0'을 만날때 까지  인덱스 늘려서 substring 실행
	이렇게 크게 생각하면 될듯 
*/

// int	main(int ac, char **av, char **envp) //test 메인문
// {
// 	int i = 0;
// 	t_envp	*head;
// 	t_envp	*tmp;
// 	char	*str = "$USER$$PATH$ $$$999...$USR$@@@";
// 	char	*ret;

// 	head = set_envp(envp);
// 	tmp = head;
// 	ret = parse_dollar(str, tmp);
// 	printf("input : %s\noutput : %s\n", str, ret);
// 	return (0);
// }

/*
뒤에 이상한 문자 이어지는 경우 판별할 수 있는지 테스트 필요
ex. $aaa로 들어와서 aaa환경변수 찾았는데, 알고보니 환경변수 키가 aaab인 경우 ?
=> strcmp에서 0이 안 나옴 ! 널이랑 다음 문자 비교하기 때문

레전드 : echo $123a시 23a 출력 ㅅㄱ ... -> 이게 배쉬 !!!
첫글자 보고 숫자면 한글자 넘기고 빠꾸쳐야댈듯 ..
*/