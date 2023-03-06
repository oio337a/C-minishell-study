/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naki <naki@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:04:10 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/06 20:15:53 by naki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char c)
{
	size_t	s;
	size_t	e;

	s = 0;
	e = ft_strlen(s1) - 1;
	while (s1[s] != '\0' && s1[s] == c)
		s++;
	if (s >= (e + 1))
		return ((char *)ft_calloc(1, 1));
	while (s1[e] == c)
		e--;
	free(s1);
	return (ft_substr(s1, s, (e - s + 1)));
}
// "l"s -al | cat -e "|" "cat -e" ">" b
// ls
// -al
// |
// cat
// -e
// | -> type word
// cat -e
// > -> type word
// b

