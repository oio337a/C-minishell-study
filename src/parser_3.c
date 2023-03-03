/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:34:22 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/03 19:43:46 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_last_quote(char *line, char quote)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i)
	{
		if (line[i] == quote)
			break ;
		i--;
	}
	return (i);

}

static char	*delete_quote(char *line, int *quote)
{
	char	*v_line;
	int		last;
	int		i;
	int		j;
	int		k;

	v_line = (char *)malloc(ft_strlen(line) - (quote[0] + quote[1]) + 1);
	i = 0;
	j = 0;
	k
	while (line[i])
	{
		if (line[i] == '\"')
		{
			last = find_last_quote(line, '\"');
			while (i < last)
			{
				if (line[i] == '\"')
					i++;
				else
				{
					v_line[j] = line[i];
					i++;
					j++;
				}
			}
		}
		else if (line[i] == '\'')
		{
			last = find_last_quote(line, '\'');
			while (i < last)
			{
				if (line[i] == '\'')
					i++;
				else
				{
					v_line[j] = line[i];
					i++;
					j++;
				}
			}
		}
		// i = last;
		i++;
	}
	v_line[j] = '\0';
	return (v_line);
}

char	*validate_readline(char *line)
{
	int		i;
	int		last;
	char	*v_line;
	int		*quote;

	quote = count_q(quote);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
		{
			last = find_last_quote(line, '\"');
			printf("last q idx : %d\n", last);
			while (i < last)
			{
				if (line[i] == ' ')
					line[i] = DLIMITER;
				if (line[i] == '\'')
					count[0]--;
				i++;
			}
		}
		else if (line[i] == '\'')
		{
			last = find_last_quote(line, '\'');
			while (i < last)
			{
				if (line[i] == ' ')
					line[i] == DLIMITER;
				if (line[i] == '\"')
					count[1]--;
				i++;
			}
		}
		i = last;
	}
	//쿼터 지우기
	// if (count[0]/2 != 0 || count[1]/2 != 0)
	// 	printf("%s: %s\n", line, strerror(errno)); // 에러 출력 후 새로운 line을 받도록
	v_line = delete_quote(line, count);
		printf("v_r 빠져나왔음\n");
	i = 0;
	while (v_line[i])
	{
		if (v_line[i] == DLIMITER)
			v_line[i] = ' ';
	}
	return (v_line);
}

#include <stdio.h>

int main(void)
{
	char *str = readline("입력 : ");
	int *a = {0,4}; 
	char *line = validate_readline(str, a);

	printf("%s", line);
	return (0);
}