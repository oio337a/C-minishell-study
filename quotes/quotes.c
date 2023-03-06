/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/06 16:10:51 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_dollar(char *dollar)
{
	char	*tmp;
	char	*key;
	int		i;

	tmp = dollar;
	while (*tmp != ' ' && *tmp)
	{
		*tmp++;
		i++;
	}
	key = (char *)ft_safe_malloc(i + 1);
	// if (!key)
	// 	error();
	if // env에 있으면 나키님 env 계속 필요한거 같은데 전역에 놓을까여??
		
	else // 없는 환경변수면 안 나옴
	
}

char	*ft_strappend(char *str, char append)
{
	char	*ret;
	int		len;

	len = ft_strlen(str);
	ret = ft_safe_malloc(len + 2);

	while(*str)
	{
		*ret = *str;
		str++;
		ret++;
	}
	ret[len] = append;
	ret[len + 1] = '\0';
	free(str);
	return (ret);
}

char	*quotes(char *c) // 문자의 주소값을 인자로 받기
{
	char	*ret;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	if (*c == '\"')
	{
		while (*c != '\"')
		{
			if (*c == '$')
				ret = process_dollar(c);
			else
				ret = ft_strappend(ret, *c);
			c++;
		}
	}
	else if (*c == '\'')
	{
		while (*c != '\'')
		{
			ret = ft_strappend(ret, *c);
			c++;
		}
	}
	else //잘못된 인자
		return (NULL);
	return (ret);
}
