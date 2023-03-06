#include "../includes/minishell.h"

static int	is_whitespace2(char c)
{
	if (c != 32 && !(c >= 9 && c <= 13))
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
	real_bulk = ft_strjoin(bulk, tmp);
	free(tmp);
	return (real_bulk);
}

void	str_tokenize(t_info *info, char *line)
{
	int	i;
	int j;
	char *tmp;
	char *bulk;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			bulk = quote_bulk(line, '\"');
			printf("bulk : %s\n", bulk);
			tmp = bulk;
			i += ft_strlen(bulk);
			if (line[i] != ' ')
				bulk = get_after_quote(line, bulk);
			free(tmp);
			i += ft_strlen(bulk);
			insert_list(info, bulk, WORD);
		}
		else if (line[i] == '\'')
		{
			bulk = quote_bulk(line, '\'');
			tmp = bulk;
			i += ft_strlen(bulk);
			if (line[i] != ' ')
				bulk = get_after_quote(line, bulk);
			free(tmp);
			i += ft_strlen(bulk);
			insert_list(info, bulk, WORD);
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				insert_list(info, ">>", REDIR);
				i++;
			}
			else
				insert_list(info, ">", REDIR);
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				insert_list(info, "<<", REDIR);
				i++;
			}
			else
				insert_list(info, "<", REDIR);
		}
		else if (line[i] == '|')
			insert_list(info, "|", PIPE);
		else if (line[i] != '>' && line[i] != '<' && line[i] != '|' && line[i] != ' ')
		{
			j = i;
			while (line[i] && is_whitespace2(line[i]))
				i++;
			tmp = ft_substr(line, j, i - j);
			insert_list(info, tmp, WORD);
			free(tmp);
			i--;
		}
		// if (line[i] == '\"' || line[i] == '\'')
		// {
		// 	tmp = //쿼터 처리한 문자열
		// }
		i++;
	}
}

int main()
{
	t_info *test;
	t_info *tmp;
	char *str = "echo \"aaabb$CCC\"";

	test = init_list();
	str_tokenize(test, str);
	tmp = test;
	while (tmp != NULL)
	{
		printf("cmd : %s type : %d\n", tmp->cmd, tmp->type);
		tmp = tmp->next;
	}
}
