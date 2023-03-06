/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/06 20:40:36 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	head = envp->next; //첫번째는 널임
	// if (*dollar == '?')
	// 	return (exit_code); //$? 처리
	while (*dollar && (ft_isalnum(*dollar) || *dollar == '_'))	//1. key 찾기
	{ // key 이름은 알파벳 + 숫자 + 언더바만 고려. 반례 있다면 알려주세요
		dollar++; //인덱스 넘김 -> 환경변수 맨 마지막 글자에 위치해있어야 함..!
		len++;
	}
	key = ft_substr(dollar, 0, len); //2. key에 duplicate . .
	// if (!key)
	// 	error();
	while (head)	//3. 환경변수 리스트 돌면서 key값 일치하는 것 있는지 찾음
	{
		if (key == head->key) // 있는 환경변수면 replace
			return (head->value);
		head = head->next;
	}
	return (NULL); // 없는 환경변수면 안 나옴
}

// char	*ft_strappend(char *str, char append)
// {
// 	char	*ret;
// 	int		len;

// 	len = ft_strlen(str);
// 	ret = ft_safe_malloc(len + 2);
// 	// if (!ret)
// 	// 	error();
// 	while(*str) //dup쓰면 말록 두번하게 되니까 그냥 한글자씩 넘김
// 	{
// 		*ret = *str;
// 		str++;
// 		ret++;
// 	}
// 	ret[len] = append;
// 	ret[len + 1] = '\0';
// 	free(str);
// 	return (ret);
// }

// char	*quotes(char *c, t_envp *head) // 문자의 주소값을 인자로 받기
// {
// 	char	*dol;
// 	char	*ret;
// 	t_envp	*tmp;

// 	tmp = head;
// 	ret = ft_strdup("");
// 	if (!ret)
// 		return (NULL);
// 	if (*c == '\"')
// 	{
// 		c++;
// 		while (*c != '\"')
// 		{
// 			if (*c == '$')
// 			{
// 				dol = parse_dollar(c, head);
// 				ret = ft_strjoin_free(ret, dol);
// 			}
// 			else
// 				ret = ft_strappend(ret, *c);
// 			c++;
// 		}
// 	}
// 	else if (*c == '\'')
// 	{
// 		c++;
// 		while (*c != '\'')
// 		{
// 			ret = ft_strappend(ret, *c);
// 			c++;
// 		}
// 	}
// 	else //잘못된 인자일 경우
// 		return (NULL);
// 	return (ret);
// }
