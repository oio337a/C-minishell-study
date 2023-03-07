#include "../includes/minishell.h"

// static int list_quotes(char *line)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'' || line[i] == '\"')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// static int	find_next_quotes2(char *line, char *quote, int quote_idx)
// {
// 	int	next_idx;

// 	next_idx = quote_idx + 1;
// 	while (line[next_idx])
// 	{
// 		if (line[next_idx] == quote)
// 			return (next_idx); // 짝 맞는 가장 가까운 쿼터 idx 반환
// 		next_idx++;
// 	}
// 	return (-1); // 맞는 쿼터를 찾지 못했음
// }

static int	is_whitespace2(char line)
{ // 스페이스가 아닐 때 리턴 1을 하는 거면 이름이 반대여야 하는 거 아닌가요
	if (line != 32 && !(line >= 9 && line <= 13))
		return (1);
	return (0);
}

static char *quote_bulk(char *line, char c)
{
	int		i;
	char	*bulk;

	i = 1;
	while (line[i] != c)
		i++;
	bulk = ft_substr(line, 0, i + 1);
	return (bulk);
}

static char *get_after_quote(char *line, char *bulk)
{
	char *tmp;
	char *real_bulk;
	int i;

	i = 0;
	while (is_whitespace2(line[i]))
		i++;
	tmp = ft_substr(line, 0, i);
	real_bulk = ft_strjoin(bulk, tmp); //bulk free 안 해줘도 되는지 ?
	free(tmp);
	return (real_bulk);
}

void	str_tokenize(t_info *info, char *line)
{
	int		i;
	char	*tmp;
	char	*bulk;
	char	*tmp2;

	i = 0;
	while (*line)
	{
		if (*line == '>')
		{
			if (*(line + 1) == '>')
			{
				insert_list(info, ">>", REDIR);
				line++;
			}
			else
				insert_list(info, ">", REDIR);
		}
		if (*line == '<')
		{
			if (*(line + 1) == '<')
			{
				insert_list(info, "<<", REDIR);
				line++;
			}
			else
				insert_list(info, "<", REDIR);
		}
		if (*line == '|')
			insert_list(info, "|", PIPE);
		if (*line == '\"')
		{
			bulk = quote_bulk(line, '\"');
			tmp = bulk;
			line += ft_strlen(bulk);
			if (*line != ' ')
			{
				bulk = get_after_quote(line, tmp);
				line += (ft_strlen(bulk) - ft_strlen(tmp));
			}
			insert_list(info, bulk, WORD);
			free(tmp);
			free(bulk);
			if (*line == '\0')
				break ;
		}
		if (*line == '\'')
		{
			bulk = quote_bulk(line, '\'');
			tmp = bulk;
			line += ft_strlen(bulk);
			if (*line != ' ')
				bulk = get_after_quote(line, tmp);
			line += (ft_strlen(bulk) - ft_strlen(tmp));
			insert_list(info, bulk, WORD);
			free(tmp);
			free(bulk);
			if (*line == '\0')
				break ;
		}
		if (*line != '>' && *line != '<' && *line != '|' && *line != ' ')
		{
			i = 0;
			while (line[i] && is_whitespace2(line[i]))
				i++;
			tmp = ft_substr(line, 0, i);
			insert_list(info, tmp, WORD);
			line += ft_strlen(tmp);
			free(tmp);
			if (*line == '\0')
				break ;
		}
		line++;
	}
}

int main()
{
	t_info *test;
	char *str = "<<< a ls | cat > \"b\"";

	printf("line : %s\n", str);
	test = init_list();
	str_tokenize(test, str);
	while (test != NULL)
	{
		printf("cmd : %s, type : %d\n", test->cmd, test->type);
		test = test->next;
	}
	system("leaks a.out");
}
