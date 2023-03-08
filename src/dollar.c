/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/08 18:31:05 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dollar(char *token)
{
	int	i;

	i = -1;
	while(token[++i])
	{
		if (token[i] == '$')
			return (i);
	}
	return (-1);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str + s1_len, s2, s2_len + 1);
	free(s1);
	return (str);
}

char	*find_key(char *dollar)
{
	char	*key;
	int		i;
	int		len; //말록하기 위해 key 길이 구함
	
	i = 1;
	// if (dollar[i++] == '?')
	// 	return (exit_code); //$? 처리
	// if (dollar[i++] == '$')
	// {
	// 	if (dollar[i++] == '$')
	// 		printf("%d", pid);
	// 	else
	// 		printf("\$");
	// }
	if (ft_isdigit(dollar[i])) // $ 넘기기
		return (ft_strdup(""));
	while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))	//1. key 찾기. key 이름은 알파벳 + 숫자 + 언더바만 고려.
		i++;
	key = ft_substr(dollar, 1, i - 1); //2. key에 duplicate . .
	return (key);
}

char	*find_value(char *key, t_envp *envp)
{
	t_envp	*head;

	head = envp;
	while (head != NULL)	//3. 환경변수 리스트 돌면서 key값 일치하는 것 있는지 찾음
	{
		if (ft_strncmp(key, head->key, ft_strlen(key)) == 0) // 있는 환경변수면 replace
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (ft_strdup("")); // 없는 환경변수면 안 나옴
}

char	*parse_dollar(char *str, t_envp *head)
{
	t_envp	*tmp;
	char	*ret;
	char	*key;
	char	*value;
	int 	len;
	int		i;

	tmp = head;
	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			// ret = ft_strjoin_free(ret, ft_substr(str, 0, len)); // 달러 전까지 문자열 잘라서 저장
			key = find_key(str + i);
			value = find_value(key, tmp);
			ret = ft_strjoin_free(ret, value);
			i += ft_strlen(key); //달러까지 넘기기 ..
			free(key);
			free(value);
		}
		else
		{
			len = is_dollar((str + i));
			ret = ft_strjoin_free(ret, ft_substr((str + i), 0, len));
			i += (len - 1);
		}
		i++; // $USER R 위치로 바꿔야지 된다 
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
	
	질문 : 처음 substr은 (str, 0, i)로 진행하면 되는데
	중간에 substr을 하고 싶으면 이전 인덱스와 현재 인덱스를 모두 저장하고 있어야 하는거죠 ?
*/
int	main(int ac, char **av, char **envp) //test 메인문
{
	int i = 0;
	t_envp	*head;
	t_envp	*tmp;
	char	*str = "I am $1 $USER";
	char	*ret;

	head = set_envp(envp);
	tmp = head;
	ret = parse_dollar(str, tmp);
	printf("input : %s\noutput : %s\n", str, ret);
	return 0;
}

/*
뒤에 이상한 문자 이어지는 경우 판별할 수 있는지 테스트 필요
ex. $aaa로 들어와서 aaa환경변수 찾았는데, 알고보니 환경변수 키가 aaab인 경우 ?
=> strncmp에서 0이 안 나옴 ! 널이랑 다음 문자 비교하기 때문
*/
//나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!
/*
key 처음 문자가 숫자가 오면 안되는데, 솔직히 달러에서는 알빠 아니지 않나요 ?ㅋㅋㅋㅋㅋ 알빠 너무 웃기다 

등록 된 게 없을거니까 .. ㅅㄱ
레전드 : echo $123a시 23a 출력 ㅅㄱ ... -> 이게 배쉬 !!!
첫글자 보고 숫자면 한글자 넘기고 빠꾸쳐야댈듯 ..
*/