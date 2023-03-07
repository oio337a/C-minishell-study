/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/07 22:41:32 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*parse_dollar(char *dollar, t_envp *envp)
{
	t_envp	*head;
	char	*tmp;
	char	*key;
	int		len; //말록하기 위해 key 길이 구함

	dollar++; // $ 넘기기
	tmp = dollar; // 환경변수 이름 시작 위치 저장
	head = envp;
	// if (*dollar == '?')
	// 	return (exit_code); //$? 처리
	if (ft_isdigit(*dollar++))
		return (ft_strdup(""));
	while (*dollar && (ft_isalnum(*dollar) || *dollar == '_'))	//1. key 찾기
	{ // key 이름은 알파벳 + 숫자 + 언더바만 고려.
		dollar++; //인덱스 넘김 -> 와일문 나오면 환경변수 다음 글자 가리키고 있음
		len++;
	}
	key = ft_substr(tmp, 0, len + 1); //2. key에 duplicate . .
	while (head != NULL)	//3. 환경변수 리스트 돌면서 key값 일치하는 것 있는지 찾음
	{
		if (ft_strncmp(key, head->key, len) == 0) // 있는 환경변수면 replace
			return (head->value);
		head = head->next;
	}
	return (ft_strdup("")); // 없는 환경변수면 안 나옴
}

int	main(int ac, char **av, char **envp) //test 메인문
{
	int i = 0;
	t_envp	*head;
	t_envp	*tmp;
	char	*str = "asdf$123a";
	char	*ret;
	char	*value;

	head = set_envp(envp);
	tmp = head;
	ret = parse_dollar(str, tmp);
	while (*str)
	{
		if (*str == '$')
		{
			value = parse_dollar(str, tmp);
			ret += ft_strlen(value);
			
		}
		else
		{
			*ret = *str;
			ret++;
			str++;
		}
	}
	printf("input key : %s\noutput value : %s\n", str, ret);
	return 0;
}

/*
뒤에 이상한 문자 이어지는 경우 판별할 수 있는지 테스트 필요
ex. $aaa로 들어와서 aaa환경변수 찾았는데, 알고보니 환경변수 키가 aaab인 경우 ?
=> strncmp에서 0이 안 나옴 ! 널이랑 다음 문자 비교하기 때문
*/
//나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!나키!
/*
key 처음 문자가 숫자가 오면 안되는데, 솔직히 달러에서는 알빠 아니지 않나요 ?
등록 된 게 없을거니까 .. ㅅㄱ
레전드 : echo $123a시 23a 출력 ㅅㄱ ...
첫글자 보고 숫자면 빠꾸쳐야댈듯 ..
*/