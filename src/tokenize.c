/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:32:13 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/14 17:42:03 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_whitespace2(char line)
{
	if (line != 32 && !(line >= 9 && line <= 13))
		return (1);
	return (0);
}

static char	*quote_bulk(char *line, char c)
{
	int		i;
	char	*bulk;

	i = 1;
	if (line[i] == c)
	{
		bulk = ft_strdup("");
		return (bulk);
	}
	while (line[i] != c)
		i++;
	bulk = ft_substr(line, 0, i + 1);
	return (bulk);
}

static char	*get_after_quote(char *line, char *bulk)
{
	char	*tmp;
	char	*real_bulk;
	int		i;

	i = 0;
	while (line[i] && is_whitespace2(line[i]))
		i++;
	tmp = ft_substr(line, 0, i);
	real_bulk = ft_strjoin(bulk, tmp);
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
				insert_list(info, ">>", HEREDOC_OUT);
				line++;
			}
			else
				insert_list(info, ">", REDIR_OUT);
		}
		else if (*line == '<')
		{
			if (*(line + 1) == '<')
			{
				insert_list(info, "<<", HEREDOC_IN);
				line++;
			}
			else
				insert_list(info, "<", REDIR_IN);
		}
		else if (*line == '|')
			insert_list(info, "|", PIPE);
		else if (*line == '\"')
		{
			bulk = quote_bulk(line, '\"');
			if (!ft_strlen(bulk))
			{
				line += 2;
				while (*line == '\"' && *line != '\0' && *line != ' ')
				{
					if (*(line + 1) != '\"')
						break ;
					line += 2;
				}
			}
			else
				line += ft_strlen(bulk);
			tmp = bulk;
			if (*line != ' ')
			{
				bulk = get_after_quote(line, tmp);
				line += (ft_strlen(bulk) - ft_strlen(tmp));
			}
			insert_list(info, bulk, WORD);
			free(tmp);
			// free(bulk);
			if (*line == '\0')
				break ;
		}
		else if (*line == '\'')
		{
			bulk = quote_bulk(line, '\'');
			if (!ft_strlen(bulk))
			{
				line += 2;
				while (*line == '\'' && *line != '\0' && *line != ' ')
				{
					if (*(line + 1) != '\'')
						break ;
					line += 2;
				}
			}
			else
				line += ft_strlen(bulk);
			tmp = bulk;
			if (*line != ' ')
			{
				bulk = get_after_quote(line, tmp);
				line += (ft_strlen(bulk) - ft_strlen(tmp));
			}
			insert_list(info, bulk, WORD);
			free(tmp);
			if (*line == '\0')
				break ;
		}
		else if (*line != '>' && *line != '<' && *line != '|' && *line != ' ')
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

// int main()
// {
// 	t_info *test;
// 	t_info *head1;
// 	t_info *head2;

// 	char *str = "cat \"$USER\" | ls -al | cat '-e' | 'w'c -l > a";

// 	printf("line : %s\n", str);
// 	test = init_list();
// 	str_tokenize(test, str);
// 	head1 = test;
// 	while(head1 != NULL)
// 	{
// 		printf("cmd : %s, type : %d\n", head1->cmd, head1->type);
// 		head1 = head1->next;
// 	}
// 	clear_quote_in_token(test);
// 	head2 = test;
// 	while (head2 != NULL)
// 	{
// 		printf("a-fter cmd : %s, type : %d\n", head2->cmd, head2->type);
// 		head2 = head2->next;
// 	}
// 	// system("leaks a.out");
// }
