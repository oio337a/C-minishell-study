#include "../includes/minishell.h"

static int	is_whitespace2(char line) //스페이스가 아닐 때 리턴 1을 하는 걸 왜 이름을 이렇게?
{
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

static char *quote_bulk_n_error_trim(char *line, char c)
{
	int		i;
	char	*bulk;

	i = 1;
	while (line[i] && line[i] != c)
		i++;
	if (line[i] != '\0')
		bulk = ft_substr(line, 1, i - 1);
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

	i = 0;
	printf("line : %s\n", line);
	while (*line != '\0')
	{
		if (*line == '\"')
		{
			printf("!!!!!!!!!!is double quotes!!!!!!!!!!\n");
			bulk = quote_bulk_n_error_trim(line, '\"');
		//	tmp = bulk; //왜 ?
			line = line + ft_strlen(bulk) + 1;
			if (*line != ' ')
				bulk = get_after_quote(line, bulk);
		//	free(tmp);
			line = line + ft_strlen(bulk) - 1;
			insert_list(info, bulk, WORD);
		}
		else if (*line == '\'')
		{
			printf("!!!!!!!!!!is single quotes!!!!!!!!!!\n");
			bulk = quote_bulk(line, '\'');
		//	tmp = bulk;
			line = line + ft_strlen(bulk);
			if (*line != ' ')
				bulk = get_after_quote(line, bulk);
		//	free(tmp);
			line = line + ft_strlen(bulk) - 1;
			insert_list(info, bulk, WORD);
		}
		else if (*line == '>')
		{
			printf("!!!!!!!!!!is right redirection!!!!!!!!!!\n");
			if (*(line + 1) == '>')
			{
				insert_list(info, ">>", REDIR);
				line++;
			}
			else
				insert_list(info, ">", REDIR);
		}
		else if (*line == '<')
		{
			printf("!!!!!!!!!!is left redirection!!!!!!!!!!\n");
			if (*(line + 1) == '<')
			{
				insert_list(info, "<<", REDIR);
				line++;
			}
			else
				insert_list(info, "<", REDIR);
		}
		else if (*line == '|')
		{
			printf("!!!!!!!!!!is pipe!!!!!!!!!!\n");
			insert_list(info, "|", PIPE);
		}
		else if (/**line != '>' && *line != '<' && *line != '|' && */*line != ' ')
		{
			printf("!!!!!!!!!!is word!!!!!!!!!!\n");
			i = 0;
			while (line[i] && is_whitespace2(line[i]))
				i++;
			if (i == 0)
				break ;
			tmp = ft_substr(line, 0, i);
			insert_list(info, tmp, WORD);
			// line = line + ft_strlen(tmp);
			line = line + i - 1;
			free(tmp);
			// printf("line : %s\n", line);
		}
		if (*line == '\0')
			break ;
		line++;
	} //	char *str = "  echo qkjwke xnfnwl";
}

// void	delete_quote(t_info *info)
// {
// 	t_info *head;
// 	int	i;
// 	int	count;
// 	int	next_q_idx;

// 	i = 0;
// 	head = info;
// 	count = 0;
// 	next_q_idx = 0;
// 	while (head != NULL)
// 	{
// 		count = list_quotes(head->cmd);
// 		head->cmd = (char *)malloc(ft_strlen(head->cmd) - count + 1);
// 		while (head->cmd[i])
// 		{
// 			if (head->cmd[i] == '\'')
// 				i++;
// 			head->cmd[i] =

// 		}
// 	}
// }

int main()
{
	t_info *test;
	char *str = "echo \"aaa\"bb\"$CCC\" ";

	test = init_list();
	str_tokenize(test, str);
	while (test != NULL)
	{
		printf("cmd : %s, type : %d\n", test->cmd, test->type);
		test = test->next;
	}
//	system("leaks a.out");
}

