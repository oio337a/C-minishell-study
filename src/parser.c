/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:34:22 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 14:33:30 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	*count_q(char *munja);
void	pipe_parser(char *line, t_info *info);
static int	find_last_quote(char *line, char quote);
static char	*delete_quote(char *line, int *quote);
char	*validate_readline(char *line);

// int	*count_q(char *munja)
// {
// 	int	*q;
// 	int	i;

// 	q = malloc(8);
// 	i = -1;
// 	q[0] = 0;
// 	q[1] = 0;
// 	while (munja[++i])
// 	{
// 		if (munja[i] == '\"')
// 			q[1]++;
// 		else if (munja[i] == '\'')
// 			q[0]++;
// 	}
// 	return (q);
// }

void	pipe_parser(char *line, t_info *info)
{
	char	**a_p;
	char	**cmd;
	char	*v_line;
	int		i;
	int		j;

	i = 0;
	a_p = ft_split(line, '|'); // "ls" -al / "cat" -e / wc -l
	// if (!a_p)
	// 	return (NULL);
	while (a_p[i])
	{
		// cmd = ft_split(a_p[i], ' '); // cmd = "ls" / -al?
		v_line = validate_readline(a_p[i], count_q(a_p[i])); //-> str -> ls -al
		///쿼터 확인하는 함수!
		j = 0;
		while (v_line[j])
		{
			insert_list(info, v_line[j]);
			j++;
		}
		// if (*a_p[i] == '\'' || '\"')
			// quoters = 1;
		ft_free(cmd);
		i++;
	}
	// ft_free(a_p);
}

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

	v_line = (char *)malloc(ft_strlen(line) - (quote[0] + quote[1]) + 1);
	i = 0;
	j = 0;
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
		else
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

	quote = count_q(line);
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
		else
			i++;
	}
	//쿼터 지우기
	// if (count[0]/2 != 0 || count[1]/2 != 0)
	// 	printf("%s: %s\n", line, strerror(errno)); // 에러 출력 후 새로운 line을 받도록
	v_line = delete_quote(line, count);
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
