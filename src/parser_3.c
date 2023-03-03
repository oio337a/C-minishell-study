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
		i = last;
	}
	v_line[j] = '\0';
	return (v_line);
}

char	*validate_readline(char *line, int *count)
{
	int	i;
	int	last;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
		{
			last = find_last_quote(line, '\"');
			while (i < last)
			{
				if (line[i] == ' ')
					line[i] = DLIMITER;
				if (line[i] == '\'')
					count[0]--;
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
			}
		}
		i = last;
	}
	//쿼터 지우기
	if (count[0]/2 != 0 && count[1]/2 != 0);
		printf("%s: %s\n", line, strerror(errno));
	delete_quote(line, count);
	return (line);
}
