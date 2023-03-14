/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yongmin_jakup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:32:13 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/14 21:58:29 by yongmipa         ###   ########seoul.kr  */
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

static void	redir_check(t_info *info, char **line)
{
	char	*temp;
	int		type;

	type = HEREDOC_IN;
	write(1, **line, 1);
	write(1, **(line + 1), 1);
	printf("line first : %c\n", **line);
	printf("line second: %c\n", *(*line + 1));
	write(1, "temp : ", 7);
	//당신의 무심함이 한 파서를 죽였습니다.. 당신을 기억할 것입니다.. 미친사람 아니야 이거
	// 니가죽엿어 니가죽엿다고 니가죽여
	// 용민아 이거 주소 옮기는거 내일 다시 봐야 한단다?? 넌 충분히 잘했어 괜찮아 ...
	// 용민아 65번째 줄은 신경 쓰지 않ㅅ아도 ㄷ ㅋㅋㅋ괜찮아 사람들이 널 물고 뜯어도 괜찮 단다??
	// 내일 이거 line 받아오는거 테스트 하면서 주소 옮기렴 파이팅ㄹ!!!!!
	if (**(line + 1) == **line)
	{
		if (**(line + 1) == '>')
			type = HEREDOC_OUT;
		temp = ft_substr(*line, 0, 2);
		write(1, temp, 2);
		insert_list(info, temp, type);
		free(temp);
		*line += 2;
	}
	else
	{
		if (**line == '>')
			insert_list(info, ">", REDIR_OUT);
		else if (**line == '<')
			insert_list(info, "<", REDIR_IN);
		else
			insert_list(info, "|", PIPE);
	}
}

void	quote_process(t_info *info, char **line)
{
	char	*bulk;
	char	*tmp;

	bulk = quote_bulk(*line, **line);
	if (!ft_strlen(bulk))
	{
		*line += 2;
		while (**line == '\"' && **line != '\0' && **line != ' ')
		{
			if (**(line + 1) != '\"')
				break ;
			*line += 2;
		}
	}
	else
		*line += ft_strlen(bulk);
	tmp = bulk;
	if (**line != ' ')
	{
		bulk = get_after_quote(*line, tmp);
		*line += (ft_strlen(bulk) - ft_strlen(tmp));
	}
	insert_list(info, bulk, WORD);
	free(tmp);
}

void	remainder(t_info *info, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*line)[i] && is_whitespace2((*line)[i]))
		i++;
	tmp = ft_substr(*line, 0, i);
	insert_list(info, tmp, WORD);
	*line += ft_strlen(tmp);
	free(tmp);
}

void	str_tokenize(t_info *info, char *line)
{
	while (*line)
	{
		if (*line == '>' || *line == '<' || *line == '|')
			redir_check(info, &line);
		else if (*line == '\"' || *line == '\'')
			quote_process(info, &line);
		else if (*line != '>' && *line != '<' && *line != '|' && *line != ' ')
			remainder(info, &line);
		if (*line == '\0')
			break ;
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
// 		write(1, "1", 1);
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
