#include "../includes/minishell.h"

// "ls$-a"'l$|$' "c"at '-e$|' cat -e
// ls$-al$|$ cat -e$| cat -e
// ls$-al$ /$ cat -e$/ cat -e -> 에러 O
// "ls" -al '|'cat -e | "wc '-'l"
// "ls" -al '|'cat -e | "wc$'-'l"
// ls -al | cat -e | wc$'-'l
// ls -al / cat -e / wc$'-'l -> 에러인데 에러로 못골라줘여 파이프 우짬?

static int	find_next_quotes(char *line, char *quote, int quote_idx)
{
	int	next_idx;

	next_idx = quote_idx + 1;
	while (line[next_idx])
	{
		if (line[next_idx] == quote)
			return (next_idx); // 짝 맞는 가장 가까운 쿼터 idx 반환
		next_idx++;
	}
	return (-1); // 맞는 쿼터를 찾지 못했음
}

static char	*delete_q(char *line, int *quote)
{
	char	*removed_quotes;
	int		i;
	int		j;
	int		new_len;
	int		next_idx;

	new_len = ft_strlen(line) - (quote[0] + quote[1]) + 1;
	removed_quotes = (char *)malloc(new_len);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			next_idx = find_next_quotes(line, '\'', i);
			while (i < next_idx)
			{
				if (line[i] == '\'')
					i++;
				else
				{
					removed_quotes[j] = line[i];
					i++;
					j++;
				}
			}
		}
		else if (line[i] == '\"')
		{
			next_idx = find_next_quotes(line, '\"', i);
			while (i < next_idx)
			{
				if (line[i] == '\"')
					i++;
				else
				{
					removed_quotes[j] == line[i];
					i++;
					j++;
				}
			}
		}
		else
		{
			removed_quotes[j] = line[i];
			i++;
			j++;
		}
	}
	removed_quotes[i] = '\0';
	return (removed_quotes);
}

char	*space_change(char *str)
{
	int		i;
	int		next_quote;
	char	*valid;
	int		*quote;

	quote = count_q(str); // 전체 한 줄의 모든 쿼터 개수 알음
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			next_quote = find_next_quotes(str, '\'', i);
			// if (next_quote == -1)
			//  err
			while (i < next_quote)
			{
				if (str[i] == ' ')
					str[i] == DLIMITER;
				if (str[i] == '\"')
					quote[1]--;
				i++;
			}
		}
		else if(str[i] == '\"')
		{
			next_quote = find_next_quotes(str, '\"', i);
			// if (next_idx == -1) // 짝 맞는 쿼터가 없습니다.
			// 		err
			while (i < next_quote)
			{
				if (str[i] == ' ')
					str[i] == DLIMITER;
				if (str[i] == '\'')
					quote[0]--;
				i++;
			}
		}
		else
			i++;
	}
	str = delete_q(str, quote);
	return (str);
}