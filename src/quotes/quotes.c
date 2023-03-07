/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/07 20:33:13 by suhwpark         ###   ########.fr       */
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
		dollar++; //인덱스 넘김 -> 와일문 나오면 환경변수 다음 글자 가리키고 있음
		len++;
	}
	key = ft_substr(tmp, 0, len); //2. key에 duplicate . .
	while (head)	//3. 환경변수 리스트 돌면서 key값 일치하는 것 있는지 찾음
	{
		if (ft_strncmp(key, head->key, len) == 0) // 있는 환경변수면 replace
			return (head->value); // 뒤에 이상한 문자 이어지는 경우 판별할 수 있는지 테스트 필요
		head = head->next; // ex. $aaa로 들어와서 aaa환경변수 찾았는데, 알고보니 aaab인 경우 ?
	}
	return (NULL); // 없는 환경변수면 안 나옴
}

int	main(int ac, char **av, char **envp) //test 메인문
{
	int i = 0;
	t_envp	*head;
	char	*str = "$a";
	char	*ret;

	head = set_envp(envp);
	// printf("////////////////////////\n");
	// printf("original output\n");
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// printf("////////////////////////\n");
	// printf("ft_env output\n");
	// ft_env(head);
	ret = parse_dollar(str, head);
	printf("input key : %s\noutput value : %s\n", str, ret);
	return 0;
}
